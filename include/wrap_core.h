/*
This file is a part of aws_wrap library.
Read LICENSE.TXT and README.TXT provided 
within this package for more information.

Copyright (C) 2012 evilrat
*/

#ifndef _AWE_WRAP_H_
#define _AWE_WRAP_H_

#if defined(WRAPEXPORT)
#	ifdef _WIN32
#		ifdef _MSC_VER
#			define EXPORT __declspec(dllexport)
#		endif
#	else
#		define EXPORT 
#	endif
#else
#	ifdef _WIN32
#		ifdef _MSC_VER
#			define EXPORT __declspec(dllimport)
#		endif
#	else
#		define EXPORT
#	endif
#endif

#ifndef __cplusplus
# include <stdbool.h>
// just in case if someone want to use visual studio's c89 -_-
# ifndef bool
#	define bool int
#	define true 1
#	define false 0
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

	
	/// null terminated wchar16 string
	typedef unsigned short* nullstring16_t;



	/// this is UTF-8 string, Awesomium uses UTF-16 internally, it's sucks.
	/// so here is the nice and simple UTF-8 string, all string
	/// conversions will be made automatically when needed
	typedef struct _cString
	{
		unsigned len;
		char* str;
	} cString;

	typedef struct _cStringArray
	{
		cString** ptr;
		unsigned size;
	} cStringArray;

	typedef struct _cWebConf
	{
		int log_level;
		int debug_port;
		unsigned addOptNum;

		cString user_agent;
		cString plugin_path;
		cString child_process_path;
		cString log_path;
		cString package_path;

		cStringArray additional_options;
	} cWebConf;

	typedef struct _cWebPrefs
	{
		cString accept_charset;
		cString accept_language;

		cString default_encoding;
		cString proxy_config;
		cString user_stylesheet;

		bool allow_file_access_from_file_url;
		bool allow_running_insecure_content;
		bool allow_scripts_to_access_clipboard;
		bool allow_scripts_to_close_windows;
		bool allow_scripts_to_open_windows;
		bool allow_universal_access_from_file_url;

		bool enable_app_cache;
		bool enable_dart;
		bool enable_databases;
		bool enable_gpu_acceleration;
		bool enable_javascript;
		bool enable_local_storage;
		bool enable_plugins;
		bool enable_remote_fonts;
		bool enable_smooth_scrolling;
		bool enable_web_audio;
		bool enable_web_gl;
		bool enable_web_security;

		bool load_images_automatically;

		bool shrink_standalone_images_to_fit;
	} cWebPrefs;


	// ---------------------------------------
	// BELOW ARE THE POINTERS TO ACTUAL AWESOMIUM CPP OBJECTS
	// YOU CAN USE THEM IF UR LANGUAGE SUPPORT CPP CLASSES(MUAHAHAH!!)
	// ---------------------------------------

	typedef struct _cWebView cWebView_t, *cWebViewPtr_t;

	typedef struct _cWebCore cWebCore_t, *cWebCorePtr_t;

	typedef struct _cWebUrl cWebUrl_t, *cWebUrlPtr_t;

	typedef struct _cWebSession cWebSession_t, *cWebSessionPtr_t;


	typedef struct _cWebString cWebString_t, *cWebStringPtr_t;

	typedef struct _cWebStringArray cWebStringArray_t, *cWebStringArrayPtr_t;


	typedef struct _cJSObject cJSObject_t, *cJSObjectPtr_t;

	typedef struct _cJSArray cJSArray_t, *cJSArrayPtr_t;

	typedef struct _cJSValue cJSValue_t, *cJSValuePtr_t;


	typedef struct _cSurface cSurface_t, *cSurfacePtr_t;

	typedef struct _cBitSurface cBitSurface_t, *cBitSurfacePtr_t;

	typedef struct _cSurfaceFactory cSurfaceFactory_t, *cSurfaceFactoryPtr_t;

	typedef struct _cResInterceptor cResInterceptor_t, *cResInterceptorPtr_t;



	// WEB STRING
	EXPORT   cWebStringPtr_t         aws_webstring_new ();
	EXPORT   cWebStringPtr_t         aws_webstring_new_substring (cWebStringPtr_t srcstring, unsigned start, unsigned len);
	EXPORT   cWebStringPtr_t         aws_webstring_new_utf8 (const char* string, unsigned len);

	EXPORT   void                    aws_webstring_delete (cWebStringPtr_t string);

	EXPORT   unsigned                aws_webstring_to_utf8 (cWebStringPtr_t string, char* dest);
	EXPORT   cString                 aws_webstring_to_cstring (cWebStringPtr_t string);

	// ====== WEB CORE =======
	EXPORT   const cWebCorePtr_t     aws_webcore_init (cWebConf wc);
	EXPORT   const cWebCorePtr_t     aws_webcore_initDefault ();
	EXPORT   void                    aws_webcore_shutdown ();
	EXPORT   const cWebCorePtr_t     aws_webcore_instance ();
	EXPORT   cWebSessionPtr_t        aws_webcore_createWebSession (cWebCorePtr_t webcore, cString path, cWebPrefs wp);
	EXPORT   cWebViewPtr_t           aws_webcore_createWebView (cWebCorePtr_t webcore, int w, int h, cWebSessionPtr_t sess, int type);
	EXPORT   void                    aws_webcore_setSurfaceFactory (cWebCorePtr_t webcore, cSurfaceFactoryPtr_t factory);
	EXPORT   cSurfaceFactoryPtr_t    aws_webcore_getSurfaceFactory (cWebCorePtr_t webcore);
	EXPORT   void                    aws_webcore_setResourceInterceptor (cWebCorePtr_t webcore, cResInterceptorPtr_t interceptor);
	EXPORT   cResInterceptorPtr_t    aws_webcore_getResourceInterceptor (cWebCorePtr_t webcore);
	EXPORT   void                    aws_webcore_update (cWebCorePtr_t webcore);
	EXPORT   const char*             aws_webcore_versionString (cWebCorePtr_t webcore);

	// ====== WEB VIEW =======
	EXPORT   void                    aws_webview_destroy (cWebViewPtr_t webview);
	EXPORT   int                     aws_webview_getType (cWebViewPtr_t webview);
	EXPORT   int                     aws_webview_getProcId (cWebViewPtr_t webview);
	EXPORT   void*                   aws_webview_getHandle (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_setParentWindow (cWebViewPtr_t webview, void* window);
	EXPORT   void*                   aws_webview_getParentWindow (cWebViewPtr_t webview);
	EXPORT   void*                   aws_webview_getWindow (cWebViewPtr_t webview);

	EXPORT   void                    aws_webview_setViewListener (cWebViewPtr_t webview, void* listener);
	EXPORT   void                    aws_webview_setLoadListener (cWebViewPtr_t webview, void* listener);
	EXPORT   void                    aws_webview_setProcessListener (cWebViewPtr_t webview, void* listener);
	EXPORT   void                    aws_webview_setMenuListener (cWebViewPtr_t webview, void* listener);
	EXPORT   void                    aws_webview_setPrintListener (cWebViewPtr_t webview, void* listener);
	EXPORT   void                    aws_webview_setDownloadListener (cWebViewPtr_t webview, void* listener);
	EXPORT   void                    aws_webview_setIMEListener (cWebViewPtr_t webview, void* listener);

	EXPORT   void*                   aws_webview_getViewListener (cWebViewPtr_t webview);
	EXPORT   void*                   aws_webview_getLoadListener (cWebViewPtr_t webview);
	EXPORT   void*                   aws_webview_getProcessListener (cWebViewPtr_t webview);
	EXPORT   void*                   aws_webview_getMenuListener (cWebViewPtr_t webview);
	EXPORT   void*                   aws_webview_getDialogListener (cWebViewPtr_t webview);
	EXPORT   void*                   aws_webview_getPrintListener (cWebViewPtr_t webview);
	EXPORT   void*                   aws_webview_getDownloadListener (cWebViewPtr_t webview);
	EXPORT   void*                   aws_webview_getIMEListener (cWebViewPtr_t webview);

	EXPORT   void                    aws_webview_loadURL (cWebViewPtr_t webview, cWebUrlPtr_t url);
	EXPORT   void                    aws_webview_goBack (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_goForward(cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_goToHistoryOffset (cWebViewPtr_t webview, int offset);
	EXPORT   void                    aws_webview_stop (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_reload (cWebViewPtr_t webview, bool ignoreCache);
	EXPORT   bool                    aws_webview_canGoBack (cWebViewPtr_t webview);
	EXPORT   bool                    aws_webview_canGoForward (cWebViewPtr_t webview);
	EXPORT   cSurfacePtr_t           aws_webview_getSurface (cWebViewPtr_t webview);
	EXPORT   cWebUrlPtr_t            aws_webview_getURL (cWebViewPtr_t webview);
	EXPORT   cWebStringPtr_t         aws_webview_getTitle (cWebViewPtr_t webview);
	EXPORT   cWebSessionPtr_t        aws_webview_getSession (cWebViewPtr_t webview);
	EXPORT   bool                    aws_webview_isLoading (cWebViewPtr_t webview);
	EXPORT   bool                    aws_webview_isCrashed (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_resize (cWebViewPtr_t webview, int x, int y);
	EXPORT   void                    aws_webview_setTransparent (cWebViewPtr_t webview, bool state);
	EXPORT   bool                    aws_webview_isTransparent (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_pauseRendering (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_resumeRendering (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_focus (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_unfocus (cWebViewPtr_t webview);
	EXPORT   int                     aws_webview_focusedElementType (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_injectMouseMove (cWebViewPtr_t webview, int mx, int my);
	EXPORT   void                    aws_webview_injectMouseButton (cWebViewPtr_t webview, int button, bool down);
	EXPORT   void                    aws_webview_injectMouseWheel (cWebViewPtr_t webview, int wx, int wy);
	EXPORT   void                    aws_webview_injectKeyboardEvent (cWebViewPtr_t webview, void* keyevent);
	EXPORT   void                    aws_webview_injectTouchEvent (cWebViewPtr_t webview, void* touchevent);
	EXPORT   void                    aws_webview_activateIME (cWebViewPtr_t webview, bool state);
	EXPORT   void                    aws_webview_setIMEComposition (cWebViewPtr_t webview, cString target_string, int cursorpos, int targetstart, int tartgetend);
	EXPORT   void                    aws_webview_cancelIMEComposition (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_undo (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_redo (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_cut (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_copy (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_copyImageAt (cWebViewPtr_t webview, int x, int y);
	EXPORT   void                    aws_webview_paste (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_pasteAndMatchStyle (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_selectAll (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_printToFile (cWebViewPtr_t webview, cString outDir, void* printconf);
	EXPORT   int                     aws_webview_lastError (cWebViewPtr_t webview);
	EXPORT   cJSValuePtr_t           aws_webview_createGlobalJSObject (cWebViewPtr_t webview, cString objname);
	EXPORT   void                    aws_webview_executeJS (cWebViewPtr_t webview, cString script, cString fxpath);
	EXPORT   cJSValuePtr_t           aws_webview_executeJSWithResult (cWebViewPtr_t webview, cString script, cString fxpath);
	EXPORT   void                    aws_webview_setJSMethodHandler (cWebViewPtr_t webview, void* jshandler);
	EXPORT   void                    aws_webview_didSelectPopupMenuItem (cWebViewPtr_t webview, int idx);
	EXPORT   void                    aws_webview_didCancelPopupMenu (cWebViewPtr_t webview);
	EXPORT   void                    aws_webview_didChooseFiles (cWebViewPtr_t webview, cStringArray arr, bool write);
	EXPORT   void                    aws_webview_didLogin (cWebViewPtr_t webview, int reqId, cString uname, cString pwd);
	EXPORT   void                    aws_webview_didCancelLogin (cWebViewPtr_t webview, int reqId);
	EXPORT   void                    aws_webview_didChooseDownloadPath (cWebViewPtr_t webview, int downloadId, cString path);
	EXPORT   void                    aws_webview_didCancelDownload (cWebViewPtr_t webview, int downloadId);

	// ====== JS VALUE =======
	EXPORT   cJSValuePtr_t           aws_jsvalue_new_bool (bool val);
	EXPORT   cJSValuePtr_t           aws_jsvalue_new_int (int val);
	EXPORT   cJSValuePtr_t           aws_jsvalue_new_double (double val);
	EXPORT   cJSValuePtr_t           aws_jsvalue_new_string (cString val);
	EXPORT   cJSValuePtr_t           aws_jsvalue_new_object (cJSObjectPtr_t val);
	EXPORT   cJSValuePtr_t           aws_jsvalue_new_array (cJSArrayPtr_t val);
	EXPORT   cJSValuePtr_t           aws_jsvalue_new_jsvalue (cJSValuePtr_t val);

	EXPORT   void                    aws_jsvalue_delete (cJSValuePtr_t jsvalue);

	EXPORT   const cJSValuePtr_t     aws_jsvalue_undefined ();
	EXPORT   const cJSValuePtr_t     aws_jsvalue_null ();

	EXPORT   bool                    aws_jsvalue_isBoolean (cJSValuePtr_t jsval);
	EXPORT   bool                    aws_jsvalue_isInteger (cJSValuePtr_t jsval);
	EXPORT   bool                    aws_jsvalue_isDouble (cJSValuePtr_t jsval);
	EXPORT   bool                    aws_jsvalue_isNumber (cJSValuePtr_t jsval);
	EXPORT   bool                    aws_jsvalue_isString (cJSValuePtr_t jsval);
	EXPORT   bool                    aws_jsvalue_isArray (cJSValuePtr_t jsval);
	EXPORT   bool                    aws_jsvalue_isObject (cJSValuePtr_t jsval);
	EXPORT   bool                    aws_jsvalue_isNull (cJSValuePtr_t jsval);
	EXPORT   bool                    aws_jsvalue_isUndefined (cJSValuePtr_t jsval);

	EXPORT   cString                 aws_jsvalue_toString (cJSValuePtr_t jsval);
	EXPORT   int                     aws_jsvalue_toInteger (cJSValuePtr_t jsval);
	EXPORT   double                  aws_jsvalue_toDouble (cJSValuePtr_t jsval);
	EXPORT   bool                    aws_jsvalue_toBoolean (cJSValuePtr_t jsval);
	EXPORT   cJSArrayPtr_t           aws_jsvalue_toArray (cJSValuePtr_t jsval);
	EXPORT   cJSObjectPtr_t          aws_jsvalue_toObject (cJSValuePtr_t jsval);

	// ====== JS OBJECT =======
	EXPORT   cJSObjectPtr_t          aws_jsobject_new ();

	EXPORT   void                    aws_jsobject_delete (cJSObjectPtr_t jsobj);

	EXPORT   unsigned                aws_jsobject_getRemoteId (cJSObjectPtr_t jsobj);
	EXPORT   int                     aws_jsobject_getRefCount (cJSObjectPtr_t jsobj);
	EXPORT   int                     aws_jsobject_getType (cJSObjectPtr_t jsobj);
	EXPORT   const cWebViewPtr_t     aws_jsobject_getOwner (cJSObjectPtr_t jsobj);

	EXPORT   bool                    aws_jsobject_hasProperty (cJSObjectPtr_t jsobj, cString name);
	EXPORT   cJSValuePtr_t           aws_jsobject_getProperty (cJSObjectPtr_t jsobj, cString name);
	EXPORT   void                    aws_jsobject_setProperty (cJSObjectPtr_t jsobj, cString name, cJSValuePtr_t jsval);
	EXPORT   void                    aws_jsobject_removeProperty (cJSObjectPtr_t jsobj, cString name);

	EXPORT   cJSArrayPtr_t           aws_jsobject_getPropertyNames (cJSObjectPtr_t jsobj);
	EXPORT   cJSArrayPtr_t           aws_jsobject_getMethodNames (cJSObjectPtr_t jsobj);
	EXPORT   bool                    aws_jsobject_hasMethod (cJSObjectPtr_t jsobj, cString name);
	EXPORT   cJSValuePtr_t           aws_jsobject_invoke (cJSObjectPtr_t jsobj, cString name, cJSArrayPtr_t args);
	EXPORT   cString                 aws_jsobject_toString (cJSObjectPtr_t jsobj);

	// ====== JS ARRAY =======
	EXPORT   cJSArrayPtr_t           aws_jsarray_new_size (unsigned size);
	EXPORT   cJSArrayPtr_t           aws_jsarray_new ();

	EXPORT   void                    aws_jsarray_delete (cJSArrayPtr_t jsarray);

	EXPORT   unsigned                aws_jsarray_getSize (cJSArrayPtr_t jsarray);
	EXPORT   unsigned                aws_jsarray_getCapacity (cJSArrayPtr_t jsarray);
	EXPORT   const cJSValuePtr_t     aws_jsarray_getItemAt (cJSArrayPtr_t jsarray, unsigned pos);
	EXPORT   void                    aws_jsarray_push (cJSArrayPtr_t jsarray, cJSValuePtr_t item);
	EXPORT   void                    aws_jsarray_pop (cJSArrayPtr_t jsarray);
	EXPORT   void                    aws_jsarray_insert (cJSArrayPtr_t jsarray, cJSValuePtr_t item, unsigned pos);
	EXPORT   void                    aws_jsarray_erase (cJSArrayPtr_t jsarray, unsigned pos);
	EXPORT   void                    aws_jsarray_clear (cJSArrayPtr_t jsarray);

	// ====== WEB URL =======
	EXPORT   cWebUrlPtr_t            aws_weburl_new ();
	EXPORT   cWebUrlPtr_t            aws_weburl_new_string (cString str);
	EXPORT   cWebUrlPtr_t            aws_weburl_new_webstring (cWebStringPtr_t str);

	EXPORT   void                    aws_weburl_delete (cWebUrlPtr_t weburl);
	
	EXPORT   bool                    aws_weburl_isValid (cWebUrlPtr_t weburl);
	EXPORT   bool                    aws_weburl_isEmpty (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getSpec (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getScheme (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getUsername (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getPassword (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getHost (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getPort (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getPath (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getQuery (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getAnchor (cWebUrlPtr_t weburl);
	EXPORT   cString                 aws_weburl_getFilename (cWebUrlPtr_t weburl);

	// ====== BITMAP SURFACE =======
	EXPORT   cBitSurfacePtr_t        aws_bitmapsurface_new (int x, int y);

	EXPORT   void                    aws_bitmapsurface_delete (cBitSurfacePtr_t surface);

	EXPORT   const unsigned char*    aws_bitmapsurface_getBuffer (cBitSurfacePtr_t surface);
	EXPORT   int                     aws_bitmapsurface_getWidth (cBitSurfacePtr_t surface);
	EXPORT   int                     aws_bitmapsurface_getHeight (cBitSurfacePtr_t surface);
	EXPORT   int                     aws_bitmapsurface_getRowSpan (cBitSurfacePtr_t surface);
	EXPORT   bool                    aws_bitmapsurface_isDirty (cBitSurfacePtr_t surface);
	EXPORT   void                    aws_bitmapsurface_setIsDirty (cBitSurfacePtr_t surface, bool val);
	EXPORT   void                    aws_bitmapsurface_copyTo (cBitSurfacePtr_t surface, unsigned char* dst_buffer, int dst_row_span, int dst_depth, bool to_rgba, bool flip_y);
	EXPORT   bool                    aws_bitmapsurface_saveToPNG (cBitSurfacePtr_t surface, cString path, bool preserve_transparency);
	EXPORT   bool                    aws_bitmapsurface_saveToJPEG (cBitSurfacePtr_t surface, cString path, int quality);
	EXPORT   unsigned char           aws_bitmapsurface_getAlphaAtPoint (cBitSurfacePtr_t surface, int x, int y);

	// --- factory methods, untested
	EXPORT   cSurfaceFactoryPtr_t    aws_surfacefactory_new ();
	EXPORT   void                    aws_surfacefactory_delete (cSurfaceFactoryPtr_t factory);

	EXPORT   cSurfacePtr_t           aws_bitmapsurface_create (cWebViewPtr_t webview, int width, int height);
	EXPORT   void                    aws_bitmapsurface_destroy (cSurfacePtr_t surface);

#ifdef __cplusplus
}
#endif

#endif