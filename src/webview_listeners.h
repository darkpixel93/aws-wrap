#ifndef _WEBVIEWLISTENER_H_
#define _WEBVIEWLISTENER_H_

#include "wrap_core.h"
#include <Awesomium/WebView.h>
#include <Awesomium/WebString.h>
#include <Awesomium/WebStringArray.h>
#include <Awesomium/WebViewListener.h>

#include <map>

using namespace Awesomium;

typedef std::map<Awesomium::WebView*, cWebView_View> viewCallbacks_t;


class WebViewListener_View : public Awesomium::WebViewListener::View
{
public:


	/// This event occurs when the page title has changed.
	virtual void OnChangeTitle(Awesomium::WebView* caller,
		const Awesomium::WebString& title);

	/// This event occurs when the page URL has changed.
	virtual void OnChangeAddressBar(Awesomium::WebView* caller,
		const Awesomium::WebURL& url);

	/// This event occurs when the tooltip text has changed. You
	/// should hide the tooltip when the text is empty.
	virtual void OnChangeTooltip(Awesomium::WebView* caller,
		const Awesomium::WebString& tooltip);

	/// This event occurs when the target URL has changed. This
	/// is usually the result of hovering over a link on a page.
	virtual void OnChangeTargetURL(Awesomium::WebView* caller,
		const Awesomium::WebURL& url);

	/// This event occurs when the cursor has changed. This is
	/// is usually the result of hovering over different content.
	virtual void OnChangeCursor(Awesomium::WebView* caller,
		Awesomium::Cursor cursor);

	/// This event occurs when the focused element changes on the page.
	/// This is usually the result of textbox being focused or some other
	/// user-interaction event.
	virtual void OnChangeFocus(Awesomium::WebView* caller,
		Awesomium::FocusedElementType focused_type);

	/// This event occurs when a WebView creates a new child WebView
	/// (usually the result of window.open or an external link). It
	/// is your responsibility to display this child WebView in your
	/// application. You should call Resize on the child WebView
	/// immediately after this event to make it match your container
	/// size.
	///
	/// If this is a child of a Windowed WebView, you should call
	/// WebView::set_parent_window on the new view immediately within
	/// this event.
	///
	virtual void OnShowCreatedWebView(Awesomium::WebView* caller,
		Awesomium::WebView* new_view,
		const Awesomium::WebURL& opener_url,
		const Awesomium::WebURL& target_url,
		const Awesomium::Rect& initial_pos,
		bool is_popup);

	void addCallback(Awesomium::WebView* view, cWebView_View clbk);

	void removeCallback(Awesomium::WebView* view);

protected:
	viewCallbacks_t callbacks;
};



///
/// @brief  An interface that you can use to handle all page-loading
///         events for a certain WebView.
///
/// @note: See WebView::SetLoadListener
///
class WebViewListener_Load : public Awesomium::WebViewListener::Load {
 public:
  /// This event occurs when the page begins loading a frame.
  virtual void OnBeginLoadingFrame(Awesomium::WebView* caller,
                                   int64 frame_id,
                                   bool is_main_frame,
                                   const Awesomium::WebURL& url,
                                   bool is_error_page);

  /// This event occurs when a frame fails to load. See error_desc
  /// for additional information.
  virtual void OnFailLoadingFrame(Awesomium::WebView* caller,
                                  int64 frame_id,
                                  bool is_main_frame,
                                  const Awesomium::WebURL& url,
                                  int error_code,
                                  const Awesomium::WebString& error_desc);

  /// This event occurs when the page finishes loading a frame.
  /// The main frame always finishes loading last for a given page load.
  virtual void OnFinishLoadingFrame(Awesomium::WebView* caller,
                                    int64 frame_id,
                                    bool is_main_frame,
                                    const Awesomium::WebURL& url) ;

  /// This event occurs when the DOM has finished parsing and the
  /// window object is available for JavaScript execution.
  virtual void OnDocumentReady(Awesomium::WebView* caller,
                               const Awesomium::WebURL& url);

 protected:
	 virtual ~WebViewListener_Load() {}
};

///
/// @brief  An interface that you can use to handle all process-related
///         events for a certain WebView.
///
/// Each WebView has an associated "render" process, you can use these events
/// to recover from crashes or hangs).
///
/// @note  See WebView::set_process_listener
///
class WebViewListener_Process : public Awesomium::WebViewListener::Process {
 public:
  /// This event occurs when the process hangs.
  virtual void OnUnresponsive(Awesomium::WebView* caller);

  /// This event occurs when the process becomes responsive after
  /// a hang.
  virtual void OnResponsive(Awesomium::WebView* caller);

  /// This event occurs when the process crashes.
  virtual void OnCrashed(Awesomium::WebView* caller,
                         Awesomium::TerminationStatus status);
 protected:
  virtual ~WebViewListener_Process() {}
};

///
/// @brief  An interface that you can use to handle all menu-related events
///         for a certain WebView.
///
/// @note  See WebView::set_menu_listener
///
class WebViewListener_Menu : public Awesomium::WebViewListener::Menu {
 public:
  ///
  /// This event occurs when the page requests to display a dropdown
  /// (popup) menu. This is usually the result of a user clicking on
  /// a "select" HTML input element. It is your responsibility to
  /// display this menu in your application. This event is not modal.
  ///
  /// @see WebView::DidSelectPopupMenuItem
  /// @see WebView::DidCancelPopupMenu
  ///
  virtual void OnShowPopupMenu(Awesomium::WebView* caller,
                               const WebPopupMenuInfo& menu_info);

  ///
  /// This event occurs when the page requests to display a context menu.
  /// This is usually the result of a user right-clicking somewhere on the
  /// page. It is your responsibility to display this menu in your
  /// application and perform the selected actions. This event is not modal.
  ///
  virtual void OnShowContextMenu(Awesomium::WebView* caller,
                                 const WebContextMenuInfo& menu_info);
 protected:
  virtual ~WebViewListener_Menu() {}
};

///
/// @brief  An interface that you can use to handle all dialog-related events
///         for a certain WebView.
///
/// @see  WebView::set_dialog_listener
///
class WebViewListener_Dialog : public Awesomium::WebViewListener::Dialog {
 public:
  ///
  /// This event occurs when the page requests to display a file chooser
  /// dialog. This is usually the result of a user clicking on an HTML
  /// input element with `type='file`. It is your responsibility to display
  /// this menu in your application. This event is not modal.
  ///
  /// @see WebView::DidChooseFiles
  ///
  virtual void OnShowFileChooser(Awesomium::WebView* caller,
                                 const WebFileChooserInfo& chooser_info);

  ///
  /// This event occurs when the page needs authentication from the user (for
  /// example, Basic HTTP Auth, NTLM Auth, etc). It is your responsibility to
  /// display a dialog so that users can input their username and password.
  /// This event is not modal.
  ///
  /// @see WebView::DidLogin
  /// @see WebView::DidCancelLogin
  ///
  virtual void OnShowLoginDialog(Awesomium::WebView* caller,
                                 const WebLoginDialogInfo& dialog_info);

 protected:
  virtual ~WebViewListener_Dialog() {}
};

///
/// @brief  An interface that you can use to handle all print-related events
///         for a certain WebView.
///
/// @see  WebView::set_print_listener
///
class WebViewListener_Print : public Awesomium::WebViewListener::Print {
 public:
  ///
  /// This event occurs when the page requests to print itself. (Usually
  /// the result of `window.print()` being called from JavaScript.) It is
  /// your responsiblity to print the WebView to a file and handle the
  /// actual device printing.
  ///
  /// @see  WebView::PrintToFile
  ///
  virtual void OnRequestPrint(Awesomium::WebView* caller);

  ///
  /// This event occurs when WebView::PrintToFile fails. Typically because of
  /// bad printer configuration or invalid output path (it must be writable).
  ///
  /// @param  request_id  The unique request ID (returned from
  ///                     WebView::PrintToFile earlier).
  ///
  virtual void OnFailPrint(Awesomium::WebView* caller,
                           int request_id);

  ///
  /// This event occurs when WebView::PrintToFile succeeds.
  ///
  /// @param  request_id  The unique request ID (returned from
  ///                     WebView::PrintToFile earlier).
  ///
  /// @param  file_list  The list of file-paths written. There may be multiple
  ///                    files written if split_pages_into_multiple_files was
  ///                    set to true in PrintConfig.
  ///
  virtual void OnFinishPrint(Awesomium::WebView* caller,
                             int request_id,
                             const WebStringArray& file_list);

 protected:
  virtual ~WebViewListener_Print() {}
};

///
/// @brief  An interface that you can use to handle all download-related events
///         for a certain WebView.
///
/// @see  WebView::set_download_listener
///
class WebViewListener_Download : public Awesomium::WebViewListener::Download {
 public:
  ///
  /// This event occurs when the page requests to begin downloading a certain
  /// file. It is your responsiblity to call WebView::DidChooseDownloadPath or
  /// WebView::DidCancelDownload as a result of this event.
  ///
  /// @param  download_id  The unique ID of the download.
  ///
  /// @param  url  The URL that initiated the download.
  ///
  /// @param  suggested_filename  The suggested name for the file.
  ///
  /// @param  mime_type  The mime type of the file.
  ///
  virtual void OnRequestDownload(Awesomium::WebView* caller,
                                 int download_id,
                                 const Awesomium::WebURL& url,
                                 const Awesomium::WebString& suggested_filename,
                                 const Awesomium::WebString& mime_type);

  ///
  /// This event occurs when the progress of the download is updated.
  ///
  /// @param  download_id  The unique ID of the download.
  ///
  /// @param  total_bytes  The total number of bytes (may be 0 if unknown).
  ///
  /// @param  received_bytes  The number of bytes received so far.
  ///
  /// @param  current_speed  The current speed in bytes per second.
  ///
  virtual void OnUpdateDownload(Awesomium::WebView* caller,
                                int download_id,
                                int64 total_bytes,
                                int64 received_bytes,
                                int64 current_speed);

  ///
  /// This event occurs when the download is finished.
  ///
  /// @param  download_id  The unique ID of the download.
  ///
  /// @param  url  The URL that initiated the download.
  ///
  /// @param  saved_path  The path that the download was saved to.
  ///
  virtual void OnFinishDownload(Awesomium::WebView* caller,
                                int download_id,
                                const Awesomium::WebURL& url,
                                const Awesomium::WebString& saved_path);

 protected:
  virtual ~WebViewListener_Download() {}
};

///
/// @brief  An interface that you can use to handle all IME-related events
///         for a certain WebView.
///
/// @see  WebView::set_input_method_editor_listener
///
class WebViewListener_IME : public Awesomium::WebViewListener::InputMethodEditor {
 public:
  ///
  /// You should handle this message if you are displaying your
  /// own IME (input method editor) widget.
  ///
  /// This event is fired whenever the user does something that may change
  /// the position, visiblity, or type of the IME Widget. This event is only
  /// active when IME is active (please see WebView::ActivateIME).
  ///
  /// @param  caller  The WebView that fired this event.
  ///
  /// @param  type  The type of IME widget that should be displayed (if any).
  ///
  /// @param  caret_x  The x-position of the caret (relative to the View).
  /// @param  caret_y  The y-position of the caret (relative to the View).
  ///
  virtual void OnUpdateIME(Awesomium::WebView* caller,
                           Awesomium::TextInputType type,
                           int caret_x,
                           int caret_y);

  ///
  /// This event is fired when the page cancels the IME composition.
  ///
  virtual void OnCancelIME(Awesomium::WebView* caller);

  ///
  /// This event is fired when the page changes the displayed range
  /// of the IME composition.
  ///
  virtual void OnChangeIMERange(Awesomium::WebView* caller,
                                unsigned int start,
                                unsigned int end);

 protected:
  virtual ~WebViewListener_IME() {}
};

#endif