// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "libcef/browser/extensions/event_router_forwarder.h"

#include "libcef/browser/browser_context_impl.h"

#include "base/bind.h"
#include "base/values.h"
#include "content/public/browser/browser_thread.h"
#include "extensions/browser/event_router.h"
#include "url/gurl.h"

using content::BrowserThread;

namespace extensions {

EventRouterForwarder::EventRouterForwarder() {
}

EventRouterForwarder::~EventRouterForwarder() {
}

void EventRouterForwarder::BroadcastEventToRenderers(
    const std::string& event_name,
    scoped_ptr<base::ListValue> event_args,
    const GURL& event_url) {
  HandleEvent(std::string(), event_name, event_args.Pass(), 0, true, event_url);
}

void EventRouterForwarder::DispatchEventToRenderers(
    const std::string& event_name,
    scoped_ptr<base::ListValue> event_args,
    void* profile,
    bool use_profile_to_restrict_events,
    const GURL& event_url) {
  if (!profile)
    return;
  HandleEvent(std::string(),
              event_name,
              event_args.Pass(),
              profile,
              use_profile_to_restrict_events,
              event_url);
}

void EventRouterForwarder::BroadcastEventToExtension(
    const std::string& extension_id,
    const std::string& event_name,
    scoped_ptr<base::ListValue> event_args,
    const GURL& event_url) {
  HandleEvent(extension_id, event_name, event_args.Pass(), 0, true, event_url);
}

void EventRouterForwarder::DispatchEventToExtension(
    const std::string& extension_id,
    const std::string& event_name,
    scoped_ptr<base::ListValue> event_args,
    void* profile,
    bool use_profile_to_restrict_events,
    const GURL& event_url) {
  if (!profile)
    return;
  HandleEvent(extension_id, event_name, event_args.Pass(), profile,
              use_profile_to_restrict_events, event_url);
}

void EventRouterForwarder::HandleEvent(const std::string& extension_id,
                                       const std::string& event_name,
                                       scoped_ptr<base::ListValue> event_args,
                                       void* profile_ptr,
                                       bool use_profile_to_restrict_events,
                                       const GURL& event_url) {
  if (!BrowserThread::CurrentlyOn(BrowserThread::UI)) {
    BrowserThread::PostTask(
        BrowserThread::UI, FROM_HERE,
        base::Bind(&EventRouterForwarder::HandleEvent, this,
                   extension_id, event_name, base::Passed(&event_args),
                   profile_ptr, use_profile_to_restrict_events, event_url));
    return;
  }

  content::BrowserContext* profile = NULL;
  if (profile_ptr) {
    profile = reinterpret_cast<content::BrowserContext*>(profile_ptr);
    if (CefBrowserContextImpl::GetForContext(profile) == NULL)
      return;
  }
  if (profile) {
    CallEventRouter(profile, extension_id, event_name, event_args.Pass(),
                    use_profile_to_restrict_events ? profile : NULL, event_url);
  } else {
    std::vector<CefBrowserContextImpl*> profiles(
        CefBrowserContextImpl::GetAll());
    for (size_t i = 0; i < profiles.size(); ++i) {
      scoped_ptr<base::ListValue> per_profile_event_args(
          event_args->DeepCopy());
      CallEventRouter(
          profiles[i], extension_id, event_name, per_profile_event_args.Pass(),
          use_profile_to_restrict_events ? profiles[i] : NULL, event_url);
    }
  }
}

void EventRouterForwarder::CallEventRouter(
    content::BrowserContext* profile,
    const std::string& extension_id,
    const std::string& event_name,
    scoped_ptr<base::ListValue> event_args,
    content::BrowserContext* restrict_to_profile,
    const GURL& event_url) {
  scoped_ptr<Event> event(
      new Event(events::UNKNOWN, event_name, event_args.Pass()));
  event->restrict_to_browser_context = restrict_to_profile;
  event->event_url = event_url;
  if (extension_id.empty()) {
    extensions::EventRouter::Get(profile)->BroadcastEvent(event.Pass());
  } else {
    extensions::EventRouter::Get(profile)
        ->DispatchEventToExtension(extension_id, event.Pass());
  }
}

}  // namespace extensions
