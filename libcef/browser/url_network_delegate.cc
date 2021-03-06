// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "libcef/browser/url_network_delegate.h"

#include <string>

#include "include/cef_urlrequest.h"
#include "libcef/browser/browser_host_impl.h"
#include "libcef/browser/thread_util.h"
#include "libcef/browser/url_request_user_data.h"
#include "libcef/common/request_impl.h"

#include "net/base/net_errors.h"
#include "net/http/http_util.h"
#include "net/url_request/url_request.h"

namespace {

class CefBeforeResourceLoadCallbackImpl : public CefRequestCallback {
 public:
  typedef net::CompletionCallback CallbackType;

  CefBeforeResourceLoadCallbackImpl(
      CefRefPtr<CefRequestImpl> cef_request,
      GURL* new_url,
      net::URLRequest* url_request,
      const CallbackType& callback)
      : cef_request_(cef_request),
        new_url_(new_url),
        url_request_(url_request),
        callback_(callback) {
    DCHECK(new_url);
    DCHECK(url_request_);

    // Add an association between the URLRequest and this object.
    url_request_->SetUserData(UserDataKey(), new Disconnector(this));
  }

  ~CefBeforeResourceLoadCallbackImpl() {
    if (!callback_.is_null()) {
      // The callback is still pending. Cancel it now.
      if (CEF_CURRENTLY_ON_IOT()) {
        RunNow(cef_request_, new_url_, url_request_, callback_, false);
      } else {
        CEF_POST_TASK(CEF_IOT,
            base::Bind(&CefBeforeResourceLoadCallbackImpl::RunNow,
                       cef_request_, new_url_, url_request_, callback_, false));
      }
    }
  }

  void Continue(bool allow) override {
    // Always continue asynchronously.
    CEF_POST_TASK(CEF_IOT,
        base::Bind(&CefBeforeResourceLoadCallbackImpl::ContinueNow,
                   this, allow));
  }

  void Cancel() override {
    Continue(false);
  }

  void ContinueNow(bool allow) {
    CEF_REQUIRE_IOT();
    if (!callback_.is_null()) {
      RunNow(cef_request_, new_url_, url_request_, callback_, allow);
      Disconnect();
    }
  }

  void Disconnect() {
    CEF_REQUIRE_IOT();
    cef_request_ = nullptr;
    new_url_ = nullptr;
    url_request_ = nullptr;
    callback_.Reset();
  }

 private:
  // Used to disconnect the callback when the associated URLRequest is
  // destroyed.
  class Disconnector : public base::SupportsUserData::Data {
   public:
    explicit Disconnector(CefBeforeResourceLoadCallbackImpl* callback)
        : callback_(callback) {
    }
    ~Disconnector() override {
      if (callback_)
        callback_->Disconnect();
    }

    void Disconnect() {
      callback_ = NULL;
    }

   private:
    CefBeforeResourceLoadCallbackImpl* callback_;
  };

  static void RunNow(CefRefPtr<CefRequestImpl> cef_request,
                     GURL* new_url,
                     net::URLRequest* request,
                     const CallbackType& callback,
                     bool allow) {
    CEF_REQUIRE_IOT();

    if (allow) {
      const GURL& old_url = request->url();
      GURL url = GURL(cef_request->GetURL().ToString());
      if (old_url != url)
        new_url->Swap(&url);

      cef_request->Get(request);
    }

    // Remove the association between the URLRequest and this object.
    Disconnector* disconnector =
        static_cast<Disconnector*>(request->GetUserData(UserDataKey()));
    DCHECK(disconnector);
    disconnector->Disconnect();
    request->RemoveUserData(UserDataKey());

    // Only execute the callback if the request has not been canceled.
    if (request->status().status() != net::URLRequestStatus::CANCELED)
      callback.Run(allow ? net::OK : net::ERR_ABORTED);
  }

  static inline void* UserDataKey() {
    return &kLocatorKey;
  }

  CefRefPtr<CefRequestImpl> cef_request_;
  const GURL old_url_;
  GURL* new_url_;
  net::URLRequest* url_request_;
  CallbackType callback_;

  // The user data key.
  static int kLocatorKey;

  IMPLEMENT_REFCOUNTING(CefBeforeResourceLoadCallbackImpl);
  DISALLOW_COPY_AND_ASSIGN(CefBeforeResourceLoadCallbackImpl);
};

int CefBeforeResourceLoadCallbackImpl::kLocatorKey = 0;

template <typename T>
class CefCallbackHolder : public base::SupportsUserData::Data
{
public:
  CefCallbackHolder(std::shared_ptr<T> callback)
    : m_callback(std::move(callback))
  {}

  std::shared_ptr<T> m_callback;
};

class CefAuthCallbackImpl : public CefAuthCallback {
 public:
  CefAuthCallbackImpl(std::weak_ptr<net::NetworkDelegate::AuthCallback> callback,
                      net::AuthCredentials* credentials)
      : callback_(std::move(callback)),
        credentials_(credentials) {
  }
  ~CefAuthCallbackImpl() override {
    if (callback_.lock()) {
      // The auth callback is still pending. Cancel it now.
      if (CEF_CURRENTLY_ON_IOT()) {
        CancelNow(callback_);
      } else {
        CEF_POST_TASK(CEF_IOT,
            base::Bind(&CefAuthCallbackImpl::CancelNow, callback_));
      }
    }
  }

  void Continue(const CefString& username,
                const CefString& password) override {
    if (CEF_CURRENTLY_ON_IOT()) {
      auto callback = callback_.lock();
      if (callback && !callback->is_null()) {
        credentials_->Set(username, password);
        callback->Run(net::NetworkDelegate::AUTH_REQUIRED_RESPONSE_SET_AUTH);
      }
      callback_.reset();
    } else {
      CEF_POST_TASK(CEF_IOT,
          base::Bind(&CefAuthCallbackImpl::Continue, this, username, password));
    }
  }

  void Cancel() override {
    if (CEF_CURRENTLY_ON_IOT()) {
      CancelNow(callback_);
      callback_.reset();
    } else {
      CEF_POST_TASK(CEF_IOT, base::Bind(&CefAuthCallbackImpl::Cancel, this));
    }
  }

  void Disconnect() {
    callback_.reset();
  }

 private:
  static void CancelNow(std::weak_ptr<net::NetworkDelegate::AuthCallback> weak) {
    CEF_REQUIRE_IOT();
    auto callback = weak.lock();
    if (callback && !callback->is_null()) {
      callback->Run(net::NetworkDelegate::AUTH_REQUIRED_RESPONSE_NO_ACTION);
    }
  }

  std::weak_ptr<net::NetworkDelegate::AuthCallback> callback_;
  net::AuthCredentials* credentials_;

  IMPLEMENT_REFCOUNTING(CefAuthCallbackImpl);
};

}  // namespace

CefNetworkDelegate::CefNetworkDelegate() {
}

CefNetworkDelegate::~CefNetworkDelegate() {
}

int CefNetworkDelegate::OnBeforeURLRequest(
    net::URLRequest* request,
    const net::CompletionCallback& callback,
    GURL* new_url) {
  CefRefPtr<CefBrowserHostImpl> browser =
      CefBrowserHostImpl::GetBrowserForRequest(request);
  if (browser.get()) {
    const CefBrowserSettings& browser_settings = browser->settings();
    if (browser_settings.accept_language_list.length > 0) {
      const std::string& accept_language =
          net::HttpUtil::GenerateAcceptLanguageHeader(
              CefString(&browser_settings.accept_language_list));
      request->SetExtraRequestHeaderByName(
          net::HttpRequestHeaders::kAcceptLanguage, accept_language, false);
    }
    CefRefPtr<CefClient> client = browser->GetClient();
    if (client.get()) {
      CefRefPtr<CefRequestHandler> handler = client->GetRequestHandler();
      if (handler.get()) {
        CefRefPtr<CefFrame> frame = browser->GetFrameForRequest(request);

        // Populate the request data.
        CefRefPtr<CefRequestImpl> requestPtr(new CefRequestImpl());
        requestPtr->Set(request);

        CefRefPtr<CefBeforeResourceLoadCallbackImpl> callbackImpl(
            new CefBeforeResourceLoadCallbackImpl(requestPtr, new_url, request,
                                                  callback));

        // Give the client an opportunity to evaluate the request.
        cef_return_value_t retval = handler->OnBeforeResourceLoad(
            browser.get(), frame, requestPtr.get(), callbackImpl.get());
        if (retval == RV_CANCEL) {
          // Cancel the request.
          callbackImpl->Continue(false);
        } else if (retval == RV_CONTINUE) {
          // Continue the request.
          callbackImpl->Continue(true);
        }

        // Continue or cancel the request asynchronously.
        return net::ERR_IO_PENDING;
      }
    }
  }

  // Continue the request immediately.
  return net::OK;
}

net::NetworkDelegate::AuthRequiredResponse CefNetworkDelegate::OnAuthRequired(
    net::URLRequest* request,
    const net::AuthChallengeInfo& auth_info,
    const AuthCallback& callback,
    net::AuthCredentials* credentials) {
  CefRefPtr<CefBrowserHostImpl> browser =
      CefBrowserHostImpl::GetBrowserForRequest(request);
  if (browser.get()) {
    CefRefPtr<CefClient> client = browser->GetClient();
    if (client.get()) {
      CefRefPtr<CefRequestHandler> handler = client->GetRequestHandler();
      if (handler.get()) {
        CefRefPtr<CefFrame> frame = browser->GetFrameForRequest(request);

        auto callback_shared = std::make_shared<AuthCallback>(callback);
        CefRefPtr<CefAuthCallbackImpl> callbackPtr(
            new CefAuthCallbackImpl(callback_shared, credentials));
        request->SetUserData("CefNetworkDelegate", new CefCallbackHolder<AuthCallback>(
                               std::move(callback_shared)));
        if (handler->GetAuthCredentials(browser.get(),
                                        frame,
                                        auth_info.is_proxy,
                                        auth_info.challenger.host(),
                                        auth_info.challenger.port(),
                                        auth_info.realm,
                                        auth_info.scheme,
                                        callbackPtr.get())) {
          return AUTH_REQUIRED_RESPONSE_IO_PENDING;
        } else {
          callbackPtr->Disconnect();
        }
      }
    }
  }

  CefURLRequestUserData* user_data =
      (CefURLRequestUserData*)request->GetUserData(
          CefURLRequestUserData::kUserDataKey);
  if (user_data) {
    CefRefPtr<CefURLRequestClient> client = user_data->GetClient();
    if (client.get()) {
      auto callback_shared = std::make_shared<AuthCallback>(callback);
      CefRefPtr<CefAuthCallbackImpl> callbackPtr(
          new CefAuthCallbackImpl(callback_shared, credentials));
      request->SetUserData("CefNetworkDelegate", new CefCallbackHolder<AuthCallback>(
                             std::move(callback_shared)));
      if (client->GetAuthCredentials(auth_info.is_proxy,
                                     auth_info.challenger.host(),
                                     auth_info.challenger.port(),
                                     auth_info.realm,
                                     auth_info.scheme,
                                     callbackPtr.get())) {
        return AUTH_REQUIRED_RESPONSE_IO_PENDING;
      } else {
        callbackPtr->Disconnect();
      }
    }
  }

  return AUTH_REQUIRED_RESPONSE_NO_ACTION;
}

bool CefNetworkDelegate::OnCanAccessFile(const net::URLRequest& request,
                                         const base::FilePath& path) const {
  return true;
}
