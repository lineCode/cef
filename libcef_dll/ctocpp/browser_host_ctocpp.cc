// Copyright (c) 2015 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "libcef_dll/cpptoc/client_cpptoc.h"
#include "libcef_dll/cpptoc/navigation_entry_visitor_cpptoc.h"
#include "libcef_dll/cpptoc/run_file_dialog_callback_cpptoc.h"
#include "libcef_dll/ctocpp/browser_ctocpp.h"
#include "libcef_dll/ctocpp/browser_host_ctocpp.h"
#include "libcef_dll/ctocpp/drag_data_ctocpp.h"
#include "libcef_dll/ctocpp/request_context_ctocpp.h"
#include "libcef_dll/transfer_util.h"


// STATIC METHODS - Body may be edited by hand.

bool CefBrowserHost::CreateBrowser(const CefWindowInfo& windowInfo,
    CefRefPtr<CefClient> client, const CefString& url,
    const CefBrowserSettings& settings,
    CefRefPtr<CefRequestContext> request_context) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: client, url, request_context

  // Execute
  int _retval = cef_browser_host_create_browser(
      &windowInfo,
      CefClientCppToC::Wrap(client),
      url.GetStruct(),
      &settings,
      CefRequestContextCToCpp::Unwrap(request_context));

  // Return type: bool
  return _retval?true:false;
}

CefRefPtr<CefBrowser> CefBrowserHost::CreateBrowserSync(
    const CefWindowInfo& windowInfo, CefRefPtr<CefClient> client,
    const CefString& url, const CefBrowserSettings& settings,
    CefRefPtr<CefRequestContext> request_context) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: client, url, request_context

  // Execute
  cef_browser_t* _retval = cef_browser_host_create_browser_sync(
      &windowInfo,
      CefClientCppToC::Wrap(client),
      url.GetStruct(),
      &settings,
      CefRequestContextCToCpp::Unwrap(request_context));

  // Return type: refptr_same
  return CefBrowserCToCpp::Wrap(_retval);
}


// VIRTUAL METHODS - Body may be edited by hand.

CefRefPtr<CefBrowser> CefBrowserHostCToCpp::GetBrowser() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_browser))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_browser_t* _retval = _struct->get_browser(_struct);

  // Return type: refptr_same
  return CefBrowserCToCpp::Wrap(_retval);
}

void CefBrowserHostCToCpp::CloseBrowser(bool force_close) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, close_browser))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->close_browser(_struct,
      force_close);
}

void CefBrowserHostCToCpp::SetFocus(bool focus) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_focus))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->set_focus(_struct,
      focus);
}

void CefBrowserHostCToCpp::SetWindowVisibility(bool visible) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_window_visibility))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->set_window_visibility(_struct,
      visible);
}

CefWindowHandle CefBrowserHostCToCpp::GetWindowHandle() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_window_handle))
    return kNullWindowHandle;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_window_handle_t _retval = _struct->get_window_handle(_struct);

  // Return type: simple
  return _retval;
}

CefWindowHandle CefBrowserHostCToCpp::GetOpenerWindowHandle() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_opener_window_handle))
    return kNullWindowHandle;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_window_handle_t _retval = _struct->get_opener_window_handle(_struct);

  // Return type: simple
  return _retval;
}

CefRefPtr<CefClient> CefBrowserHostCToCpp::GetClient() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_client))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_client_t* _retval = _struct->get_client(_struct);

  // Return type: refptr_diff
  return CefClientCppToC::Unwrap(_retval);
}

CefRefPtr<CefRequestContext> CefBrowserHostCToCpp::GetRequestContext() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_request_context))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_request_context_t* _retval = _struct->get_request_context(_struct);

  // Return type: refptr_same
  return CefRequestContextCToCpp::Wrap(_retval);
}

double CefBrowserHostCToCpp::GetZoomLevel() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_zoom_level))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  double _retval = _struct->get_zoom_level(_struct);

  // Return type: simple
  return _retval;
}

void CefBrowserHostCToCpp::SetZoomLevel(double zoomLevel) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_zoom_level))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->set_zoom_level(_struct,
      zoomLevel);
}

void CefBrowserHostCToCpp::RunFileDialog(FileDialogMode mode,
    const CefString& title, const CefString& default_file_path,
    const std::vector<CefString>& accept_filters, int selected_accept_filter,
    CefRefPtr<CefRunFileDialogCallback> callback) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, run_file_dialog))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: selected_accept_filter; type: simple_byval
  DCHECK_GE(selected_accept_filter, 0);
  if (selected_accept_filter < 0)
    return;
  // Verify param: callback; type: refptr_diff
  DCHECK(callback.get());
  if (!callback.get())
    return;
  // Unverified params: title, default_file_path, accept_filters

  // Translate param: accept_filters; type: string_vec_byref_const
  cef_string_list_t accept_filtersList = cef_string_list_alloc();
  DCHECK(accept_filtersList);
  if (accept_filtersList)
    transfer_string_list_contents(accept_filters, accept_filtersList);

  // Execute
  _struct->run_file_dialog(_struct,
      mode,
      title.GetStruct(),
      default_file_path.GetStruct(),
      accept_filtersList,
      selected_accept_filter,
      CefRunFileDialogCallbackCppToC::Wrap(callback));

  // Restore param:accept_filters; type: string_vec_byref_const
  if (accept_filtersList)
    cef_string_list_free(accept_filtersList);
}

void CefBrowserHostCToCpp::StartDownload(const CefString& url) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, start_download))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: url; type: string_byref_const
  DCHECK(!url.empty());
  if (url.empty())
    return;

  // Execute
  _struct->start_download(_struct,
      url.GetStruct());
}

void CefBrowserHostCToCpp::Print() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, print))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->print(_struct);
}

void CefBrowserHostCToCpp::Find(int identifier, const CefString& searchText,
    bool forward, bool matchCase, bool findNext) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, find))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: searchText; type: string_byref_const
  DCHECK(!searchText.empty());
  if (searchText.empty())
    return;

  // Execute
  _struct->find(_struct,
      identifier,
      searchText.GetStruct(),
      forward,
      matchCase,
      findNext);
}

void CefBrowserHostCToCpp::StopFinding(bool clearSelection) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, stop_finding))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->stop_finding(_struct,
      clearSelection);
}

void CefBrowserHostCToCpp::ShowDevTools(const CefWindowInfo& windowInfo,
    CefRefPtr<CefClient> client, const CefBrowserSettings& settings,
    const CefPoint& inspect_element_at) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, show_dev_tools))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: client; type: refptr_diff
  DCHECK(client.get());
  if (!client.get())
    return;
  // Unverified params: inspect_element_at

  // Execute
  _struct->show_dev_tools(_struct,
      &windowInfo,
      CefClientCppToC::Wrap(client),
      &settings,
      &inspect_element_at);
}

void CefBrowserHostCToCpp::CloseDevTools() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, close_dev_tools))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->close_dev_tools(_struct);
}

void CefBrowserHostCToCpp::GetNavigationEntries(
    CefRefPtr<CefNavigationEntryVisitor> visitor, bool current_only) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_navigation_entries))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: visitor; type: refptr_diff
  DCHECK(visitor.get());
  if (!visitor.get())
    return;

  // Execute
  _struct->get_navigation_entries(_struct,
      CefNavigationEntryVisitorCppToC::Wrap(visitor),
      current_only);
}

void CefBrowserHostCToCpp::SetMouseCursorChangeDisabled(bool disabled) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_mouse_cursor_change_disabled))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->set_mouse_cursor_change_disabled(_struct,
      disabled);
}

bool CefBrowserHostCToCpp::IsMouseCursorChangeDisabled() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, is_mouse_cursor_change_disabled))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_mouse_cursor_change_disabled(_struct);

  // Return type: bool
  return _retval?true:false;
}

void CefBrowserHostCToCpp::ReplaceMisspelling(const CefString& word) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, replace_misspelling))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: word; type: string_byref_const
  DCHECK(!word.empty());
  if (word.empty())
    return;

  // Execute
  _struct->replace_misspelling(_struct,
      word.GetStruct());
}

void CefBrowserHostCToCpp::AddWordToDictionary(const CefString& word) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, add_word_to_dictionary))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: word; type: string_byref_const
  DCHECK(!word.empty());
  if (word.empty())
    return;

  // Execute
  _struct->add_word_to_dictionary(_struct,
      word.GetStruct());
}

bool CefBrowserHostCToCpp::IsWindowRenderingDisabled() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, is_window_rendering_disabled))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_window_rendering_disabled(_struct);

  // Return type: bool
  return _retval?true:false;
}

void CefBrowserHostCToCpp::WasResized() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, was_resized))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->was_resized(_struct);
}

void CefBrowserHostCToCpp::WasHidden(bool hidden) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, was_hidden))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->was_hidden(_struct,
      hidden);
}

void CefBrowserHostCToCpp::NotifyScreenInfoChanged() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, notify_screen_info_changed))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->notify_screen_info_changed(_struct);
}

void CefBrowserHostCToCpp::Invalidate(PaintElementType type) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, invalidate))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->invalidate(_struct,
      type);
}

void CefBrowserHostCToCpp::SendKeyEvent(const CefKeyEvent& event) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, send_key_event))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->send_key_event(_struct,
      &event);
}

void CefBrowserHostCToCpp::SendMouseClickEvent(const CefMouseEvent& event,
    MouseButtonType type, bool mouseUp, int clickCount) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, send_mouse_click_event))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->send_mouse_click_event(_struct,
      &event,
      type,
      mouseUp,
      clickCount);
}

void CefBrowserHostCToCpp::SendMouseMoveEvent(const CefMouseEvent& event,
    bool mouseLeave) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, send_mouse_move_event))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->send_mouse_move_event(_struct,
      &event,
      mouseLeave);
}

void CefBrowserHostCToCpp::SendMouseWheelEvent(const CefMouseEvent& event,
    int deltaX, int deltaY) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, send_mouse_wheel_event))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->send_mouse_wheel_event(_struct,
      &event,
      deltaX,
      deltaY);
}

void CefBrowserHostCToCpp::SendTouchEvent(const CefTouchEvent& event) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, send_touch_event))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->send_touch_event(_struct,
      &event);
}

void CefBrowserHostCToCpp::SendFocusEvent(bool setFocus) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, send_focus_event))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->send_focus_event(_struct,
      setFocus);
}

void CefBrowserHostCToCpp::SendCaptureLostEvent() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, send_capture_lost_event))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->send_capture_lost_event(_struct);
}

void CefBrowserHostCToCpp::NotifyMoveOrResizeStarted() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, notify_move_or_resize_started))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->notify_move_or_resize_started(_struct);
}

int CefBrowserHostCToCpp::GetWindowlessFrameRate() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_windowless_frame_rate))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->get_windowless_frame_rate(_struct);

  // Return type: simple
  return _retval;
}

void CefBrowserHostCToCpp::SetWindowlessFrameRate(int frame_rate) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_windowless_frame_rate))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->set_windowless_frame_rate(_struct,
      frame_rate);
}

CefTextInputContext CefBrowserHostCToCpp::GetNSTextInputContext() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_nstext_input_context))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_text_input_context_t _retval = _struct->get_nstext_input_context(_struct);

  // Return type: simple
  return _retval;
}

void CefBrowserHostCToCpp::HandleKeyEventBeforeTextInputClient(
    CefEventHandle keyEvent) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, handle_key_event_before_text_input_client))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->handle_key_event_before_text_input_client(_struct,
      keyEvent);
}

void CefBrowserHostCToCpp::HandleKeyEventAfterTextInputClient(
    CefEventHandle keyEvent) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, handle_key_event_after_text_input_client))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->handle_key_event_after_text_input_client(_struct,
      keyEvent);
}

void CefBrowserHostCToCpp::DragTargetDragEnter(CefRefPtr<CefDragData> drag_data,
    const CefMouseEvent& event, DragOperationsMask allowed_ops) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, drag_target_drag_enter))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: drag_data; type: refptr_same
  DCHECK(drag_data.get());
  if (!drag_data.get())
    return;

  // Execute
  _struct->drag_target_drag_enter(_struct,
      CefDragDataCToCpp::Unwrap(drag_data),
      &event,
      allowed_ops);
}

void CefBrowserHostCToCpp::DragTargetDragOver(const CefMouseEvent& event,
    DragOperationsMask allowed_ops) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, drag_target_drag_over))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->drag_target_drag_over(_struct,
      &event,
      allowed_ops);
}

void CefBrowserHostCToCpp::DragTargetDragLeave() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, drag_target_drag_leave))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->drag_target_drag_leave(_struct);
}

void CefBrowserHostCToCpp::DragTargetDrop(const CefMouseEvent& event) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, drag_target_drop))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->drag_target_drop(_struct,
      &event);
}

void CefBrowserHostCToCpp::DragSourceEndedAt(int x, int y,
    DragOperationsMask op) {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, drag_source_ended_at))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->drag_source_ended_at(_struct,
      x,
      y,
      op);
}

void CefBrowserHostCToCpp::DragSourceSystemDragEnded() {
  cef_browser_host_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, drag_source_system_drag_ended))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->drag_source_system_drag_ended(_struct);
}


// CONSTRUCTOR - Do not edit by hand.

CefBrowserHostCToCpp::CefBrowserHostCToCpp() {
}

template<> cef_browser_host_t* CefCToCpp<CefBrowserHostCToCpp, CefBrowserHost,
    cef_browser_host_t>::UnwrapDerived(CefWrapperType type,
    CefBrowserHost* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#ifndef NDEBUG
template<> base::AtomicRefCount CefCToCpp<CefBrowserHostCToCpp, CefBrowserHost,
    cef_browser_host_t>::DebugObjCt = 0;
#endif

template<> CefWrapperType CefCToCpp<CefBrowserHostCToCpp, CefBrowserHost,
    cef_browser_host_t>::kWrapperType = WT_BROWSER_HOST;
