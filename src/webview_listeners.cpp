#include "webview_listeners.h"


/// This event occurs when the page title has changed.
	 void WebViewListener_View::OnChangeTitle(Awesomium::WebView* caller,
		const Awesomium::WebString& title)
	 {
		 auto cb = callbacks.find(caller);
		 if ( cb != callbacks.end() )
		 {
			 cb->second.tooltip(
					reinterpret_cast<cWebViewPtr_t>(caller),
					reinterpret_cast<const cWebStringPtr_t&>(title),
					cb->second.userPointer
				);
		 }
	 }

	/// This event occurs when the page URL has changed.
	 void WebViewListener_View::OnChangeAddressBar(Awesomium::WebView* caller,
		const Awesomium::WebURL& url)
	 {
		 auto cb = callbacks.find(caller);
		 if ( cb != callbacks.end() )
		 {
			 cb->second.address(
					reinterpret_cast<cWebViewPtr_t>(caller),
					reinterpret_cast<const cWebUrlPtr_t&>(url),
					cb->second.userPointer
				);
		 }
	 }

	/// This event occurs when the tooltip text has changed. You
	/// should hide the tooltip when the text is empty.
	 void WebViewListener_View::OnChangeTooltip(Awesomium::WebView* caller,
		const Awesomium::WebString& tooltip)
	 {
		 auto cb = callbacks.find(caller);
		 if ( cb != callbacks.end() )
		 {
			 cb->second.tooltip(
					reinterpret_cast<cWebViewPtr_t>(caller),
					reinterpret_cast<const cWebStringPtr_t&>(tooltip),
					cb->second.userPointer
				);
		 }
	 }

	/// This event occurs when the target URL has changed. This
	/// is usually the result of hovering over a link on a page.
	 void WebViewListener_View::OnChangeTargetURL(Awesomium::WebView* caller,
		const Awesomium::WebURL& url)
	 {
		 auto cb = callbacks.find(caller);
		 if ( cb != callbacks.end() )
		 {
			 cb->second.url(
					reinterpret_cast<cWebViewPtr_t>(caller),
					reinterpret_cast<const cWebUrlPtr_t&>(url),
					cb->second.userPointer
				);
		 }
	 }

	/// This event occurs when the cursor has changed. This is
	/// is usually the result of hovering over different content.
	 void WebViewListener_View::OnChangeCursor(Awesomium::WebView* caller,
		Awesomium::Cursor cursor)
	 {
		 auto cb = callbacks.find(caller);
		 if ( cb != callbacks.end() )
		 {
			 cb->second.cursor(
					reinterpret_cast<cWebViewPtr_t>(caller),
					cursor,
					cb->second.userPointer
				);
		 }
	 }

	/// This event occurs when the focused element changes on the page.
	/// This is usually the result of textbox being focused or some other
	/// user-interaction event.
	 void WebViewListener_View::OnChangeFocus(Awesomium::WebView* caller,
		Awesomium::FocusedElementType focused_type)
	 {
		 auto cb = callbacks.find(caller);
		 if ( cb != callbacks.end() )
		 {
			 cb->second.focus(
					reinterpret_cast<cWebViewPtr_t>(caller),
					focused_type,
					cb->second.userPointer
				);
		 }
	 }

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
	 void WebViewListener_View::OnShowCreatedWebView(Awesomium::WebView* caller,
		Awesomium::WebView* new_view,
		const Awesomium::WebURL& opener_url,
		const Awesomium::WebURL& target_url,
		const Awesomium::Rect& initial_pos,
		bool is_popup)
	 {
		 auto cb = callbacks.find(caller);
		 if ( cb != callbacks.end() )
		 {
			 cRect rect;

			 rect.x = initial_pos.x;
			 rect.y = initial_pos.y;
			 rect.width = initial_pos.width;
			 rect.height = initial_pos.height;

			 // i'm not sure about this casts ...
			 cb->second.show(
					reinterpret_cast<cWebViewPtr_t>(caller),
					reinterpret_cast<cWebViewPtr_t>(new_view),
					reinterpret_cast<const cWebUrlPtr_t&>(opener_url),
					reinterpret_cast<const cWebUrlPtr_t&>(target_url),
					rect,
					is_popup,
					cb->second.userPointer
				);
		 }
	 }

	void WebViewListener_View::addCallback(Awesomium::WebView* view, cWebView_View clbk)
	{
		callbacks.emplace(view, clbk);
	}

	void WebViewListener_View::removeCallback(Awesomium::WebView* view)
	{
		auto cb = callbacks.find(view);

		if  ( cb != callbacks.end() )
		{
			callbacks.erase(cb);
		}
	}


	 // ------------------ LOAD -------------------------



  /// This event occurs when the page begins loading a frame.
   void WebViewListener_Load::OnBeginLoadingFrame(Awesomium::WebView* caller,
                                   int64 frame_id,
                                   bool is_main_frame,
                                   const Awesomium::WebURL& url,
                                   bool is_error_page)
   {

   }

  /// This event occurs when a frame fails to load. See error_desc
  /// for additional information.
   void WebViewListener_Load::OnFailLoadingFrame(Awesomium::WebView* caller,
                                  int64 frame_id,
                                  bool is_main_frame,
                                  const Awesomium::WebURL& url,
                                  int error_code,
                                  const Awesomium::WebString& error_desc)
   {

   }

  /// This event occurs when the page finishes loading a frame.
  /// The main frame always finishes loading last for a given page load.
   void WebViewListener_Load::OnFinishLoadingFrame(Awesomium::WebView* caller,
                                    int64 frame_id,
                                    bool is_main_frame,
                                    const Awesomium::WebURL& url)
   {

   }

  /// This event occurs when the DOM has finished parsing and the
  /// window object is available for JavaScript execution.
   void WebViewListener_Load::OnDocumentReady(Awesomium::WebView* caller,
                               const Awesomium::WebURL& url)
   {

   }


  /// This event occurs when the process hangs.
   void WebViewListener_Process::OnUnresponsive(Awesomium::WebView* caller)
   {

   }

  /// This event occurs when the process becomes responsive after
  /// a hang.
   void WebViewListener_Process::OnResponsive(Awesomium::WebView* caller)
   {

   }

  /// This event occurs when the process crashes.
   void WebViewListener_Process::OnCrashed(Awesomium::WebView* caller,
                         Awesomium::TerminationStatus status)
   {

   }


  ///
  /// This event occurs when the page requests to display a dropdown
  /// (popup) menu. This is usually the result of a user clicking on
  /// a "select" HTML input element. It is your responsibility to
  /// display this menu in your application. This event is not modal.
  ///
  /// @see WebView::DidSelectPopupMenuItem
  /// @see WebView::DidCancelPopupMenu
  ///
   void WebViewListener_Menu::OnShowPopupMenu(Awesomium::WebView* caller,
                               const WebPopupMenuInfo& menu_info)
   {

   }

  ///
  /// This event occurs when the page requests to display a context menu.
  /// This is usually the result of a user right-clicking somewhere on the
  /// page. It is your responsibility to display this menu in your
  /// application and perform the selected actions. This event is not modal.
  ///
   void WebViewListener_Menu::OnShowContextMenu(Awesomium::WebView* caller,
                                 const WebContextMenuInfo& menu_info)
   {
   }

  ///
  /// This event occurs when the page requests to display a file chooser
  /// dialog. This is usually the result of a user clicking on an HTML
  /// input element with `type='file`. It is your responsibility to display
  /// this menu in your application. This event is not modal.
  ///
  /// @see WebView::DidChooseFiles
  ///
   void WebViewListener_Dialog::OnShowFileChooser(Awesomium::WebView* caller,
                                 const WebFileChooserInfo& chooser_info)
   {

   }

  ///
  /// This event occurs when the page needs authentication from the user (for
  /// example, Basic HTTP Auth, NTLM Auth, etc). It is your responsibility to
  /// display a dialog so that users can input their username and password.
  /// This event is not modal.
  ///
  /// @see WebView::DidLogin
  /// @see WebView::DidCancelLogin
  ///
   void WebViewListener_Dialog::OnShowLoginDialog(Awesomium::WebView* caller,
                                 const WebLoginDialogInfo& dialog_info)
   {

   }


  ///
  /// This event occurs when the page requests to print itself. (Usually
  /// the result of `window.print()` being called from JavaScript.) It is
  /// your responsiblity to print the WebView to a file and handle the
  /// actual device printing.
  ///
  /// @see  WebView::PrintToFile
  ///
   void WebViewListener_Print::OnRequestPrint(Awesomium::WebView* caller)
   {

   }

  ///
  /// This event occurs when WebView::PrintToFile fails. Typically because of
  /// bad printer configuration or invalid output path (it must be writable).
  ///
  /// @param  request_id  The unique request ID (returned from
  ///                     WebView::PrintToFile earlier).
  ///
   void WebViewListener_Print::OnFailPrint(Awesomium::WebView* caller,
                           int request_id)
   {

   }

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
   void WebViewListener_Print::OnFinishPrint(Awesomium::WebView* caller,
                             int request_id,
                             const WebStringArray& file_list)
   {

   }


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
   void WebViewListener_Download::OnRequestDownload(Awesomium::WebView* caller,
                                 int download_id,
                                 const Awesomium::WebURL& url,
                                 const Awesomium::WebString& suggested_filename,
                                 const Awesomium::WebString& mime_type)
   {

   }

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
   void WebViewListener_Download::OnUpdateDownload(Awesomium::WebView* caller,
                                int download_id,
                                int64 total_bytes,
                                int64 received_bytes,
                                int64 current_speed)
   {

   }

  ///
  /// This event occurs when the download is finished.
  ///
  /// @param  download_id  The unique ID of the download.
  ///
  /// @param  url  The URL that initiated the download.
  ///
  /// @param  saved_path  The path that the download was saved to.
  ///
   void WebViewListener_Download::OnFinishDownload(Awesomium::WebView* caller,
                                int download_id,
                                const Awesomium::WebURL& url,
                                const Awesomium::WebString& saved_path)
   {

   }


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
   void WebViewListener_IME::OnUpdateIME(Awesomium::WebView* caller,
                           Awesomium::TextInputType type,
                           int caret_x,
                           int caret_y)
   {
   }

  ///
  /// This event is fired when the page cancels the IME composition.
  ///
   void WebViewListener_IME::OnCancelIME(Awesomium::WebView* caller)
   {
   }

  ///
  /// This event is fired when the page changes the displayed range
  /// of the IME composition.
  ///
   void WebViewListener_IME::OnChangeIMERange(Awesomium::WebView* caller,
                                unsigned int start,
                                unsigned int end)
   {

   }
