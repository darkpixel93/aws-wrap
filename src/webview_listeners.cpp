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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.begin(
					reinterpret_cast<cWebViewPtr_t>(caller),
					frame_id,
					is_main_frame,
					reinterpret_cast<const cWebUrlPtr_t&>(url),
					is_error_page,
					cb->second.userPointer
				);
		 }
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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.fail(
					reinterpret_cast<cWebViewPtr_t>(caller),
					frame_id,
					is_main_frame,
					reinterpret_cast<const cWebUrlPtr_t&>(url),
					error_code,
					reinterpret_cast<const cWebStringPtr_t&>(error_desc),
					cb->second.userPointer
				);
		 }
   }

  /// This event occurs when the page finishes loading a frame.
  /// The main frame always finishes loading last for a given page load.
   void WebViewListener_Load::OnFinishLoadingFrame(Awesomium::WebView* caller,
                                    int64 frame_id,
                                    bool is_main_frame,
                                    const Awesomium::WebURL& url)
   {
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.finish(
					reinterpret_cast<cWebViewPtr_t>(caller),
					frame_id,
					is_main_frame,
					reinterpret_cast<const cWebUrlPtr_t&>(url),
					cb->second.userPointer
				);
		 }
   }

  /// This event occurs when the DOM has finished parsing and the
  /// window object is available for JavaScript execution.
   void WebViewListener_Load::OnDocumentReady(Awesomium::WebView* caller,
                               const Awesomium::WebURL& url)
   {
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.ready(
					reinterpret_cast<cWebViewPtr_t>(caller),
					reinterpret_cast<const cWebUrlPtr_t&>(url),
					cb->second.userPointer
				);
		 }
   }

   	void WebViewListener_Load::addCallback(Awesomium::WebView* view, cWebView_Load clbk)
	{
		callbacks.emplace(view, clbk);
	}

	void WebViewListener_Load::removeCallback(Awesomium::WebView* view)
	{
		auto cb = callbacks.find(view);

		if  ( cb != callbacks.end() )
		{
			callbacks.erase(cb);
		}
	}

	 // ------------------ PROCESS -------------------------

  /// This event occurs when the process hangs.
   void WebViewListener_Process::OnUnresponsive(Awesomium::WebView* caller)
   {
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.unresponsive(
					reinterpret_cast<cWebViewPtr_t>(caller),
					cb->second.userPointer
				);
		 }
   }

  /// This event occurs when the process becomes responsive after
  /// a hang.
   void WebViewListener_Process::OnResponsive(Awesomium::WebView* caller)
   {
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.responsive(
					reinterpret_cast<cWebViewPtr_t>(caller),
					cb->second.userPointer
				);
		 }
   }

  /// This event occurs when the process crashes.
   void WebViewListener_Process::OnCrashed(Awesomium::WebView* caller,
                         Awesomium::TerminationStatus status)
   {
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.crashed(
					reinterpret_cast<cWebViewPtr_t>(caller),
					status,
					cb->second.userPointer
				);
		 }
   }

   void WebViewListener_Process::addCallback(Awesomium::WebView* view, cWebView_Process clbk)
	{
		callbacks.emplace(view, clbk);
	}

	void WebViewListener_Process::removeCallback(Awesomium::WebView* view)
	{
		auto cb = callbacks.find(view);

		if  ( cb != callbacks.end() )
		{
			callbacks.erase(cb);
		}
	}

	// ------------------ MENU -------------------------


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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cWebPopupMenuInfo_t minfo;
		   cRect rect;

		   rect.x = menu_info.bounds.x;
		   rect.y = menu_info.bounds.y;
		   rect.width = menu_info.bounds.width;
		   rect.height = menu_info.bounds.height;

		   minfo.bounds = rect;
		   minfo.items = reinterpret_cast<cWebMenuItemArrayPtr_t>( new Awesomium::WebMenuItemArray(menu_info.items) );
		   minfo.item_font_size = menu_info.item_font_size;
		   minfo.item_height = menu_info.item_height;
		   minfo.right_aligned = menu_info.right_aligned;
		   minfo.selected_item = menu_info.selected_item;

		   cb->second.popup(
					reinterpret_cast<cWebViewPtr_t>(caller),
					minfo,
					cb->second.userPointer
				);
		 }
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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cWebContextMenuInfo_t minfo;

		   minfo.edit_flags = menu_info.edit_flags;
		   minfo.frame_id = menu_info.frame_id;
		   minfo.frame_url = reinterpret_cast<cWebUrlPtr_t>(new Awesomium::WebURL(menu_info.frame_url));
		   minfo.is_editable = menu_info.is_editable;
		   minfo.link_url = reinterpret_cast<cWebUrlPtr_t>(new Awesomium::WebURL(menu_info.link_url));
		   minfo.media_state = menu_info.media_state;
		   minfo.media_type = menu_info.media_type;
		   minfo.page_url = reinterpret_cast<cWebUrlPtr_t>(new Awesomium::WebURL(menu_info.page_url));
		   minfo.pos_x = menu_info.pos_x;
		   minfo.pos_y = menu_info.pos_y;
		   minfo.src_url = reinterpret_cast<cWebUrlPtr_t>(new Awesomium::WebURL(menu_info.src_url));

		   cb->second.context(
					reinterpret_cast<cWebViewPtr_t>(caller),
					minfo,
					cb->second.userPointer
				);
		 }
   }

   void WebViewListener_Menu::addCallback(Awesomium::WebView* view, cWebView_Menu clbk)
	{
		callbacks.emplace(view, clbk);
	}

	void WebViewListener_Menu::removeCallback(Awesomium::WebView* view)
	{
		auto cb = callbacks.find(view);

		if  ( cb != callbacks.end() )
		{
			callbacks.erase(cb);
		}
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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cWebFileChooserInfo_t minfo;

		   minfo.accept_types = reinterpret_cast<const cWebStringArrayPtr_t&>(chooser_info.accept_types);
		   minfo.default_file_name = reinterpret_cast<const cWebStringPtr_t&>(chooser_info.default_file_name);
		   minfo.mode = chooser_info.mode;
		   minfo.title = reinterpret_cast<const cWebStringPtr_t&>(chooser_info.title);

		   cb->second.file(
					reinterpret_cast<cWebViewPtr_t>(caller),
					minfo,
					cb->second.userPointer
				);
		 }
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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cWebLoginDialogInfo_t minfo;

		   minfo.host = reinterpret_cast<const cWebStringPtr_t&>(dialog_info.host);
		   minfo.is_proxy = dialog_info.is_proxy;
		   minfo.port = dialog_info.port;
		   minfo.realm = reinterpret_cast<const cWebStringPtr_t&>(dialog_info.realm);
		   minfo.request_id = dialog_info.request_id;
		   minfo.request_url = reinterpret_cast<const cWebStringPtr_t&>(dialog_info.request_url);
		   minfo.scheme = reinterpret_cast<const cWebStringPtr_t&>(dialog_info.scheme);

		   cb->second.login(
					reinterpret_cast<cWebViewPtr_t>(caller),
					minfo,
					cb->second.userPointer
				);
		 }
   }

   void WebViewListener_Dialog::addCallback(Awesomium::WebView* view, cWebView_Dialog clbk)
	{
		callbacks.emplace(view, clbk);
	}

	void WebViewListener_Dialog::removeCallback(Awesomium::WebView* view)
	{
		auto cb = callbacks.find(view);

		if  ( cb != callbacks.end() )
		{
			callbacks.erase(cb);
		}
	}

   // ------------------ PRINT -------------------------


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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.request(
					reinterpret_cast<cWebViewPtr_t>(caller),
					cb->second.userPointer
				);
		 }
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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.fail(
					reinterpret_cast<cWebViewPtr_t>(caller),
					request_id,
					cb->second.userPointer
				);
		 }
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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.finish(
					reinterpret_cast<cWebViewPtr_t>(caller),
					request_id,
					reinterpret_cast<const cWebStringArrayPtr_t&>(file_list),
					cb->second.userPointer
				);
		 }
   }

   void WebViewListener_Print::addCallback(Awesomium::WebView* view, cWebView_Print clbk)
	{
		callbacks.emplace(view, clbk);
	}

	void WebViewListener_Print::removeCallback(Awesomium::WebView* view)
	{
		auto cb = callbacks.find(view);

		if  ( cb != callbacks.end() )
		{
			callbacks.erase(cb);
		}
	}

   // ------------------ DOWNLOAD -------------------------


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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.request(
					reinterpret_cast<cWebViewPtr_t>(caller),
					download_id,
					reinterpret_cast<const cWebUrlPtr_t&>(url),
					reinterpret_cast<const cWebStringPtr_t&>(suggested_filename),
					reinterpret_cast<const cWebStringPtr_t&>(mime_type),
					cb->second.userPointer
				);
		 }
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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.update(
					reinterpret_cast<cWebViewPtr_t>(caller),
					download_id,
					total_bytes,
					received_bytes,
					current_speed,
					cb->second.userPointer
				);
		 }
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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.finish(
					reinterpret_cast<cWebViewPtr_t>(caller),
					download_id,
					reinterpret_cast<const cWebUrlPtr_t&>(url),
					reinterpret_cast<const cWebStringPtr_t&>(saved_path),
					cb->second.userPointer
				);
		 }
   }

   void WebViewListener_Download::addCallback(Awesomium::WebView* view, cWebView_Download clbk)
	{
		callbacks.emplace(view, clbk);
	}

	void WebViewListener_Download::removeCallback(Awesomium::WebView* view)
	{
		auto cb = callbacks.find(view);

		if  ( cb != callbacks.end() )
		{
			callbacks.erase(cb);
		}
	}


   // ------------------ IME -------------------------

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
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.update(
					reinterpret_cast<cWebViewPtr_t>(caller),
					type,
					caret_x,
					caret_y,
					cb->second.userPointer
				);
		 }
   }

  ///
  /// This event is fired when the page cancels the IME composition.
  ///
   void WebViewListener_IME::OnCancelIME(Awesomium::WebView* caller)
   {
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.cancel(
					reinterpret_cast<cWebViewPtr_t>(caller),
					cb->second.userPointer
				);
		 }
   }

  ///
  /// This event is fired when the page changes the displayed range
  /// of the IME composition.
  ///
   void WebViewListener_IME::OnChangeIMERange(Awesomium::WebView* caller,
                                unsigned int start,
                                unsigned int end)
   {
	   auto cb = callbacks.find(caller);
	   if ( cb != callbacks.end() )
	   {
		   cb->second.range(
					reinterpret_cast<cWebViewPtr_t>(caller),
					start,
					end,
					cb->second.userPointer
				);
		 }
   }

   void WebViewListener_IME::addCallback(Awesomium::WebView* view, cWebView_IME clbk)
	{
		callbacks.emplace(view, clbk);
	}

	void WebViewListener_IME::removeCallback(Awesomium::WebView* view)
	{
		auto cb = callbacks.find(view);

		if  ( cb != callbacks.end() )
		{
			callbacks.erase(cb);
		}
	}
