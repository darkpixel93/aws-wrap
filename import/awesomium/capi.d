/*
This file is a part of aws_wrap library.
Read LICENSE.TXT and README.TXT provided 
within this package for more information.

Copyright (C) 2012 evilrat
*/

module awesomium.capi;

extern(C):

struct cString
{
	uint len;
	char* str;
}

struct cStringArray
{
	cString** ptr;
	uint size;
}

struct cWebConf
{
	int log_level;
	int debug_port;
	uint addOptNum;

	cString user_agent;
	cString plugin_path;
	cString child_process_path;
	cString log_path;
	cString package_path;

	cStringArray additional_options;
}

struct cWebPrefs
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
}


// WEB VIEW
struct cWebView;
alias cWebView cWebView_t;
alias cWebView* cWebViewPtr_t;

// WEB CORE
struct cWebCore;
alias cWebCore cWebCore_t;
alias cWebCore* cWebCorePtr_t;

// WEB URL
struct cWebUrl;
alias cWebUrl cWebUrl_t;
alias cWebUrl* cWebUrlPtr_t;

// WEB STRING
struct cWebString;
alias cWebString cWebString_t;
alias cWebString* cWebStringPtr_t;

// WEB STRING ARRAY
struct cWebStringArray;
alias cWebStringArray cWebStringArray_t;
alias cWebStringArray* cWebStringArrayPtr_t;

// WEB SESSION
struct cWebSession;
alias cWebSession cWebSession_t;
alias cWebSession* cWebSessionPtr_t;

// JS OBJECT
struct cJSObject;
alias cJSObject cJSObject_t;
alias cJSObject* cJSObjectPtr_t;

// JS ARRAY
struct cJSArray;
alias cJSArray cJSArray_t;
alias cJSArray* cJSArrayPtr_t;

// JS VALUE
struct cJSValue;
alias cJSValue cJSValue_t;
alias cJSValue* cJSValuePtr_t;

// this and below disabled due to some problems with struct sizes 
// SURFACE
version(none) 
{
struct cSurface;
alias cSurface cSurface_t;
alias cSurface* cSurfacePtr_t;
}
alias void* cSurfacePtr_t;

// BIT SURFACE
version(none)
{
struct cBitSurface;
alias cBitSurface cBitSurface_t;
alias cBitSurface* cBitSurfacePtr_t;
}

alias void* cBitSurfacePtr_t;

// SURFACE FACTORY
struct cSurfaceFactory;
//alias cSurfaceFactory cSurfaceFactory_t;
alias cSurfaceFactory* cSurfaceFactoryPtr_t;

// RESOURCE INSPECTOR
struct cResInterceptor;
alias cResInterceptor cResInterceptor_t;
alias cResInterceptor* cResInterceptorPtr_t;


// UTIL
cWebStringPtr_t         aws_webstring_new_utf8 (const(char)* string, uint len);
uint                    aws_webstring_to_utf8 (cWebStringPtr_t string, char* dest);

cString                 aws_webstring_to_cstring (cWebStringPtr_t string);

/// call this when you are done with string to release buffer
void                    aws_cstring_release (cString str);

// ====== WEB CORE =======
const(cWebCorePtr_t)    aws_webcore_init (cWebConf wc);
const(cWebCorePtr_t)    aws_webcore_initDefault ();
void                    aws_webcore_shutdown ();
const(cWebCorePtr_t)    aws_webcore_instance ();
cWebSessionPtr_t        aws_webcore_createWebSession (cWebCorePtr_t webcore, cString path, cWebPrefs wp);
cWebViewPtr_t           aws_webcore_createWebView (cWebCorePtr_t webcore, int w, int h, cWebSessionPtr_t sess, int type);
void                    aws_webcore_setSurfaceFactory (cWebCorePtr_t webcore, cSurfaceFactoryPtr_t factory);
cSurfaceFactoryPtr_t    aws_webcore_getSurfaceFactory (cWebCorePtr_t webcore);
void                    aws_webcore_setResourceInterceptor (cWebCorePtr_t webcore, cResInterceptorPtr_t interceptor);
cResInterceptorPtr_t    aws_webcore_getResourceInterceptor (cWebCorePtr_t webcore);
void                    aws_webcore_update (cWebCorePtr_t webcore);
const(char)*            aws_webcore_versionString (cWebCorePtr_t webcore);

// ====== WEB VIEW =======
void                    aws_webview_destroy (cWebViewPtr_t webview);
int                     aws_webview_getType (cWebViewPtr_t webview);
int                     aws_webview_getProcId (cWebViewPtr_t webview);
void*                   aws_webview_getHandle (cWebViewPtr_t webview);
void                    aws_webview_setParentWindow (cWebViewPtr_t webview, void* window);
void*                   aws_webview_getParentWindow (cWebViewPtr_t webview);
void*                   aws_webview_getWindow (cWebViewPtr_t webview);

void                    aws_webview_setViewListener (cWebViewPtr_t webview, void* listener);
void                    aws_webview_setLoadListener (cWebViewPtr_t webview, void* listener);
void                    aws_webview_setProcessListener (cWebViewPtr_t webview, void* listener);
void                    aws_webview_setMenuListener (cWebViewPtr_t webview, void* listener);
void                    aws_webview_setPrintListener (cWebViewPtr_t webview, void* listener);
void                    aws_webview_setDownloadListener (cWebViewPtr_t webview, void* listener);
void                    aws_webview_setIMEListener (cWebViewPtr_t webview, void* listener);

void*                   aws_webview_getViewListener (cWebViewPtr_t webview);
void*                   aws_webview_getLoadListener (cWebViewPtr_t webview);
void*                   aws_webview_getProcessListener (cWebViewPtr_t webview);
void*                   aws_webview_getMenuListener (cWebViewPtr_t webview);
void*                   aws_webview_getDialogListener (cWebViewPtr_t webview);
void*                   aws_webview_getPrintListener (cWebViewPtr_t webview);
void*                   aws_webview_getDownloadListener (cWebViewPtr_t webview);
void*                   aws_webview_getIMEListener (cWebViewPtr_t webview);

void                    aws_webview_loadURL (cWebViewPtr_t webview, cWebUrlPtr_t url);
void                    aws_webview_goBack (cWebViewPtr_t webview);
void                    aws_webview_goForward(cWebViewPtr_t webview);
void                    aws_webview_goToHistoryOffset (cWebViewPtr_t webview, int offset);
void                    aws_webview_stop (cWebViewPtr_t webview);
void                    aws_webview_reload (cWebViewPtr_t webview, bool ignoreCache);
bool                    aws_webview_canGoBack (cWebViewPtr_t webview);
bool                    aws_webview_canGoForward (cWebViewPtr_t webview);
cSurfacePtr_t           aws_webview_getSurface (cWebViewPtr_t webview);
cWebUrlPtr_t            aws_webview_getURL (cWebViewPtr_t webview);
cWebStringPtr_t         aws_webview_getTitle (cWebViewPtr_t webview);
cWebSessionPtr_t        aws_webview_getSession (cWebViewPtr_t webview);
bool                    aws_webview_isLoading (cWebViewPtr_t webview);
bool                    aws_webview_isCrashed (cWebViewPtr_t webview);
void                    aws_webview_resize (cWebViewPtr_t webview, int x, int y);
void                    aws_webview_setTransparent (cWebViewPtr_t webview, bool state);
bool                    aws_webview_isTransparent (cWebViewPtr_t webview);
void                    aws_webview_pauseRendering (cWebViewPtr_t webview);
void                    aws_webview_resumeRendering (cWebViewPtr_t webview);
void                    aws_webview_focus (cWebViewPtr_t webview);
void                    aws_webview_unfocus (cWebViewPtr_t webview);
int                     aws_webview_focusedElementType (cWebViewPtr_t webview);
void                    aws_webview_injectMouseMove (cWebViewPtr_t webview, int mx, int my);
void                    aws_webview_injectMouseButton (cWebViewPtr_t webview, int button, bool down);
void                    aws_webview_injectMouseWheel (cWebViewPtr_t webview, int wx, int wy);
void                    aws_webview_injectKeyboardEvent (cWebViewPtr_t webview, void* keyevent);
void                    aws_webview_injectTouchEvent (cWebViewPtr_t webview, void* touchevent);
void                    aws_webview_activateIME (cWebViewPtr_t webview, bool state);
void                    aws_webview_setIMEComposition (cWebViewPtr_t webview, cString target_string, int cursorpos, int targetstart, int tartgetend);
void                    aws_webview_cancelIMEComposition (cWebViewPtr_t webview);
void                    aws_webview_undo (cWebViewPtr_t webview);
void                    aws_webview_redo (cWebViewPtr_t webview);
void                    aws_webview_cut (cWebViewPtr_t webview);
void                    aws_webview_copy (cWebViewPtr_t webview);
void                    aws_webview_copyImageAt (cWebViewPtr_t webview, int x, int y);
void                    aws_webview_paste (cWebViewPtr_t webview);
void                    aws_webview_pasteAndMatchStyle (cWebViewPtr_t webview);
void                    aws_webview_selectAll (cWebViewPtr_t webview);
void                    aws_webview_printToFile (cWebViewPtr_t webview, cString outDir, void* printconf);
int                     aws_webview_lastError (cWebViewPtr_t webview);
cJSValuePtr_t           aws_webview_createGlobalJSObject (cWebViewPtr_t webview, cString objname);
void                    aws_webview_executeJS (cWebViewPtr_t webview, cString script, cString fxpath);
cJSValuePtr_t           aws_webview_executeJSWithResult (cWebViewPtr_t webview, cString script, cString fxpath);
void                    aws_webview_setJSMethodHandler (cWebViewPtr_t webview, void* jshandler);
void                    aws_webview_didSelectPopupMenuItem (cWebViewPtr_t webview, int idx);
void                    aws_webview_didCancelPopupMenu (cWebViewPtr_t webview);
void                    aws_webview_didChooseFiles (cWebViewPtr_t webview, cStringArray arr, bool write);
void                    aws_webview_didLogin (cWebViewPtr_t webview, int reqId, cString uname, cString pwd);
void                    aws_webview_didCancelLogin (cWebViewPtr_t webview, int reqId);
void                    aws_webview_didChooseDownloadPath (cWebViewPtr_t webview, int downloadId, cString path);
void                    aws_webview_didCancelDownload (cWebViewPtr_t webview, int downloadId);

// ====== JS VALUE =======
cJSValuePtr_t           aws_jsvalue_new_bool (bool val);
cJSValuePtr_t           aws_jsvalue_new_int (int val);
cJSValuePtr_t           aws_jsvalue_new_double (double val);
cJSValuePtr_t           aws_jsvalue_new_string (cString val);
cJSValuePtr_t           aws_jsvalue_new_object (cJSObjectPtr_t val);
cJSValuePtr_t           aws_jsvalue_new_array (cJSArrayPtr_t val);
cJSValuePtr_t           aws_jsvalue_new_jsvalue (cJSValuePtr_t val);

void                    aws_jsvalue_delete (cJSValuePtr_t jsvalue);

const(cJSValuePtr_t)    aws_jsvalue_undefined ();
const(cJSValuePtr_t)    aws_jsvalue_null ();

bool                    aws_jsvalue_isBoolean (cJSValuePtr_t jsval);
bool                    aws_jsvalue_isInteger (cJSValuePtr_t jsval);
bool                    aws_jsvalue_isDouble (cJSValuePtr_t jsval);
bool                    aws_jsvalue_isNumber (cJSValuePtr_t jsval);
bool                    aws_jsvalue_isString (cJSValuePtr_t jsval);
bool                    aws_jsvalue_isArray (cJSValuePtr_t jsval);
bool                    aws_jsvalue_isObject (cJSValuePtr_t jsval);
bool                    aws_jsvalue_isNull (cJSValuePtr_t jsval);
bool                    aws_jsvalue_isUndefined (cJSValuePtr_t jsval);

cString                 aws_jsvalue_toString (cJSValuePtr_t jsval);
int                     aws_jsvalue_toInteger (cJSValuePtr_t jsval);
double                  aws_jsvalue_toDouble (cJSValuePtr_t jsval);
bool                    aws_jsvalue_toBoolean (cJSValuePtr_t jsval);
cJSArrayPtr_t           aws_jsvalue_toArray (cJSValuePtr_t jsval);
cJSObjectPtr_t          aws_jsvalue_toObject (cJSValuePtr_t jsval);

// ====== JS OBJECT =======
cJSObjectPtr_t          aws_jsobject_new ();

void                    aws_jsobject_delete (cJSObjectPtr_t jsobj);

uint                    aws_jsobject_getRemoteId (cJSObjectPtr_t jsobj);
int                     aws_jsobject_getRefCount (cJSObjectPtr_t jsobj);
int                     aws_jsobject_getType (cJSObjectPtr_t jsobj);
const(cWebViewPtr_t)    aws_jsobject_getOwner (cJSObjectPtr_t jsobj);

bool                    aws_jsobject_hasProperty (cJSObjectPtr_t jsobj, cString name);
cJSValuePtr_t           aws_jsobject_getProperty (cJSObjectPtr_t jsobj, cString name);
void                    aws_jsobject_setProperty (cJSObjectPtr_t jsobj, cString name, cJSValuePtr_t jsval);
void                    aws_jsobject_removeProperty (cJSObjectPtr_t jsobj, cString name);

cJSArrayPtr_t           aws_jsobject_getPropertyNames (cJSObjectPtr_t jsobj);
cJSArrayPtr_t           aws_jsobject_getMethodNames (cJSObjectPtr_t jsobj);
bool                    aws_jsobject_hasMethod (cJSObjectPtr_t jsobj, cString name);
cJSValuePtr_t           aws_jsobject_invoke (cJSObjectPtr_t jsobj, cString name, cJSArrayPtr_t args);
cString                 aws_jsobject_toString (cJSObjectPtr_t jsobj);

// ====== JS ARRAY =======
cJSArrayPtr_t           aws_jsarray_new_size (uint size);
cJSArrayPtr_t           aws_jsarray_new ();

void                    aws_jsarray_delete (cJSArrayPtr_t jsarray);

uint                    aws_jsarray_getSize (cJSArrayPtr_t jsarray);
uint                    aws_jsarray_getCapacity (cJSArrayPtr_t jsarray);
const(cJSValuePtr_t)    aws_jsarray_getItemAt (cJSArrayPtr_t jsarray, uint pos);
void                    aws_jsarray_push (cJSArrayPtr_t jsarray, cJSValuePtr_t item);
void                    aws_jsarray_pop (cJSArrayPtr_t jsarray);
void                    aws_jsarray_insert (cJSArrayPtr_t jsarray, cJSValuePtr_t item, uint pos);
void                    aws_jsarray_erase (cJSArrayPtr_t jsarray, uint pos);
void                    aws_jsarray_clear (cJSArrayPtr_t jsarray);

// ====== WEB URL =======
cWebUrlPtr_t            aws_weburl_new ();
cWebUrlPtr_t            aws_weburl_new_string (cString str);
cWebUrlPtr_t            aws_weburl_new_webstring (cWebStringPtr_t str);

void                    aws_weburl_delete (cWebUrlPtr_t weburl);

bool                    aws_weburl_isValid (cWebUrlPtr_t weburl);
bool                    aws_weburl_isEmpty (cWebUrlPtr_t weburl);
cString                 aws_weburl_getSpec (cWebUrlPtr_t weburl);
cString                 aws_weburl_getScheme (cWebUrlPtr_t weburl);
cString                 aws_weburl_getUsername (cWebUrlPtr_t weburl);
cString                 aws_weburl_getPassword (cWebUrlPtr_t weburl);
cString                 aws_weburl_getHost (cWebUrlPtr_t weburl);
cString                 aws_weburl_getPort (cWebUrlPtr_t weburl);
cString                 aws_weburl_getPath (cWebUrlPtr_t weburl);
cString                 aws_weburl_getQuery (cWebUrlPtr_t weburl);
cString                 aws_weburl_getAnchor (cWebUrlPtr_t weburl);
cString                 aws_weburl_getFilename (cWebUrlPtr_t weburl);

// ====== BITMAP SURFACE =======
cBitSurfacePtr_t        aws_bitmapsurface_new (int x, int y);

void                    aws_bitmapsurface_delete (cBitSurfacePtr_t surface);

const(ubyte)*           aws_bitmapsurface_getBuffer (cBitSurfacePtr_t surface);
int                     aws_bitmapsurface_getWidth (cBitSurfacePtr_t surface);
int                     aws_bitmapsurface_getHeight (cBitSurfacePtr_t surface);
int                     aws_bitmapsurface_getRowSpan (cBitSurfacePtr_t surface);
bool                    aws_bitmapsurface_isDirty (cBitSurfacePtr_t surface);
void                    aws_bitmapsurface_setIsDirty (cBitSurfacePtr_t surface, bool val);
void                    aws_bitmapsurface_copyTo (cBitSurfacePtr_t surface, ubyte* dst_buffer, int dst_row_span, int dst_depth, bool to_rgba, bool flip_y);
bool                    aws_bitmapsurface_saveToPNG (cBitSurfacePtr_t surface, cString path, bool preserve_transparency);
bool                    aws_bitmapsurface_saveToJPEG (cBitSurfacePtr_t surface, cString path, int quality);
ubyte                   aws_bitmapsurface_getAlphaAtPoint (cBitSurfacePtr_t surface, int x, int y);

// --- factory methods, untested
cSurfaceFactoryPtr_t    aws_surfacefactory_new ();
void                    aws_surfacefactory_delete (cSurfaceFactoryPtr_t factory);

cSurfacePtr_t           aws_bitmapsurface_create (cWebViewPtr_t webview, int width, int height);
void                    aws_bitmapsurface_destroy (cSurfacePtr_t surface);
