/*
This file is a part of aws_wrap library.
Read LICENSE.TXT and README.TXT provided 
within this package for more information.

Copyright (C) 2012 evilrat
*/

module awesomium.webview;

import awesomium.capi, awesomium.util, 
	awesomium.inputevt, awesomium.websession,
	awesomium.surface;
import std.c.string : strlen;



enum WebViewType
{
	OFFSCREEN = 0,
	WINDOWED,
}


enum FocusedElementType
{
	XZ
}



alias int NativeWindow;
alias int PrintConfig;

struct JSValue
{

}



class WebView
{
public:


	///
	/// Begin loading a certain URL asynchronously.
	///
	/// @param  url  The URL to begin loading.
	///
	/// @note  The page is not guaranteed to be loaded after this method returns.
	///        You should use WebViewListener::Load::OnFinishLoadingFrame to do
	///        something after the page is loaded.
	///
	void loadURL(string url)
	{
		auto weburl = aws_weburl_new_string(url.toCString);
		aws_webview_loadURL( this, weburl );
		aws_weburl_delete(weburl);
	}

	///
	/// The type of this WebView (declared at WebCore::CreateWebView). If this
	/// is an Offscreen WebView, you will need to display the Surface and pass
	/// all input yourself.
	///
	@property WebViewType type()
	{
		return cast(WebViewType) aws_webview_getType(this);
	}

	///
	/// Get the unique ID for the corresponding child-process hosting this
	/// WebView. May return 0 if the WebView has crashed or there is no
	/// process active.
	///
	int process_id() {
		return aws_webview_getProcId(this);
	}

	///
	/// Get the handle for the corresponding child-process hosting this
	/// WebView. This may not be initialized until some time after the
	/// WebView is actually created (when we receive the first IPC message
	/// from the child-process).
	///
	void* /*ProcessHandle*/ process_handle() {
		return aws_webview_getHandle(this);
	}

	///
	/// Set the parent window for this WebView. You should only call this
	/// for windowed WebViews (eg, those created with kWebViewType_Window)
	/// on the Windows platform.
	///
	/// You should call this method immediately after calling CreateWebView,
	/// the window for this WebView will not be created until the first
	/// call to set_parent_window on the Windows platform.
	///
	@disable void set_parent_window(NativeWindow parent)
	{

	}

	///
	/// Get the parent window for this WebView.
	///
	NativeWindow parent_window()
	{
		return 0;
	}

	///
	/// Get the actual window handle that was created by this WebView. This is
	/// only valid for windowed WebViews.
	///
	/// On the Mac OSX platform, you will need to retrieve this window (NSView)
	/// and add it to your application's view container to display it.
	///
	NativeWindow window()
	{
		return 0;
	}

	///
	/// Register a listener to handle view-related events.
	///
	/// @param  listener  The instance to register (you retain ownership).
	///
	//void set_view_listener(WebViewListener.View listener) = 0;

	///
	/// Register a listener to handle page-load events.
	///
	/// @param  listener  The instance to register (you retain ownership).
	///
	//void set_load_listener(WebViewListener::Load* listener) = 0;

	///
	/// Register a listener to handle process-related events (crash, hangs, etc).
	///
	/// @param  listener  The instance to register (you retain ownership).
	///
	//void set_process_listener(WebViewListener::Process* listener) = 0;

	///
	/// Register a listener to handle the display of various menus.
	///
	/// @param  listener  The instance to register (you retain ownership).
	///
	//void set_menu_listener(WebViewListener::Menu* listener) = 0;

	///
	/// Register a listener to handle the display of various dialogs.
	///
	/// @param  listener  The instance to register (you retain ownership).
	///
	//void set_dialog_listener(WebViewListener::Dialog* listener) = 0;

	///
	/// Register a listener to handle printing-related events.
	///
	/// @param  listener  The instance to register (you retain ownership).
	///
	//void set_print_listener(WebViewListener::Print* listener) = 0;

	///
	/// Register a listener to handle download-related events.
	///
	/// @param  listener  The instance to register (you retain ownership).
	///
	//void set_download_listener(WebViewListener::Download* listener) = 0;

	///
	/// Register a listener to handle IME-related events.
	///
	/// @param  listener  The instance to register (you retain ownership).
	///
	//void set_input_method_editor_listener(WebViewListener::InputMethodEditor* listener) = 0;

	/// Get the current view-event listener (may be NULL).
	//WebViewListener::View* view_listener() = 0;

	/// Get the current load-event listener (may be NULL).
	//WebViewListener::Load* load_listener() = 0;

	/// Get the current process-event listener (may be NULL).
	//WebViewListener::Process* process_listener() = 0;

	/// Get the current menu-event listener (may be NULL).
	//WebViewListener::Menu* menu_listener() = 0;

	/// Get the current dialog-event listener (may be NULL).
	//WebViewListener::Dialog* dialog_listener() = 0;

	/// Get the current print-event listener (may be NULL).
	//WebViewListener::Print* print_listener() = 0;

	/// Get the current download-event listener (may be NULL).
	//WebViewListener::Download* download_listener() = 0;

	/// Get the current download-event listener (may be NULL).
	//WebViewListener::InputMethodEditor* input_method_editor_listener() = 0;

	///
	/// Go back one page in history.
	///
	void GoBack()
	{
		aws_webview_goBack(this);
	}

	///
	/// Go forward one page in history.
	///
	void GoForward()
	{
		aws_webview_goForward(this);
	}

	///
	/// Go to a specific offset in history (for example, -1 would
	/// go back one page).
	///
	/// @param  The offset to go to.
	///
	void GoToHistoryOffset(int offset)
	{
		aws_webview_goToHistoryOffset(this, offset);
	}

	///
	/// Stop all page loads.
	///
	void Stop()
	{
		aws_webview_stop(this);
	}

	///
	/// Reload the current page.
	///
	/// @param  ignore_cache  Whether or not we force cached resources to
	///                       to be reloaded as well.
	///
	void Reload(bool ignore_cache)
	{
		aws_webview_reload(this, ignore_cache);
	}

	///
	/// Check whether or not we can go back in history.
	///
	bool CanGoBack()
	{
		return aws_webview_canGoBack(this);
	}

	///
	/// Check whether or not we can go forward in history.
	///
	bool CanGoForward()
	{
		return aws_webview_canGoForward(this);
	}

	///
	/// Get the current rendering Surface. May be NULL. This is only valid for
	/// offscreen WebViews (this will be NULL for windowed WebViews).
	///
	/// @note: If you never call WebCore::SetSurfaceFactory, the returned
	///        Surface will always be of type BitmapSurface.
	///
	/// @see WebCore::set_surface_factory
	///
	Surface surface()
	{
		// fixme
		auto surf = new BitmapSurface();
		surf._parent = this;
		surf._internal = cast(cBitSurfacePtr_t) aws_webview_getSurface(this);
		return surf;
	}

	void Destroy()
	{
		aws_webview_destroy(this);
	}

	/// Get the current page URL.
	//WebURL url() ;

	/// Get the current page title.
	@property string title()
	{	
		auto ws = aws_webview_getTitle(this);
		auto cs = aws_webstring_to_cstring(ws);

		auto len = strlen(cs.str);

		char[] tmp;
		tmp.length = len;
		tmp = cast(char[])cs.str[0..len];

		string ver = tmp.idup;

		//aws_webstring_delete(ws);

		return ver;
	}

	/// Get the session associated with this WebView.
	@disable WebSession session()
	{
		return null;
	}

	/// Check whether or not any page resources are loading.
	bool IsLoading()
	{
		return aws_webview_isLoading(this);
	}

	/// Check whether or not the WebView process has crashed.
	bool IsCrashed()
	{
		return aws_webview_isCrashed(this);
	}

	///
	/// Resize to certain pixel dimensions (will trigger a new Surface to
	/// be created). This operation is asynchronous and may not complete
	/// by the time this method returns.
	///
	/// @param  width  The width in pixels.
	///
	/// @param  height  The height in pixels.
	///
	void Resize(int width, int height)
	{
		aws_webview_resize(this, width, height);
	}

	///
	/// Set the background of the view to be transparent. You must call this
	/// if you intend to preserve the transparency of a page (eg, your
	/// body element has "background-color: transparent;" or some other
	/// semi-translucent background). Please note that the alpha channel is
	/// premultiplied.
	///
	/// This is only compatible with Offscreen WebViews.
	///
	/// If you never call this, the view will have an opaque, white background
	/// by default.
	///
	/// @param  is_transparent  Whether or not the view should support
	///                         transparency.
	///
	void SetTransparent(bool is_transparent)
	{
		aws_webview_setTransparent(this, is_transparent);
	}

	///
	/// Whether or not the view supports transparency.
	///
	bool IsTransparent()
	{
		return aws_webview_isTransparent(this);
	}

	///
	/// Pause the renderer. All rendering is done asynchronously in a separate
	/// process so you should call this when your view is hidden to save
	/// some CPU cycles.
	///
	void PauseRendering()
	{
		aws_webview_pauseRendering(this);
	}

	///
	/// Resume the renderer (will force a full repaint).
	///
	/// @see WebView::PauseRendering
	///
	void ResumeRendering()
	{
		aws_webview_resumeRendering(this);
	}

	///
	/// Give the appearance of input focus. You should call this whenever the
	/// view gains focus.
	///
	/// @note If you fail to see a blinking caret when you select a textbox,
	///       it's usually because you forgot to call this method.
	///
	void Focus()
	{
		aws_webview_focus(this);
	}

	///
	/// Remove the appearance of input focus. You should call this whenever the
	/// view loses focus.
	///
	void Unfocus()
	{
		aws_webview_unfocus(this);
	}

	///
	/// Get the type of the currently-focused element. This is useful for
	/// determining if the WebView should capture keyboard events. If no element
	/// is focused, this will return kFocusedElementType_None.
	///
	/// @see FocusedElementType
	///
	@disable FocusedElementType focused_element_type()
	{
		return cast(FocusedElementType) aws_webview_focusedElementType(this);
	}

	///
	/// Passes a mouse-move event to the view.
	///
	/// @param  x  The x-coordinate of the current mouse position
	///
	/// @param  y  The y-coordinate of the current mouse position
	///
	/// @note All coordinates should be localized to the view. All values are in
	///       pixels, the origin (0,0) begins at the top-left corner of the view,
	///       positive-y values are "down" and positive-x values are "right".
	///
	void InjectMouseMove(int x, int y)
	{
		aws_webview_injectMouseMove(this, x, y);
	}

	///
	/// Passes a mouse-down event using the last mouse-move coordinates.
	///
	/// @param  button  The button that was pressed.
	///
	void InjectMouseDown(MouseButton button)
	{
		aws_webview_injectMouseButton(this, button, true);
	}

	///
	/// Passes a mouse-up event using the last mouse-move coordinates.
	///
	/// @param  button  The button that was released.
	///
	void InjectMouseUp(MouseButton button)
	{
		aws_webview_injectMouseButton(this, button, false);
	}

	///
	/// Passes a mouse-wheel event.
	///
	/// @param  scroll_vert  The amount of pixels to scroll vertically by.
	///
	/// @param  scroll_horz  The amount of pixels to scroll horizontally by.
	///
	void InjectMouseWheel(int scroll_vert, int scroll_horz)
	{
		aws_webview_injectMouseWheel(this, scroll_vert, scroll_horz);
	}

	///
	/// Passes a keyboard event.
	///
	/// @param  key_event  The keyboard event.
	///
	@disable void InjectKeyboardEvent(WebKeyboardEvent key_event)
	{

	}

	///
	/// Passes a multi-touch event.
	///
	/// @param  touch_event  The multi-touch event.
	///
	@disable void InjectTouchEvent(WebTouchEvent touch_event)
	{

	}

	///
	/// Call this method to let the WebView know you will be passing
	/// text input via IME and will need to be notified of any
	/// IME-related events (caret position, user unfocusing textbox, etc.)
	/// Please see WebViewListener::InputMethodEditor.
	///
	/// Please note this is only compatible with Offscreen WebViews.
	///
	/// @param  activate  Whether or not IME should be activated.
	///
	void ActivateIME(bool activate)
	{
		aws_webview_activateIME(this, activate);
	}

	///
	/// Update the current IME text composition.
	///
	/// @param  input_string  The string generated by your IME.
	/// @param  cursor_pos    The current cursor position in your IME composition.
	/// @param  target_start  The position of the beginning of the selection.
	/// @param  target_end    The position of the end of the selection.
	///
	@disable void SetIMEComposition(string input_string,
								   int cursor_pos,
								   int target_start,
								   int target_end)
	{

	}

	///
	/// Confirm a current IME text composition.
	///
	/// @param  input_string  The string generated by your IME.
	///
	@disable void ConfirmIMEComposition(string input_string)
	{
		
	}

	///
	/// Cancel a current IME text composition.
	///
	void CancelIMEComposition()
	{
		aws_webview_cancelIMEComposition(this);
	}

	///
	/// Undo the last 'edit' operation. (Similar to CTRL+Z).
	///
	void Undo()
	{
		aws_webview_undo(this);
	}

	///
	/// Redo the last 'edit' operation. (Similar to CTRL+Y).
	///
	void Redo()
	{
		aws_webview_redo(this);
	}

	///
	/// Performs a 'cut' operation using the system clipboard.
	///
	void Cut()
	{
		aws_webview_cut(this);
	}

	///
	/// Performs a 'copy' operation using the system clipboard.
	///
	void Copy()
	{
		aws_webview_copy(this);
	}

	///
	/// Attempt to copy an image on the page to the system clipboard.
	/// This is meant to be used with Menu::OnShowContextMenu.
	///
	/// @param  x  The x-coordinate.
	///
	/// @param  y  The y-coordinate.
	///
	/// @note All coordinates should be localized to the view. All values are in
	///       pixels, the origin (0,0) begins at the top-left corner of the view,
	///       positive-y values are "down" and positive-x values are "right".
	///
	void CopyImageAt(int x, int y)
	{
		aws_webview_copyImageAt(this, x, y);
	}

	///
	/// Performs a 'paste' operation using the system clipboard.
	///
	void Paste()
	{
		aws_webview_paste(this);
	}

	///
	/// Performs a 'paste' operation using the system clipboard while attempting
	/// to preserve any styles of the original text.
	///
	void PasteAndMatchStyle()
	{
		aws_webview_pasteAndMatchStyle(this);
	}

	///
	/// Performs a 'select all' operation.
	///
	void SelectAll()
	{
		aws_webview_selectAll(this);
	}

	///
	/// Prints this WebView to a PDF file asynchronously.
	///
	/// @param  output_directory  A writeable directory to write the file(s) to.
	///
	/// @param  config  The configuration settings to use (you must specify
	///                 a writable output_path or this operation will fail).
	///
	/// @see WebView::set_print_listener
	///
	/// @return  Returns a unique request ID that you can use later to identify
	///          this specific request (see WebViewListener::Print). May return 0
	///          if this method fails prematurely (eg, if the view has crashed).
	///
	@disable int PrintToFile(string output_directory, PrintConfig config) 
	{
		return 0;
	}

	///
	/// Check if an error occurred during the last synchronous API call.
	///
	/// @see WebView::CreateGlobalJavascriptObject
	/// @see WebView::ExecuteJavascriptWithResult
	///
	@disable /*Error*/int last_error()
	{
		return 0;
	}

	///
	/// Create a JavaScript Object that will persist between all loaded pages.
	///
	/// @note
	///
	/// Global Objects can only contain the following JavaScript types as
	/// properties:
	///
	/// - Number
	/// - String
	/// - Array
	/// - Other Global Objects
	/// - Null
	/// - Undefined
	///
	/// Global Objects will retain any custom methods that are registered.
	///
	/// You can only create objects on pages with an active DOM. (You should
	/// wait until the first DOMReady event before creating your objects).
	///
	/// @param  name  The name of the object as it will appear in JavaScript.
	///               To create a child global-object, you should specify the
	///               the full name with dot-notation for example:
	///                  parentobject.childobject
	///
	///               The parent object should exist before attempting to make
	///               any children.
	///
	/// @return The returned JSValue will be of 'Object' type if this call
	/// succeeds. You can check the reason why the call failed by calling
	/// WebView::last_error() after this method.
	///
	@disable JSValue CreateGlobalJavascriptObject(string name)
	{
		return JSValue();
	}

	///
	/// Executes some JavaScript asynchronously on the page.
	///
	/// @param  script       The string of JavaScript to execute.
	///
	/// @param  frame_xpath  The xpath of the frame to execute within; leave
	///                      this blank to execute in the main frame.
	///
	void ExecuteJavascript(string script, string frame_xpath)
	{
		aws_webview_executeJS(this, script.toCString, frame_xpath.toCString);
	}

	///
	/// Executes some JavaScript synchronously on the page and returns a result.
	///
	/// @param  script       The string of JavaScript to execute.
	///
	/// @param  frame_xpath  The xpath of the frame to execute within; leave
	///                      this blank to execute in the main frame.
	///
	/// @return  Returns the result (if any). Any JSObject returned from this
	///          method will be a remote proxy for an object contained within
	///          the WebView process. If this call fails, JSValue will have an
	///          Undefined type. You can check WebView::last_error() for more
	///          information about the failure.
	///
	/// @note  You should never call this from within any of the following
	///        callbacks:
	///
	///        - JSMethodHandler::OnMethodCall
	///        - JSMethodHandler::OnMethodCallWithReturnValue
	///        - DataSource::OnRequest
	///
	@disable JSValue ExecuteJavascriptWithResult(string script, string frame_xpath)
	{
		return JSValue();
	}

	///
	/// Register a handler for custom JSObject methods.
	///
	/// @param  handler  The handler to register (you retain ownership).
	///
	/// @see JSObject::SetCustomMethod
	///
	//void set_js_method_handler(JSMethodHandler handler) ;

	/// Get the handler for custom JSObject methods.
	//JSMethodHandler* js_method_handler() = 0;

	///
	/// This method should be called as the result of a user selecting an item
	/// in a popup (dropdown) menu.
	///
	/// @param  item_index  The index of the item selected. Item index starts
	///                     at 0. You can pass -1 as a shortcut for
	///                     WebView::DidCancelPopupMenu.
	///
	/// @see  WebViewListener::Menu::OnShowPopupMenu
	///
	void DidSelectPopupMenuItem(int item_index)
	{
		aws_webview_didSelectPopupMenuItem(this, item_index);
	}

	///
	/// This method should be called as the result of a user cancelling a popup
	/// menu.
	///
	/// @see  WebViewListener::Menu::OnShowPopupMenu
	///
	void DidCancelPopupMenu()
	{
		aws_webview_didCancelPopupMenu(this);
	}

	///
	/// This method should be called as the result of a user selecting files in
	/// a file-chooser dialog.
	///
	/// @param  files  An array of file-paths that the user selected. If the
	///                user cancelled the dialog, you should pass an empty array.
	///
	/// @param  should_write_files  Whether or not this was a Save File dialog.
	///
	/// @see  WebViewListener::Dialog::OnShowFileChooser
	///
	@disable void DidChooseFiles(string[] files, bool should_write_files)
	{

	}

	///
	/// This method should be called as the result of a user supplying
	/// their credentials in a login dialog.
	///
	/// @param  request_id  The id of the request that was handled (see
	///                     WebLoginDialogInfo::request_id).
	///
	/// @param  username  The username supplied.
	///
	/// @param  password  The password supplied.
	///
	/// @see  WebViewListener::Dialog::OnShowLoginDialog
	///
	void DidLogin(int request_id, string username, string password)
	{
		aws_webview_didLogin(this, request_id, username.toCString, password.toCString);
	}

	///
	/// This method should be called as the result of a user cancelling
	/// a login dialog.
	///
	/// @param  request_id  The id of the request that was handled (see
	///                     WebLoginDialogInfo::request_id).
	///
	/// @see  WebViewListener::Dialog::OnShowLoginDialog
	///
	void DidCancelLogin(int request_id)
	{
		aws_webview_didCancelLogin(this, request_id);
	}

	///
	/// This method should be called as the result of a user selecting
	/// a path to download a file. The file will only begin downloading
	/// after this call is made.
	///
	/// @param  download_id  The id of the download.
	///
	/// @param  path  The full path (including filename) to write the download to.
	///
	/// @see  WebViewListener::Download::OnRequestDownload
	///
	void DidChooseDownloadPath(int download_id, string path)
	{
		aws_webview_didChooseDownloadPath(this, download_id, path.toCString);
	}

	///
	/// This method should be called as the result of a user cancelling a
	/// download.
	///
	/// @param  download_id  The id of the download.
	///
	/// @see  WebViewListener::Download::OnRequestDownload
	///
	void DidCancelDownload(int download_id)
	{
		aws_webview_didCancelDownload(this, download_id);
	}

package:
	alias _internal this;
	cWebView* _internal;
}




// this is the part of webview config so let it be here for now
struct WebPreferences {

///
/// Whether or not JavaScript should be enabled. (Default: true)
///
bool enable_javascript = true;

///
/// Whether or not Dart (experimental) should be enabled. (Default: true)
///
bool enable_dart = true;

///
/// Whether or not plugins (Flash, Silverlight) should be enabled.
/// (Default: true)
///
bool enable_plugins = true;

///
/// Whether or not HTML5 Local Storage should be enabled. (Default: true)
///
bool enable_local_storage = true;

///
/// Whether or not HTML5 Databases should be enabled. (Default: false)
///
bool enable_databases = false;

///
/// Whether or not HTML5 App Cache should be enabled. (Default: true)
///
bool enable_app_cache = true;

///
/// Whether or not HTML5 WebAudio should be enabled. (Default: true)
///
bool enable_web_audio = true;

///
/// Whether or not HTML5 WebGL (experimental) should be enabled.
/// (Default: false)
///
bool enable_web_gl = false;

///
/// Whether or not web security should be enabled (prevents cross-domain
/// requests, for example). (Default: true)
///
bool enable_web_security = true;

///
/// Whether or not remote fonts should be enabled. (Default: true)
///
bool enable_remote_fonts = true;

///
/// Whether or not smooth scrolling should be enabled. (Default: false)
///
bool enable_smooth_scrolling = false;

///
/// Whether or not GPU accelerated compositing (experimental) should be
/// enabled. This is only compatible with windowed WebViews at this time.
/// (Default: false)
///
bool enable_gpu_acceleration = false;

///
/// User-defined CSS to be applied to all web-pages. This is useful for
/// overriding default styles. (Default: empty)
///
string user_stylesheet;

///
/// Proxy configuration string.
///
/// @note  Can either be: "auto" (use the OS proxy config), "none" (ignore
///        proxy settings), or you can specify a hardcoded proxy config
///        string, for example: "myproxyserver.com:80". (Default: "auto")
///
string proxy_config = "auto";

///
/// The accept-language for the browser (Default: "en-us,en")
///
string accept_language = "en-us,en";

///
/// The accept-charset for the browser (Default: "iso-8859-1,*,utf-8")
///
string accept_charset = "iso-8859-1,*,utf-8";

///
/// The default encoding for the browser (Default: "iso-8859-1")
///
string default_encoding = "iso-8859-1";

///
/// Whether or not standalone images should be shrunk to fit the view.
/// (Default: true)
///
bool shrink_standalone_images_to_fit = true;

///
/// Whether or not images should be loaded automatically on the page.
/// (Default: true)
///
bool load_images_automatically = true;

///
/// Whether or not scripts are allowed to open windows. (Default: true)
///
bool allow_scripts_to_open_windows = true;

///
/// Whether or not scripts are allowed to close windows. (Default: true)
///
bool allow_scripts_to_close_windows = true;

///
/// Whether or not scripts are allowed to access the clipboard.
/// (Default: false)
///
bool allow_scripts_to_access_clipboard = false;

///
/// Whether or not local files can access other local files. (Default: false)
///
bool allow_universal_access_from_file_url = false;

///
/// Whether or not scripts are allowed to open windows. (Default: false)
///
bool allow_file_access_from_file_url = false;

///
/// Whether or not insecure content is displayed and/or run. (Default: true)
///
bool allow_running_insecure_content = true;
};