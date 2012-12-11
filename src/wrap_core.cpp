#include <Awesomium/WebCore.h>
#include <Awesomium/WebConfig.h>
#include <Awesomium/WebPreferences.h>

#include <Awesomium/JSArray.h>
#include <Awesomium/JSObject.h>
#include <Awesomium/JSValue.h>

#include <Awesomium/WebURL.h>
#include <Awesomium/WebView.h>

#include <Awesomium/BitmapSurface.h>


#include "wrap_core.h"


class JSHandler : public Awesomium::JSMethodHandler
{

};


// pragma message stuff
#define STRING2(x) #x
#define STRING(x) STRING2(x)


Awesomium::WebConfig wcToAweConf(cWebConf wc);
Awesomium::WebPreferences wpToAwePrefs(cWebPrefs wp);
Awesomium::WebString toAweString(cString str);
Awesomium::WebStringArray toAweStrArray(cStringArray sa);

Awesomium::WebString toAweString(cString str)
{
	return Awesomium::WebString::CreateFromUTF8(str.str, str.len);
}

Awesomium::WebStringArray toAweStrArray(cStringArray sa)
{
	Awesomium::WebStringArray wsa;
	
	for( unsigned i = 0; i < sa.size; ++i ) {
		wsa.Push( toAweString(*sa.ptr[i]) );
	}

	return wsa;
}

extern "C" 
{

	cString fromAweString(const Awesomium::WebString& ws)
	{
		cString ls;

		ls.len = ws.ToUTF8(nullptr,0);
		ls.str = static_cast<char*>(malloc(ls.len));
		memset(ls.str, 0, ls.len);
		ws.ToUTF8(ls.str,ls.len);

		return ls;
	}

	EXPORT cString aws_webstring_to_cstring (cWebStringPtr_t string)
	{
		return fromAweString(*reinterpret_cast<Awesomium::WebString*>(string));
	}

	EXPORT cWebStringPtr_t aws_webstring_new()
	{
		return reinterpret_cast<cWebStringPtr_t>(
				new Awesomium::WebString()
			);
	}

	EXPORT void aws_webstring_delete(cWebStringPtr_t string)
	{
		auto str = reinterpret_cast<Awesomium::WebString*>(string);

		if ( str ) {
			delete str;
		}
	}

	EXPORT cWebStringPtr_t aws_webstring_new_utf8(const char* string, unsigned len)
	{
		return reinterpret_cast<cWebStringPtr_t>(
				new Awesomium::WebString(
					Awesomium::WebString::CreateFromUTF8(string, len)
				)
			);
	}

	EXPORT unsigned aws_webstring_to_utf8(cWebStringPtr_t string, char* dest)
	{
		auto str = reinterpret_cast<Awesomium::WebString*>(string);

		if ( str ) {
			unsigned len = str->ToUTF8(nullptr, 0);
			return str->ToUTF8(dest,len);
		}
		
		return 0;
	}

	EXPORT cWebStringPtr_t aws_webstring_new_substring (cWebStringPtr_t srcstring, unsigned start, unsigned len)
	{
		auto str = reinterpret_cast<Awesomium::WebString*>(srcstring);

		if ( str ) {
			return reinterpret_cast<cWebStringPtr_t>(new Awesomium::WebString(*str, start, len));
		}

		return nullptr;
	}

	// ===============================================
	// WEB CORE

	EXPORT const cWebCorePtr_t aws_webcore_init(cWebConf wc)
	{
		return reinterpret_cast<cWebCorePtr_t>(Awesomium::WebCore::Initialize( wcToAweConf(wc) ));
	}

	EXPORT const cWebCorePtr_t aws_webcore_initDefault()
	{
		return reinterpret_cast<cWebCorePtr_t>(Awesomium::WebCore::Initialize( Awesomium::WebConfig() ));
	}

	EXPORT void aws_webcore_shutdown()
	{
		Awesomium::WebCore::Shutdown();
	}

	EXPORT const cWebCorePtr_t aws_webcore_instance()
	{
		return reinterpret_cast<cWebCorePtr_t>(Awesomium::WebCore::instance());
	}

	EXPORT cWebSessionPtr_t aws_webcore_createWebSession(cWebCorePtr_t webcore, cString path, cWebPrefs wp)
	{
		auto wc = reinterpret_cast<Awesomium::WebCore*>(webcore);

		if ( wc ) {
			return reinterpret_cast<cWebSessionPtr_t>( wc->CreateWebSession(toAweString(path), wpToAwePrefs(wp)) );
		}
		
		return nullptr;
	}

	EXPORT cWebViewPtr_t aws_webcore_createWebView(cWebCorePtr_t webcore, int w, int h, cWebSessionPtr_t sess, int type)
	{
		auto wc = reinterpret_cast<Awesomium::WebCore*>(webcore);

		if ( wc ) {

			auto session = reinterpret_cast<Awesomium::WebSession*>(sess);
			auto viewtype = static_cast<Awesomium::WebViewType>(type);

			return reinterpret_cast<cWebViewPtr_t>( wc->CreateWebView( w, h,
								session ? session : nullptr,
								viewtype) );
		}

		return nullptr;
	}

	EXPORT void aws_webcore_setSurfaceFactory(cWebCorePtr_t webcore, cSurfaceFactoryPtr_t factory)
	{
		auto wc = reinterpret_cast<Awesomium::WebCore*>(webcore);

		if ( wc ) {
			auto sf = reinterpret_cast<Awesomium::SurfaceFactory*>(factory);

			wc->set_surface_factory(sf);
		}
	}

	EXPORT cSurfaceFactoryPtr_t aws_webcore_getSurfaceFactory(cWebCorePtr_t webcore)
	{
		auto wc = reinterpret_cast<Awesomium::WebCore*>(webcore);

		if ( wc ) {
			return reinterpret_cast<cSurfaceFactoryPtr_t>(wc->surface_factory());
		}

		return nullptr;
	}

	EXPORT void aws_webcore_setResourceInterceptor(cWebCorePtr_t webcore, cResInterceptorPtr_t interceptor)
	{
		auto wc = reinterpret_cast<Awesomium::WebCore*>(webcore);

		if ( wc ) {
			auto ri = reinterpret_cast<Awesomium::ResourceInterceptor*>(interceptor);

			wc->set_resource_interceptor(ri);
		}
	}

	EXPORT cResInterceptorPtr_t aws_webcore_getResourceInterceptor(cWebCorePtr_t webcore)
	{
		auto wc = reinterpret_cast<Awesomium::WebCore*>(webcore);

		if ( wc ) {
			return reinterpret_cast<cResInterceptorPtr_t>(wc->resource_interceptor());
		}

		return nullptr;
	}

	EXPORT void aws_webcore_update(cWebCorePtr_t webcore)
	{
		auto wc = reinterpret_cast<Awesomium::WebCore*>(webcore);

		if ( wc ) {
			wc->Update();
		}
	}

	EXPORT const char* aws_webcore_versionString(cWebCorePtr_t webcore)
	{
		auto wc = reinterpret_cast<Awesomium::WebCore*>(webcore);

		if ( wc ) {
			return wc->version_string();
		}

		return nullptr;
	}

	// ===============================================
	// WEB VIEW

	EXPORT void aws_webview_destroy(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Destroy();
		}
	}

	EXPORT int aws_webview_getType(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->type();
		}

		return -1;
	}

	EXPORT int aws_webview_getProcId(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->process_id();
		}

		return -1;
	}

	EXPORT void* aws_webview_getHandle(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->process_handle();
		}

		return nullptr;
	}

	EXPORT void aws_webview_setParentWindow(cWebViewPtr_t webview, void* window)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto wnd = static_cast<Awesomium::NativeWindow>(window);
			view->set_parent_window(wnd);
		}
	}

	EXPORT void* aws_webview_getParentWindow(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->parent_window();
		}

		return nullptr;
	}

	EXPORT void* aws_webview_getWindow(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->window();
		}

		return nullptr;
	}

	// ------------ SET LISTENERS

	EXPORT void aws_webview_setViewListener(cWebViewPtr_t webview, void* listener)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto lst = static_cast<Awesomium::WebViewListener::View*>(listener);
			view->set_view_listener(lst);
		}
	}

	EXPORT void aws_webview_setProcessListener(cWebViewPtr_t webview, void* listener)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto lst = static_cast<Awesomium::WebViewListener::View*>(listener);
			view->set_view_listener(lst);
		}
	}

	EXPORT void aws_webview_setLoadListener(cWebViewPtr_t webview, void* listener)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto lst = static_cast<Awesomium::WebViewListener::Load*>(listener);
			view->set_load_listener(lst);
		}
	}

	EXPORT void aws_webview_setMenuListener(cWebViewPtr_t webview, void* listener)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto lst = static_cast<Awesomium::WebViewListener::Menu*>(listener);
			view->set_menu_listener(lst);
		}
	}

	EXPORT void aws_webview_setPrintListener(cWebViewPtr_t webview, void* listener)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto lst = static_cast<Awesomium::WebViewListener::Print*>(listener);
			view->set_print_listener(lst);
		}
	}

	EXPORT void aws_webview_setDownloadListener(cWebViewPtr_t webview, void* listener)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto lst = static_cast<Awesomium::WebViewListener::Download*>(listener);
			view->set_download_listener(lst);
		}
	}

	EXPORT void aws_webview_setIMEListener(cWebViewPtr_t webview, void* listener)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto lst = static_cast<Awesomium::WebViewListener::InputMethodEditor*>(listener);
			view->set_input_method_editor_listener(lst);
		}
	}


	// ------------ GET LISTENERS

	EXPORT void* aws_webview_getViewListener(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->view_listener();
		}

		return nullptr;
	}

	EXPORT void* aws_webview_getLoadListener(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->load_listener();
		}

		return nullptr;
	}

	EXPORT void* aws_webview_getProcessListener(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->process_listener();
		}

		return nullptr;
	}

	EXPORT void* aws_webview_getMenuListener(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->menu_listener();
		}

		return nullptr;
	}

	EXPORT void* aws_webview_getDialogListener(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->dialog_listener();
		}

		return nullptr;
	}
	
	EXPORT void* aws_webview_getPrintListener(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->print_listener();
		}

		return nullptr;
	}

	EXPORT void* aws_webview_getDownloadListener(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->download_listener();
		}

		return nullptr;
	}

	EXPORT void* aws_webview_getIMEListener(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->input_method_editor_listener();
		}

		return nullptr;
	}

	// -------------------------------

	EXPORT void aws_webview_loadURL(cWebViewPtr_t webview, cWebUrlPtr_t url)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto _url = reinterpret_cast<Awesomium::WebURL*>(url);
			view->LoadURL(*_url);
		}
	}

	EXPORT void aws_webview_goBack(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->GoBack();
		}
	}

	EXPORT void aws_webview_goForward(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->GoForward();
		}
	}

	EXPORT void aws_webview_goToHistoryOffset(cWebViewPtr_t webview, int offset)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->GoToHistoryOffset(offset);
		}
	}

	EXPORT void aws_webview_stop(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Stop();
		}
	}

	EXPORT void aws_webview_reload(cWebViewPtr_t webview, bool ignoreCache)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Reload(ignoreCache);
		}
	}

	EXPORT bool aws_webview_canGoBack(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->CanGoBack();
		}

		return false;
	}

	EXPORT bool aws_webview_canGoForward(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->CanGoForward();
		}

		return false;
	}

	EXPORT cSurfacePtr_t aws_webview_getSurface(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return reinterpret_cast<cSurfacePtr_t>(view->surface());
		}

		return nullptr;
	}

	EXPORT cWebUrlPtr_t aws_webview_getURL(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return reinterpret_cast<cWebUrlPtr_t>(
						new Awesomium::WebURL(view->url())
					);
		}

		return nullptr;
	}

	EXPORT cWebStringPtr_t aws_webview_getTitle(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return reinterpret_cast<cWebStringPtr_t>(
						new Awesomium::WebString(view->title())
					);
		}

		return nullptr;
	}

	EXPORT cWebSessionPtr_t aws_webview_getSession(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return reinterpret_cast<cWebSessionPtr_t>(view->session());
		}

		return nullptr;
	}

	EXPORT bool aws_webview_isLoading(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->IsLoading();
		}

		return false;
	}

	EXPORT bool aws_webview_isCrashed(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->IsCrashed();
		}

		return false;
	}

	EXPORT void aws_webview_resize(cWebViewPtr_t webview, int x, int y)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Resize(x,y);
		}
	}

	EXPORT void aws_webview_setTransparent(cWebViewPtr_t webview, bool state)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->SetTransparent(state);
		}
	}

	EXPORT bool aws_webview_isTransparent(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->IsTransparent();
		}

		return false;
	}

	EXPORT void aws_webview_pauseRendering(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->PauseRendering();
		}
	}

	EXPORT void aws_webview_resumeRendering(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->ResumeRendering();
		}
	}

	EXPORT void aws_webview_focus(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Focus();
		}
	}

	EXPORT void aws_webview_unfocus(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Unfocus();
		}
	}

	EXPORT int aws_webview_focusedElementType(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->focused_element_type();
		}

		return -1;
	}

	EXPORT void aws_webview_injectMouseMove(cWebViewPtr_t webview, int mx, int my)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->InjectMouseMove(mx,my);
		}
	}

	EXPORT void aws_webview_injectMouseButton(cWebViewPtr_t webview, int button, bool down)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto btn = static_cast<Awesomium::MouseButton>(button);
			if ( down )
				view->InjectMouseDown(btn);
			else 
				view->InjectMouseUp(btn);
		}
	}

	EXPORT void aws_webview_injectMouseWheel(cWebViewPtr_t webview, int wx, int wy)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->InjectMouseWheel(wx, wy);
		}
	}

	EXPORT void aws_webview_injectKeyboardEvent(cWebViewPtr_t webview, void* keyevent)
	{
#pragma message (__FILE__ "[" STRING(__LINE__) "]: function not implemented")
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto evt = Awesomium::WebKeyboardEvent();
			view->InjectKeyboardEvent(evt);
		}
	}

	EXPORT void aws_webview_injectTouchEvent(cWebViewPtr_t webview, void* touchevent)
	{
#pragma message (__FILE__ "[" STRING(__LINE__) "]: function not implemented")
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto evt = Awesomium::WebTouchEvent();
			view->InjectTouchEvent(evt);
		}
	}

	EXPORT void aws_webview_activateIME(cWebViewPtr_t webview, bool state)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->ActivateIME(state);
		}
	}

	EXPORT void aws_webview_setIMEComposition(cWebViewPtr_t webview, cString target_string, int cursorpos, int targetstart, int tartgetend)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->SetIMEComposition( toAweString(target_string), cursorpos, targetstart, tartgetend);
		}
	}

	EXPORT void aws_webview_cancelIMEComposition(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->CancelIMEComposition();
		}
	}

	EXPORT void aws_webview_undo(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Undo();
		}
	}

	EXPORT void aws_webview_redo(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Redo();
		}
	}

	EXPORT void aws_webview_cut(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Cut();
		}
	}

	EXPORT void aws_webview_copy(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Copy();
		}
	}

	EXPORT void aws_webview_copyImageAt(cWebViewPtr_t webview, int x, int y)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->CopyImageAt(x,y);
		}
	}

	EXPORT void aws_webview_paste(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->Paste();
		}
	}

	EXPORT void aws_webview_pasteAndMatchStyle(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->PasteAndMatchStyle();
		}
	}

	EXPORT void aws_webview_selectAll(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->SelectAll();
		}
	}

	EXPORT void aws_webview_printToFile(cWebViewPtr_t webview, cString outDir, void* printconf)
	{
#pragma message (__FILE__ "[" STRING(__LINE__) "]: function not implemented")
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto pconf = Awesomium::PrintConfig();
			view->PrintToFile( toAweString(outDir), pconf );
		}
	}

	EXPORT int aws_webview_lastError(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return view->last_error();
		}

		return -1;
	}

	EXPORT cJSValuePtr_t aws_webview_createGlobalJSObject(cWebViewPtr_t webview, cString objname)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return reinterpret_cast <cJSValuePtr_t>(
				new Awesomium::JSValue(view->CreateGlobalJavascriptObject( toAweString(objname) ))
			);
		}

		return nullptr;
	}

	EXPORT void aws_webview_executeJS(cWebViewPtr_t webview, cString script, cString fxpath)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->ExecuteJavascript( toAweString(script), toAweString(fxpath) );
		}
	}

	EXPORT cJSValuePtr_t aws_webview_executeJSWithResult(cWebViewPtr_t webview, cString script, cString fxpath)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			return reinterpret_cast<cJSValuePtr_t>(
					new Awesomium::JSValue(
						view->ExecuteJavascriptWithResult( toAweString(script), toAweString(fxpath) )
					)
				);
		}

		return nullptr;
	}

	EXPORT void aws_webview_setJSMethodHandler(cWebViewPtr_t webview, void* jshandler)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			auto jsh = static_cast<Awesomium::JSMethodHandler*>(jshandler);
			view->set_js_method_handler( jsh );
		}
	}

	EXPORT void aws_webview_didSelectPopupMenuItem(cWebViewPtr_t webview, int idx)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->DidSelectPopupMenuItem( idx );
		}
	}

	EXPORT void aws_webview_didCancelPopupMenu(cWebViewPtr_t webview)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->DidCancelPopupMenu();
		}
	}

	EXPORT void aws_webview_didChooseFiles(cWebViewPtr_t webview, cStringArray arr, bool write)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->DidChooseFiles( toAweStrArray(arr), write );
		}
	}

	EXPORT void aws_webview_didLogin(cWebViewPtr_t webview, int reqId, cString uname, cString pwd)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->DidLogin( reqId, toAweString(uname), toAweString(pwd) );
		}
	}

	EXPORT void aws_webview_didCancelLogin(cWebViewPtr_t webview, int reqId)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->DidCancelLogin(reqId);
		}
	}

	EXPORT void aws_webview_didChooseDownloadPath(cWebViewPtr_t webview, int downloadId, cString path)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->DidChooseDownloadPath( downloadId, toAweString(path) );
		}
	}

	EXPORT void aws_webview_didCancelDownload(cWebViewPtr_t webview, int downloadId)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			view->DidCancelDownload(downloadId);
		}
	}

	// ===============================================
	// JSVALUE

	EXPORT cJSValuePtr_t aws_jsvalue_new_bool(bool val)
	{
		return reinterpret_cast<cJSValuePtr_t>(new Awesomium::JSValue( val ));
	}

	EXPORT cJSValuePtr_t aws_jsvalue_new_int(int val)
	{
		return reinterpret_cast<cJSValuePtr_t>(new Awesomium::JSValue( val ));
	}

	EXPORT cJSValuePtr_t aws_jsvalue_new_double(double val)
	{
		return reinterpret_cast<cJSValuePtr_t>(new Awesomium::JSValue( val ));
	}

	EXPORT cJSValuePtr_t aws_jsvalue_new_string(cString val)
	{
		return reinterpret_cast<cJSValuePtr_t>(new Awesomium::JSValue( toAweString(val) ));
	}

	EXPORT cJSValuePtr_t aws_jsvalue_new_object(cJSObjectPtr_t val)
	{
		auto obj = reinterpret_cast<Awesomium::JSObject*>(val);
		return reinterpret_cast<cJSValuePtr_t>(new Awesomium::JSValue( *obj ));
	}

	EXPORT cJSValuePtr_t aws_jsvalue_new_array(cJSArrayPtr_t val)
	{
		auto arr = reinterpret_cast<Awesomium::JSArray*>(val);
		return reinterpret_cast<cJSValuePtr_t>(new Awesomium::JSValue( *arr ));
	}

	EXPORT cJSValuePtr_t aws_jsvalue_new_jsvalue(cJSValuePtr_t val)
	{
		auto obj = reinterpret_cast<Awesomium::JSValue*>(val);
		return reinterpret_cast<cJSValuePtr_t>(new Awesomium::JSValue( *obj ));
	}

	EXPORT void aws_jsvalue_delete(cJSValuePtr_t jsvalue)
	{
		auto obj = reinterpret_cast<Awesomium::JSValue*>(jsvalue);

		if ( obj ) {
			delete obj;
		}
	}

	EXPORT const cJSValuePtr_t aws_jsvalue_undefined()
	{
		return reinterpret_cast<cJSValuePtr_t>(const_cast<Awesomium::JSValue*>(&Awesomium::JSValue::Undefined()));
	}

	EXPORT const cJSValuePtr_t aws_jsvalue_null()
	{
		return reinterpret_cast<cJSValuePtr_t>(const_cast<Awesomium::JSValue*>(&Awesomium::JSValue::Null()));
	}

	EXPORT bool aws_jsvalue_isBoolean(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->IsBoolean();
		}

		return false;
	}

	EXPORT bool aws_jsvalue_isInteger(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->IsInteger();
		}

		return false;
	}

	EXPORT bool aws_jsvalue_isDouble(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->IsDouble();
		}

		return false;
	}

	EXPORT bool aws_jsvalue_isNumber(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->IsNumber();
		}

		return false;
	}

	EXPORT bool aws_jsvalue_isString(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->IsString();
		}

		return false;
	}

	EXPORT bool aws_jsvalue_isArray(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->IsArray();
		}

		return false;
	}

	EXPORT bool aws_jsvalue_isObject(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->IsObject();
		}

		return false;
	}

	EXPORT bool aws_jsvalue_isNull(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->IsNull();
		}

		return false;
	}

	EXPORT bool aws_jsvalue_isUndefined(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->IsUndefined();
		}

		return false;
	}

	EXPORT cString aws_jsvalue_toString(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return fromAweString( jsv->ToString() );
		}

		return cString();
	}

	EXPORT int aws_jsvalue_toInteger(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->ToInteger();
		}

		return (unsigned)-1;
	}

	EXPORT double aws_jsvalue_toDouble(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->ToDouble();
		}

		return 0;
	}

	EXPORT bool aws_jsvalue_toBoolean(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return jsv->ToBoolean();
		}

		return false;
	}

	EXPORT cJSArrayPtr_t aws_jsvalue_toArray(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return reinterpret_cast <cJSArrayPtr_t>(
					new Awesomium::JSArray( jsv->ToArray() )
				);
		}

		return nullptr;
	}

	EXPORT cJSObjectPtr_t aws_jsvalue_toObject(cJSValuePtr_t jsval)
	{
		auto jsv = reinterpret_cast<Awesomium::JSValue*>(jsval);

		if ( jsv ) {
			return reinterpret_cast <cJSObjectPtr_t>(
					new Awesomium::JSObject( jsv->ToObject() )
				);
		}

		return nullptr;
	}

	// =========================
	// JS OBJECT

	EXPORT cJSObjectPtr_t aws_jsobject_new()
	{
		return reinterpret_cast<cJSObjectPtr_t>(new Awesomium::JSObject());
	}

	EXPORT void aws_jsobject_delete(cJSObjectPtr_t jsobj)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			delete jso;
		}
	}

	EXPORT unsigned aws_jsobject_getRemoteId(cJSObjectPtr_t jsobj)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return jso->remote_id();
		}

		return -1;
	}

	EXPORT int aws_jsobject_getRefCount(cJSObjectPtr_t jsobj)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return jso->ref_count();
		}

		return -1;
	}

	EXPORT int aws_jsobject_getType(cJSObjectPtr_t jsobj)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return jso->type();
		}

		return -1;
	}

	EXPORT const cWebViewPtr_t aws_jsobject_getOwner(cJSObjectPtr_t jsobj)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return reinterpret_cast<cWebViewPtr_t>(jso->owner());
		}

		return nullptr;
	}

	EXPORT bool aws_jsobject_hasProperty(cJSObjectPtr_t jsobj, cString name)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return jso->HasProperty( toAweString(name) );
		}

		return false;
	}

	EXPORT cJSValuePtr_t aws_jsobject_getProperty(cJSObjectPtr_t jsobj, cString name)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return reinterpret_cast<cJSValuePtr_t>(
					new Awesomium::JSValue(jso->GetProperty( toAweString(name) ))
				);
		}

		return nullptr;
	}

	EXPORT void aws_jsobject_setProperty(cJSObjectPtr_t jsobj, cString name, cJSValuePtr_t jsval)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			auto val = reinterpret_cast<Awesomium::JSValue*>(jsval);
			jso->SetProperty( toAweString(name), *val );
		}
	}

	EXPORT void aws_jsobject_removeProperty(cJSObjectPtr_t jsobj, cString name)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			jso->RemoveProperty( toAweString(name) );
		}
	}

	EXPORT cJSArrayPtr_t aws_jsobject_getPropertyNames(cJSObjectPtr_t jsobj)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return reinterpret_cast<cJSArrayPtr_t>(
						new Awesomium::JSArray(jso->GetPropertyNames())
					);
		}

		return nullptr;
	}

	EXPORT cJSArrayPtr_t aws_jsobject_getMethodNames(cJSObjectPtr_t jsobj)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return reinterpret_cast<cJSArrayPtr_t>(
						new Awesomium::JSArray(jso->GetMethodNames())
					);
		}

		return nullptr;
	}

	EXPORT bool aws_jsobject_hasMethod(cJSObjectPtr_t jsobj, cString name)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return jso->HasMethod( toAweString(name) );
		}

		return false;
	}

	EXPORT cJSValuePtr_t aws_jsobject_invoke(cJSObjectPtr_t jsobj, cString name, cJSArrayPtr_t args)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			auto arg = Awesomium::JSArray();

			return reinterpret_cast<cJSValuePtr_t>(
						new Awesomium::JSValue(jso->Invoke( toAweString(name), arg ))
					);
		}

		return nullptr;
	}

	EXPORT cString aws_jsobject_toString(cJSObjectPtr_t jsobj)
	{
		auto jso = reinterpret_cast<Awesomium::JSObject*>(jsobj);

		if ( jso ) {
			return fromAweString(jso->ToString());
		}

		return cString();
	}

	// =========================
	// JS ARRAY

	EXPORT cJSArrayPtr_t aws_jsarray_new_size(unsigned size)
	{
		return reinterpret_cast<cJSArrayPtr_t>(new Awesomium::JSArray(size));
	}

	EXPORT cJSArrayPtr_t aws_jsarray_new()
	{
		return reinterpret_cast<cJSArrayPtr_t>(new Awesomium::JSArray());
	}

	EXPORT void aws_jsarray_size(cJSArrayPtr_t jsarray)
	{
		auto jsa = reinterpret_cast<Awesomium::JSArray*>(jsarray);

		if ( jsa ) {
			delete jsa;
		}
	}

	EXPORT unsigned aws_jsarray_getSize(cJSArrayPtr_t jsarray)
	{
		auto jsa = reinterpret_cast<Awesomium::JSArray*>(jsarray);

		if ( jsa ) {
			return jsa->size();
		}

		return (unsigned)-1;
	}

	EXPORT unsigned aws_jsarray_getCapacity(cJSArrayPtr_t jsarray)
	{
		auto jsa = reinterpret_cast<Awesomium::JSArray*>(jsarray);

		if ( jsa ) {
			return jsa->capacity();
		}

		return (unsigned)-1;
	}

	EXPORT const cJSValuePtr_t aws_jsarray_getItemAt(cJSArrayPtr_t jsarray, unsigned pos)
	{
		auto jsa = reinterpret_cast<Awesomium::JSArray*>(jsarray);

		if ( jsa ) {
			return reinterpret_cast<cJSValuePtr_t>(&jsa->At(pos));
		}

		return nullptr;
	}

	EXPORT void aws_jsarray_push(cJSArrayPtr_t jsarray, cJSValuePtr_t item)
	{
		auto jsa = reinterpret_cast<Awesomium::JSArray*>(jsarray);

		if ( jsa ) {
			auto val = reinterpret_cast<Awesomium::JSValue*>(item);
			jsa->Push(*val);
		}
	}

	EXPORT void aws_jsarray_pop(cJSArrayPtr_t jsarray)
	{
		auto jsa = reinterpret_cast<Awesomium::JSArray*>(jsarray);

		if ( jsa ) {
			jsa->Pop();
		}
	}

	EXPORT void aws_jsarray_insert(cJSArrayPtr_t jsarray, cJSValuePtr_t item, unsigned pos)
	{
		auto jsa = reinterpret_cast<Awesomium::JSArray*>(jsarray);

		if ( jsa ) {
			auto val = reinterpret_cast<Awesomium::JSValue*>(item);
			jsa->Insert(*val,pos);
		}
	}

	EXPORT void aws_jsarray_erase(cJSArrayPtr_t jsarray, unsigned pos)
	{
		auto jsa = reinterpret_cast<Awesomium::JSArray*>(jsarray);

		if ( jsa ) {
			jsa->Erase(pos);
		}
	}

	EXPORT void aws_jsarray_clear(cJSArrayPtr_t jsarray)
	{
		auto jsa = reinterpret_cast<Awesomium::JSArray*>(jsarray);

		if ( jsa ) {
			jsa->Clear();
		}
	}

	// =========================
	// WEB URL

	EXPORT cWebUrlPtr_t aws_weburl_new()
	{
		return reinterpret_cast<cWebUrlPtr_t>(new Awesomium::WebURL());
	}

	EXPORT void aws_weburl_delete(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			delete url;
		}
	}

	EXPORT cWebUrlPtr_t aws_weburl_new_string(cString str)
	{
		return reinterpret_cast<cWebUrlPtr_t>(new Awesomium::WebURL( toAweString(str) ));
	}

	EXPORT cWebUrlPtr_t aws_weburl_new_webstring(cWebStringPtr_t str)
	{
		return reinterpret_cast<cWebUrlPtr_t>(
				new Awesomium::WebURL(
					*reinterpret_cast<Awesomium::WebString*>(str)
				)
			);
	}

	EXPORT bool aws_weburl_isValid(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return url->IsValid();
		}

		return false;
	}

	EXPORT bool aws_weburl_isEmpty(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return url->IsValid();
		}

		return false;
	}

	EXPORT cString aws_weburl_getSpec(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->spec());
		}

		return cString();
	}

	EXPORT cString aws_weburl_getScheme(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->scheme());
		}

		return cString();
	}

	EXPORT cString aws_weburl_getUsername(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->username());
		}

		return cString();
	}

	EXPORT cString aws_weburl_getPassword(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->password());
		}

		return cString();
	}

	EXPORT cString aws_weburl_getHost(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->host());
		}

		return cString();
	}

	EXPORT cString aws_weburl_getPort(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->port());
		}

		return cString();
	}

	EXPORT cString aws_weburl_getPath(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->path());
		}

		return cString();
	}

	EXPORT cString aws_weburl_getQuery(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->query());
		}

		return cString();
	}

	EXPORT cString aws_weburl_getAnchor(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->anchor());
		}

		return cString();
	}

	EXPORT cString aws_weburl_getFilename(cWebUrlPtr_t weburl)
	{
		auto url = reinterpret_cast<Awesomium::WebURL*>(weburl);

		if ( url ) {
			return fromAweString(url->filename());
		}

		return cString();
	}

	// =========================
	// BITMAP SURFACE

	EXPORT cBitSurfacePtr_t aws_bitmapsurface_new(int x, int y)
	{
		return reinterpret_cast<cBitSurfacePtr_t>(new Awesomium::BitmapSurface(x,y));
	}

	EXPORT void aws_bitmapsurface_delete(cBitSurfacePtr_t surface)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			delete bs;
		}
	}

	EXPORT const unsigned char* aws_bitmapsurface_getBuffer(cBitSurfacePtr_t surface)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			return bs->buffer();
		}

		return nullptr;
	}

	EXPORT int aws_bitmapsurface_getWidth(cBitSurfacePtr_t surface)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			return bs->width();
		}

		return -1;
	}

	EXPORT int aws_bitmapsurface_getHeight(cBitSurfacePtr_t surface)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			return bs->height();
		}

		return -1;
	}

	EXPORT int aws_bitmapsurface_getRowSpan(cBitSurfacePtr_t surface)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			return bs->row_span();
		}

		return -1;
	}

	EXPORT bool aws_bitmapsurface_isDirty(cBitSurfacePtr_t surface)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			return bs->is_dirty();
		}

		return false;
	}

	EXPORT void aws_bitmapsurface_setIsDirty(cBitSurfacePtr_t surface, bool val)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			bs->set_is_dirty(val);
		}
	}

	EXPORT void aws_bitmapsurface_copyTo(cBitSurfacePtr_t surface, unsigned char* dst_buffer, int dst_row_span, int dst_depth, bool to_rgba, bool flip_y)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			bs->CopyTo( dst_buffer, dst_row_span, dst_depth, to_rgba, flip_y );
		}
	}

	EXPORT bool aws_bitmapsurface_saveToPNG(cBitSurfacePtr_t surface, cString path, bool preserve_transparency)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			return bs->SaveToPNG( toAweString(path), preserve_transparency );
		}

		return false;
	}

	EXPORT bool aws_bitmapsurface_saveToJPEG(cBitSurfacePtr_t surface, cString path, int quality)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			return bs->SaveToJPEG( toAweString(path), quality );
		}

		return false;
	}

	EXPORT unsigned char aws_bitmapsurface_getAlphaAtPoint(cBitSurfacePtr_t surface, int x, int y)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ) {
			return bs->GetAlphaAtPoint( x, y );
		}

		return -1;
	}

	// ----------------------------------
	// BitmapSurfaceFactory 
	EXPORT cSurfacePtr_t aws_bitmapsurfacefactory_create(cWebViewPtr_t webview, int width, int height)
	{
		auto view = reinterpret_cast<Awesomium::WebView*>(webview);

		if ( view ) {
			Awesomium::BitmapSurfaceFactory bsf;
			return reinterpret_cast<cSurfacePtr_t>(bsf.CreateSurface( view, width, height ));
		}

		return nullptr;
	}

	EXPORT void aws_bitmapsurfacefactory_destroy(cSurfacePtr_t surface)
	{
		auto bs = reinterpret_cast<Awesomium::BitmapSurface*>(surface);

		if ( bs ){
			Awesomium::BitmapSurfaceFactory bsf;
			bsf.DestroySurface( bs );
		}
	}


	// =========================
	// END
}



//=========================
// WEB CONFIG
Awesomium::WebConfig wcToAweConf(cWebConf wc)
{
	Awesomium::WebConfig awc;

	awc.additional_options = toAweStrArray(wc.additional_options);

	awc.plugin_path = toAweString ( wc.plugin_path );

	awc.child_process_path = toAweString ( wc.child_process_path );

	awc.log_level = static_cast<Awesomium::LogLevel>( wc.log_level );

	awc.log_path = toAweString ( wc.log_path );

	awc.package_path = toAweString ( wc.package_path) ;

	awc.remote_debugging_port =  wc.debug_port;

	awc.user_agent = toAweString ( wc.user_agent );

	return awc;
}

//=========================
// WEB PREFERENCES
Awesomium::WebPreferences wpToAwePrefs(cWebPrefs wp)
{
	Awesomium::WebPreferences awp;

	awp.accept_charset = toAweString ( wp.accept_charset );
	awp.accept_language = toAweString ( wp.accept_language );

	awp.allow_file_access_from_file_url = wp.allow_file_access_from_file_url;
	awp.allow_running_insecure_content = wp.allow_running_insecure_content;
	awp.allow_scripts_to_access_clipboard = wp.allow_scripts_to_access_clipboard;
	awp.allow_scripts_to_close_windows = wp.allow_scripts_to_close_windows;
	awp.allow_scripts_to_open_windows = wp.allow_scripts_to_open_windows;
	awp.allow_universal_access_from_file_url = wp.allow_universal_access_from_file_url;

	awp.default_encoding = toAweString ( wp.default_encoding );

	awp.enable_app_cache = wp.enable_app_cache;
	awp.enable_dart = wp.enable_dart;
	awp.enable_databases = wp.enable_databases;
	awp.enable_gpu_acceleration = wp.enable_gpu_acceleration;
	awp.enable_javascript = wp.enable_javascript;
	awp.enable_local_storage = wp.enable_local_storage;
	awp.enable_plugins = wp.enable_plugins;
	awp.enable_remote_fonts = wp.enable_remote_fonts;
	awp.enable_smooth_scrolling = wp.enable_smooth_scrolling;
	awp.enable_web_audio = wp.enable_web_audio;
	awp.enable_web_gl = wp.enable_web_gl;
	awp.enable_web_security = wp.enable_web_security;
	awp.load_images_automatically = wp.load_images_automatically;
	awp.proxy_config = toAweString ( wp.proxy_config );
	awp.shrink_standalone_images_to_fit = wp.shrink_standalone_images_to_fit;
	awp.user_stylesheet = toAweString ( wp.user_stylesheet );

	return awp;
}