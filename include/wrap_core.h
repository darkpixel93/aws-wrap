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
#			define AWS_EXPORT __declspec(dllexport)
#		endif
#	else
#		define AWS_EXPORT 
#	endif
#else
#	ifdef _WIN32
#		ifdef _MSC_VER
#			define AWS_EXPORT __declspec(dllimport)
#		endif
#	else
#		define AWS_EXPORT
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

#ifdef _WIN32
#	include <Windows.h>
#endif

#ifdef __APPLE__
#	import <Cocoa/Cocoa.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/// awesomium int64
	typedef long long aint64;

	/// null terminated wchar16 string
	typedef unsigned short* nullstr16_t;
	
	typedef unsigned short wchar16;



	/// this is UTF-8 string, Awesomium uses UTF-16 internally, it's sucks.
	/// so here is the nice and simple UTF-8 string, all string
	/// conversions will be made automatically when needed
	typedef struct _cString
	{
		unsigned len;
		char* str;
	} cString;

	typedef struct _cRect
	{
		int x, y, width, height;
	} cRect;

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

	/// this structure holds Awesomium WebKeyboardEvent data
	typedef struct _cKeyEventData
	{
		int type;
		int modifiers;

		int virtual_key_code;
		int native_key_code;

		char key_identifier[20];

		wchar16 text[4];
		wchar16 unmodified_text[4];

		bool is_system_key;
	} cKeyEventData;

	// ---------------------------------------
	// BELOW ARE THE POINTERS TO ACTUAL AWESOMIUM CPP OBJECTS
	// YOU CAN USE THEM IF UR LANGUAGE SUPPORT CPP CLASSES(MUAHAHAH!!)
	// ---------------------------------------

	typedef struct _cWebView *cWebViewPtr_t;

	typedef struct _cWebCore  *cWebCorePtr_t;

	typedef struct _cWebUrl  *cWebUrlPtr_t;

	typedef struct _cWebSession  *cWebSessionPtr_t;

	
	typedef struct _cDataSource *cDataSourcePtr_t;


	typedef struct _cWebString  *cWebStringPtr_t;

	typedef struct _cWebStringArray  *cWebStringArrayPtr_t;

	typedef struct _cWebMenuItemArray *cWebMenuItemArrayPtr_t;


	typedef struct _cJSObject  *cJSObjectPtr_t;

	typedef struct _cJSArray  *cJSArrayPtr_t;

	typedef struct _cJSValue  *cJSValuePtr_t;

	typedef struct _cJSMethodHandler *cJSMethodHandlerPtr_t;


	typedef struct _cKeyboardEvt *cKeyboardEvtPtr_t;

	typedef struct _cTouchEvt *cTouchEvtPtr_t;


	typedef struct _cSurface  *cSurfacePtr_t;

	typedef struct _cBitSurface  *cBitSurfacePtr_t;

	typedef struct _cSurfaceFactory  *cSurfaceFactoryPtr_t;


	typedef struct _cResInterceptor  *cResInterceptorPtr_t;

	typedef struct _cResRequest  *cResRequestPtr_t;

	typedef struct _cResResponse  *cResResponsePtr_t;

	typedef struct _cUploadElement *cUploadElementPtr_t;


	typedef struct _cWebView_onView *cWebView_onViewPtr_t;

	typedef struct _cWebView_onLoad *cWebView_onLoadPtr_t;

	typedef struct _cWebView_onProcess *cWebView_onProcessPtr_t;

	typedef struct _cWebView_onMenu *cWebView_onMenuPtr_t;

	typedef struct _cWebView_onDialog *cWebView_onDialogPtr_t;

	typedef struct _cWebView_onPrint *cWebView_onPrintPtr_t;

	typedef struct _cWebView_onDownload *cWebView_onDownloadPtr_t;

	typedef struct _cWebView_onIME *cWebView_onIMEPtr_t;



	// =======================

	typedef struct _cWebPopupMenuInfo {
		cRect bounds;  ///< The location to display the menu
		int item_height;         ///< The height of each menu item
		double item_font_size;   ///< The font-size of each menu item
		int selected_item;       ///< The index of the currently-selected item
		cWebMenuItemArrayPtr_t items;  ///< The actual menu items
		bool right_aligned;      ///< Whether or not the menu is right-aligned
	} cWebPopupMenuInfo_t;

	typedef struct _cWebContextMenuInfo {
		int pos_x;                 ///< The x-coordinate of the menu's position.
		int pos_y;                 ///< The y-coordinate of the menu's position.
		int media_type;      ///< The type of media (if any) that was clicked.
		int media_state;           ///< The state of the media (if any).
		cWebUrlPtr_t link_url;           ///< The URL of the link (if any).
		cWebUrlPtr_t src_url;            ///< The URL of the media (if any).
		cWebUrlPtr_t page_url;           ///< The URL of the web-page.
		cWebUrlPtr_t frame_url;          ///< The URL of the frame.
		aint64 frame_id;            ///< The ID of the frame.
		cWebStringPtr_t selection_text;  ///< The selected text (if any).
		bool is_editable;          ///< Whether or not this node is editable.
		int edit_flags;            ///< Which edit actions can be performed
	} cWebContextMenuInfo_t;

	typedef struct _cWebFileChooserInfo {
		int mode;       ///< The type of dialog to display
		cWebStringPtr_t title;               ///< Title of the dialog
		cWebStringPtr_t default_file_name;   ///< Suggested file name for the dialog
		cWebStringArrayPtr_t accept_types;   ///< Valid mime type
	} cWebFileChooserInfo_t;

	typedef struct _cWebLoginDialogInfo {
		int request_id;         ///< The unique ID of the request.
		cWebStringPtr_t request_url;  ///< The URL of the web-page requesting login.
		bool is_proxy;          ///< Whether or not this is a proxy auth.
		cWebStringPtr_t host;         ///< The hostname of the server.
		unsigned short port;    ///< The port of the server.
		cWebStringPtr_t scheme;       ///< The scheme of the server.
		cWebStringPtr_t realm;        ///< The realm of the server
	} cWebLoginDialogInfo_t;

	// ===== CALLBACKS ======

	// JS EVENTS
	/// this method gets called on javascript method call which doesn't return value
	typedef void (*jshnd_onMethodCall)(cWebViewPtr_t caller, unsigned remoteObjId, cWebStringPtr_t methodName, cJSArrayPtr_t args, void* userPointer);

	/// this method gets called on javascript method call which returns value
	typedef cJSValuePtr_t (*jshnd_onMethodCallValue)(cWebViewPtr_t caller, unsigned remoteObjId, cWebStringPtr_t methodName, cJSArrayPtr_t args, void* userPointer);

	///
	/// this structure stores JavaScript callback method handlers
	typedef struct _cJSMethodCallback_t 
	{
		///
		/// this function will be called whenever JS handler attached to view,
		/// and javascript function without returning value called.
		/// it may be NULL, in this case it will be ignored
		jshnd_onMethodCall call;

		///
		/// this function will be called whenever JS handler attached to view,
		/// and javascript function which returns value called.
		/// it may be NULL, in this case it will be ignored
		jshnd_onMethodCallValue callval;

		///
		/// you could use this to set object instance pointer or something
		void* userptr;
	} cJSMethodCallback_t;

	// --------------------------------
	// WEBVIEW EVENTS

	// -- view
	typedef void (*wvview_onChangeTitle)(cWebViewPtr_t caller, const cWebStringPtr_t title, void* userPointer);
	typedef void (*wvview_onChangeAddressBar)(cWebViewPtr_t caller, const cWebUrlPtr_t title, void* userPointer);
	typedef void (*wvview_onChangeTooltip)(cWebViewPtr_t caller, const cWebStringPtr_t tooltip, void* userPointer);
	typedef void (*wvview_onChangeTargetURL)(cWebViewPtr_t caller, const cWebUrlPtr_t url, void* userPointer);
	typedef void (*wvview_onChangeCursor)(cWebViewPtr_t caller, int cursor, void* userPointer);
	typedef void (*wvview_onChangeFocus)(cWebViewPtr_t caller, int focused_type, void* userPointer);
	typedef void (*wvview_onShowCreatedWebView)(cWebViewPtr_t caller, cWebViewPtr_t new_view, 
												const cWebUrlPtr_t opener_url, const cWebUrlPtr_t target_url,
												const cRect* initial_pos, bool is_popup, void* userPointer) ;


	typedef struct _cWebView_View
	{
		wvview_onChangeTitle title;
		wvview_onChangeAddressBar address;
		wvview_onChangeTooltip tooltip;
		wvview_onChangeTargetURL url;
		wvview_onChangeCursor cursor;
		wvview_onChangeFocus focus;
		wvview_onShowCreatedWebView show;

		/// you could use this to set object instance or something
		void* userPointer;
	} cWebView_View;



	// -- load
	typedef void (*wvload_onBeginLoadingFrame)(cWebViewPtr_t caller, aint64 frame_id,
									bool is_main_frame, const cWebUrlPtr_t url,
									bool is_error_page, void* userptr);
	typedef void (*wvload_onFailLoadingFrame)(cWebViewPtr_t caller, aint64 frame_id,
									bool is_main_frame, const cWebUrlPtr_t url,
									int error_code, const cWebStringPtr_t error_desc,
									void* userptr);
	typedef void (*wvload_onFinishLoadingFrame)(cWebViewPtr_t caller, aint64 frame_id, bool is_main_frame,
                                    const cWebUrlPtr_t url, void* userptr);
	typedef void (*wvload_onDocumentReady)(cWebViewPtr_t caller, const cWebUrlPtr_t url, void* userptr);


	typedef struct _cWebView_Load
	{
		wvload_onBeginLoadingFrame begin;
		wvload_onFailLoadingFrame fail;
		wvload_onFinishLoadingFrame finish;
		wvload_onDocumentReady ready;

		void* userPointer;
	} cWebView_Load;

	

	// -- process
	typedef void (*wvproc_onUnresponsive)(cWebViewPtr_t caller, void* userptr);
	typedef void (*wvproc_onResponsive)(cWebViewPtr_t caller, void* userptr);
	typedef void (*wvproc_onCrashed)(cWebViewPtr_t caller, int status, void* userptr);


	typedef struct _cWebView_Process
	{
		wvproc_onUnresponsive unresponsive;
		wvproc_onResponsive responsive;
		wvproc_onCrashed crashed;

		void* userPointer;
	} cWebView_Process;


	// -- menu
	typedef void (*wvmenu_onShowPopupMenu)(cWebViewPtr_t caller, cWebPopupMenuInfo_t menu_info, void* userptr);
	typedef void (*wvmenu_onShowContextMenu)(cWebViewPtr_t caller, cWebContextMenuInfo_t menu_info, void* userptr);


	typedef struct _cWebView_Menu
	{
		wvmenu_onShowPopupMenu popup;
		wvmenu_onShowContextMenu context;

		void* userPointer;
	} cWebView_Menu;

	
	// -- dialog
	typedef void (*wvdialog_onShowFileChooser)(cWebViewPtr_t caller, cWebFileChooserInfo_t chooser_info, void* userptr);
	typedef void (*wvdialog_onShowLoginDialog)(cWebViewPtr_t caller, cWebLoginDialogInfo_t dialog_info, void* userptr);

	typedef struct _cWebView_Dialog
	{
		wvdialog_onShowFileChooser file;
		wvdialog_onShowLoginDialog login;

		void* userPointer;
	} cWebView_Dialog;


	// -- print
	typedef void (*wvprint_onRequestPrint)(cWebViewPtr_t caller, void* userptr);
	typedef void (*wvprint_onFailPrint)(cWebViewPtr_t caller, int request_id, void* userptr);
	typedef void (*wvprint_onFinishPrint)(cWebViewPtr_t caller, int request_id, const cWebStringArrayPtr_t, void* userptr);

	typedef struct _cWebView_Print
	{
		wvprint_onRequestPrint request;
		wvprint_onFailPrint fail;
		wvprint_onFinishPrint finish;

		void* userPointer;
	} cWebView_Print;

	// -- download
	typedef void (*wvdownload_onRequestDownload)(cWebViewPtr_t caller, int download_id,
													const cWebUrlPtr_t url,
													const cWebStringPtr_t suggested_filename,
													const cWebStringPtr_t mime_type,
													void* userptr);
	typedef void (*wvdownload_onUpdateDownload)(cWebViewPtr_t caller,
                                int download_id,
                                aint64 total_bytes,
                                aint64 received_bytes,
                                aint64 current_speed,
								void* userptr);

	typedef void (*wvdownload_onFinishDownload)(cWebViewPtr_t caller,
                                int download_id,
                                const cWebUrlPtr_t url,
                                const cWebStringPtr_t saved_path,
								void* userptr);

	typedef struct _cWebView_Download
	{
		wvdownload_onRequestDownload request;
		wvdownload_onUpdateDownload update;
		wvdownload_onFinishDownload finish;

		void* userPointer;
	} cWebView_Download;

	
	// -- IME
	typedef void (*wvime_onUpdateIME)(cWebViewPtr_t caller, int type, int caret_x, int caret_y, void* userptr);
	typedef void (*wvime_onCancelIME)(cWebViewPtr_t caller, void* userptr);
	typedef void (*wvime_onChangeIMERange)(cWebViewPtr_t caller, unsigned int start, 
									unsigned int end, void* userptr);


	typedef struct _cWebView_IME
	{
		wvime_onUpdateIME update;
		wvime_onCancelIME cancel;
		wvime_onChangeIMERange range;

		void* userPointer;
	} cWebView_IME;


	// --------------------------------

	// ====== WEB STRING ======
	AWS_EXPORT   cWebStringPtr_t         aws_webstring_new ();
	AWS_EXPORT   cWebStringPtr_t         aws_webstring_new_substring (cWebStringPtr_t srcstring, unsigned start, unsigned len);
	AWS_EXPORT   cWebStringPtr_t         aws_webstring_new_utf8 (const char* string, unsigned len);
	AWS_EXPORT   cWebStringPtr_t         aws_webstring_new_webstring (cWebStringPtr_t string);

	AWS_EXPORT   void                    aws_webstring_delete (cWebStringPtr_t string);

	AWS_EXPORT   unsigned                aws_webstring_to_utf8 (cWebStringPtr_t string, char* dest, unsigned length);
	AWS_EXPORT   const wchar16*          aws_webstring_data (cWebStringPtr_t string);
	AWS_EXPORT   cString                 aws_webstring_to_cstring (cWebStringPtr_t string);

	// ====== WEB CORE =======
	AWS_EXPORT   const cWebCorePtr_t     aws_webcore_init (cWebConf wc);
	AWS_EXPORT   const cWebCorePtr_t     aws_webcore_initDefault ();
	AWS_EXPORT   void                    aws_webcore_shutdown ();
	AWS_EXPORT   const cWebCorePtr_t     aws_webcore_instance ();
	AWS_EXPORT   cWebSessionPtr_t        aws_webcore_createWebSession (cWebCorePtr_t webcore, cWebStringPtr_t path, cWebPrefs wp);
	AWS_EXPORT   cWebViewPtr_t           aws_webcore_createWebView (cWebCorePtr_t webcore, int w, int h, cWebSessionPtr_t sess, int type);
	AWS_EXPORT   void                    aws_webcore_setSurfaceFactory (cWebCorePtr_t webcore, cSurfaceFactoryPtr_t factory);
	AWS_EXPORT   cSurfaceFactoryPtr_t    aws_webcore_getSurfaceFactory (cWebCorePtr_t webcore);
	AWS_EXPORT   void                    aws_webcore_setResourceInterceptor (cWebCorePtr_t webcore, cResInterceptorPtr_t interceptor);
	AWS_EXPORT   cResInterceptorPtr_t    aws_webcore_getResourceInterceptor (cWebCorePtr_t webcore);
	AWS_EXPORT   void                    aws_webcore_update (cWebCorePtr_t webcore);
	AWS_EXPORT   const char*             aws_webcore_versionString (cWebCorePtr_t webcore);

	// ====== WEB VIEW =======
	AWS_EXPORT   void                    aws_webview_destroy (cWebViewPtr_t webview);
	AWS_EXPORT   int                     aws_webview_getType (cWebViewPtr_t webview);
	AWS_EXPORT   int                     aws_webview_getProcId (cWebViewPtr_t webview);
	AWS_EXPORT   void*                   aws_webview_getHandle (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_setParentWindow (cWebViewPtr_t webview, void* window);
	AWS_EXPORT   void*                   aws_webview_getParentWindow (cWebViewPtr_t webview);
	AWS_EXPORT   void*                   aws_webview_getWindow (cWebViewPtr_t webview);

	AWS_EXPORT   void                    aws_webview_setViewListener (cWebViewPtr_t webview, cWebView_onViewPtr_t listener);
	AWS_EXPORT   void                    aws_webview_setLoadListener (cWebViewPtr_t webview, cWebView_onLoadPtr_t listener);
	AWS_EXPORT   void                    aws_webview_setProcessListener (cWebViewPtr_t webview, cWebView_onProcessPtr_t listener);
	AWS_EXPORT   void                    aws_webview_setMenuListener (cWebViewPtr_t webview, cWebView_onMenuPtr_t listener);
	AWS_EXPORT   void                    aws_webview_setDialogListener (cWebViewPtr_t webview, cWebView_onDialogPtr_t listener);
	AWS_EXPORT   void                    aws_webview_setPrintListener (cWebViewPtr_t webview, cWebView_onPrintPtr_t listener);
	AWS_EXPORT   void                    aws_webview_setDownloadListener (cWebViewPtr_t webview, cWebView_onDownloadPtr_t listener);
	AWS_EXPORT   void                    aws_webview_setIMEListener (cWebViewPtr_t webview, cWebView_onIMEPtr_t listener);

	AWS_EXPORT   cWebView_onViewPtr_t    aws_webview_getViewListener (cWebViewPtr_t webview);
	AWS_EXPORT   cWebView_onLoadPtr_t    aws_webview_getLoadListener (cWebViewPtr_t webview);
	AWS_EXPORT   cWebView_onProcessPtr_t aws_webview_getProcessListener (cWebViewPtr_t webview);
	AWS_EXPORT   cWebView_onMenuPtr_t    aws_webview_getMenuListener (cWebViewPtr_t webview);
	AWS_EXPORT   cWebView_onDialogPtr_t  aws_webview_getDialogListener (cWebViewPtr_t webview);
	AWS_EXPORT   cWebView_onPrintPtr_t   aws_webview_getPrintListener (cWebViewPtr_t webview);
	AWS_EXPORT   cWebView_onDownloadPtr_t aws_webview_getDownloadListener (cWebViewPtr_t webview);
	AWS_EXPORT   cWebView_onIMEPtr_t     aws_webview_getIMEListener (cWebViewPtr_t webview);

	AWS_EXPORT   void                    aws_webview_loadURL (cWebViewPtr_t webview, cWebUrlPtr_t url);
	AWS_EXPORT   void                    aws_webview_goBack (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_goForward(cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_goToHistoryOffset (cWebViewPtr_t webview, int offset);
	AWS_EXPORT   void                    aws_webview_stop (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_reload (cWebViewPtr_t webview, bool ignoreCache);
	AWS_EXPORT   bool                    aws_webview_canGoBack (cWebViewPtr_t webview);
	AWS_EXPORT   bool                    aws_webview_canGoForward (cWebViewPtr_t webview);
	AWS_EXPORT   cSurfacePtr_t           aws_webview_getSurface (cWebViewPtr_t webview);
	AWS_EXPORT   cWebUrlPtr_t            aws_webview_getURL (cWebViewPtr_t webview);
	AWS_EXPORT   cWebStringPtr_t         aws_webview_getTitle (cWebViewPtr_t webview);
	AWS_EXPORT   cWebSessionPtr_t        aws_webview_getSession (cWebViewPtr_t webview);
	AWS_EXPORT   bool                    aws_webview_isLoading (cWebViewPtr_t webview);
	AWS_EXPORT   bool                    aws_webview_isCrashed (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_resize (cWebViewPtr_t webview, int x, int y);
	AWS_EXPORT   void                    aws_webview_setTransparent (cWebViewPtr_t webview, bool state);
	AWS_EXPORT   bool                    aws_webview_isTransparent (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_pauseRendering (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_resumeRendering (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_focus (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_unfocus (cWebViewPtr_t webview);
	AWS_EXPORT   int                     aws_webview_focusedElementType (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_injectMouseMove (cWebViewPtr_t webview, int mx, int my);
	AWS_EXPORT   void                    aws_webview_injectMouseButton (cWebViewPtr_t webview, int button, bool down);
	AWS_EXPORT   void                    aws_webview_injectMouseWheel (cWebViewPtr_t webview, int wx, int wy);
	AWS_EXPORT   void                    aws_webview_injectKeyboardEvent (cWebViewPtr_t webview, cKeyboardEvtPtr_t keyevent);
	AWS_EXPORT   void                    aws_webview_injectTouchEvent (cWebViewPtr_t webview, cTouchEvtPtr_t touchevent);
	AWS_EXPORT   void                    aws_webview_activateIME (cWebViewPtr_t webview, bool state);
	AWS_EXPORT   void                    aws_webview_setIMEComposition (cWebViewPtr_t webview, cWebStringPtr_t target_string, int cursorpos, int targetstart, int tartgetend);
	AWS_EXPORT   void                    aws_webview_cancelIMEComposition (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_undo (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_redo (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_cut (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_copy (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_copyImageAt (cWebViewPtr_t webview, int x, int y);
	AWS_EXPORT   void                    aws_webview_paste (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_pasteAndMatchStyle (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_selectAll (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_printToFile (cWebViewPtr_t webview, cWebStringPtr_t outDir, void* printconf);
	AWS_EXPORT   int                     aws_webview_lastError (cWebViewPtr_t webview);
	AWS_EXPORT   cJSValuePtr_t           aws_webview_createGlobalJSObject (cWebViewPtr_t webview, cWebStringPtr_t objname);
	AWS_EXPORT   void                    aws_webview_executeJS (cWebViewPtr_t webview, cWebStringPtr_t script, cWebStringPtr_t fxpath);
	AWS_EXPORT   cJSValuePtr_t           aws_webview_executeJSWithResult (cWebViewPtr_t webview, cWebStringPtr_t script, cWebStringPtr_t fxpath);
	AWS_EXPORT   void                    aws_webview_setJSMethodHandler (cWebViewPtr_t webview, cJSMethodHandlerPtr_t jshandler);
	AWS_EXPORT   void                    aws_webview_didSelectPopupMenuItem (cWebViewPtr_t webview, int idx);
	AWS_EXPORT   void                    aws_webview_didCancelPopupMenu (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_didChooseFiles (cWebViewPtr_t webview, cWebStringArrayPtr_t arr, bool write);
	AWS_EXPORT   void                    aws_webview_didLogin (cWebViewPtr_t webview, int reqId, cWebStringPtr_t uname, cWebStringPtr_t pwd);
	AWS_EXPORT   void                    aws_webview_didCancelLogin (cWebViewPtr_t webview, int reqId);
	AWS_EXPORT   void                    aws_webview_didChooseDownloadPath (cWebViewPtr_t webview, int downloadId, cWebStringPtr_t path);
	AWS_EXPORT   void                    aws_webview_didCancelDownload (cWebViewPtr_t webview, int downloadId);

	// ====== JS VALUE =======
	AWS_EXPORT   cJSValuePtr_t           aws_jsvalue_new_bool (bool val);
	AWS_EXPORT   cJSValuePtr_t           aws_jsvalue_new_int (int val);
	AWS_EXPORT   cJSValuePtr_t           aws_jsvalue_new_double (double val);
	AWS_EXPORT   cJSValuePtr_t           aws_jsvalue_new_string (cWebStringPtr_t val);
	AWS_EXPORT   cJSValuePtr_t           aws_jsvalue_new_object (cJSObjectPtr_t val);
	AWS_EXPORT   cJSValuePtr_t           aws_jsvalue_new_array (cJSArrayPtr_t val);
	AWS_EXPORT   cJSValuePtr_t           aws_jsvalue_new_jsvalue (cJSValuePtr_t val);

	AWS_EXPORT   void                    aws_jsvalue_delete (cJSValuePtr_t jsvalue);

	AWS_EXPORT   const cJSValuePtr_t     aws_jsvalue_undefined ();
	AWS_EXPORT   const cJSValuePtr_t     aws_jsvalue_null ();

	AWS_EXPORT   bool                    aws_jsvalue_isBoolean (cJSValuePtr_t jsval);
	AWS_EXPORT   bool                    aws_jsvalue_isInteger (cJSValuePtr_t jsval);
	AWS_EXPORT   bool                    aws_jsvalue_isDouble (cJSValuePtr_t jsval);
	AWS_EXPORT   bool                    aws_jsvalue_isNumber (cJSValuePtr_t jsval);
	AWS_EXPORT   bool                    aws_jsvalue_isString (cJSValuePtr_t jsval);
	AWS_EXPORT   bool                    aws_jsvalue_isArray (cJSValuePtr_t jsval);
	AWS_EXPORT   bool                    aws_jsvalue_isObject (cJSValuePtr_t jsval);
	AWS_EXPORT   bool                    aws_jsvalue_isNull (cJSValuePtr_t jsval);
	AWS_EXPORT   bool                    aws_jsvalue_isUndefined (cJSValuePtr_t jsval);

	AWS_EXPORT   cWebStringPtr_t         aws_jsvalue_toString (cJSValuePtr_t jsval);
	AWS_EXPORT   int                     aws_jsvalue_toInteger (cJSValuePtr_t jsval);
	AWS_EXPORT   double                  aws_jsvalue_toDouble (cJSValuePtr_t jsval);
	AWS_EXPORT   bool                    aws_jsvalue_toBoolean (cJSValuePtr_t jsval);
	AWS_EXPORT   cJSArrayPtr_t           aws_jsvalue_toArray (cJSValuePtr_t jsval);
	AWS_EXPORT   cJSObjectPtr_t          aws_jsvalue_toObject (cJSValuePtr_t jsval);

	// ====== JS OBJECT =======
	AWS_EXPORT   cJSObjectPtr_t          aws_jsobject_new ();

	AWS_EXPORT   void                    aws_jsobject_delete (cJSObjectPtr_t jsobj);

	AWS_EXPORT   unsigned                aws_jsobject_getRemoteId (cJSObjectPtr_t jsobj);
	AWS_EXPORT   int                     aws_jsobject_getRefCount (cJSObjectPtr_t jsobj);
	AWS_EXPORT   int                     aws_jsobject_getType (cJSObjectPtr_t jsobj);
	AWS_EXPORT   const cWebViewPtr_t     aws_jsobject_getOwner (cJSObjectPtr_t jsobj);

	AWS_EXPORT   bool                    aws_jsobject_hasProperty (cJSObjectPtr_t jsobj, cWebStringPtr_t name);
	AWS_EXPORT   cJSValuePtr_t           aws_jsobject_getProperty (cJSObjectPtr_t jsobj, cWebStringPtr_t name);
	AWS_EXPORT   void                    aws_jsobject_setProperty (cJSObjectPtr_t jsobj, cWebStringPtr_t name, cJSValuePtr_t jsval);
	AWS_EXPORT   void                    aws_jsobject_removeProperty (cJSObjectPtr_t jsobj, cWebStringPtr_t name);

	AWS_EXPORT   cJSArrayPtr_t           aws_jsobject_getPropertyNames (cJSObjectPtr_t jsobj);
	AWS_EXPORT   cJSArrayPtr_t           aws_jsobject_getMethodNames (cJSObjectPtr_t jsobj);
	AWS_EXPORT   bool                    aws_jsobject_hasMethod (cJSObjectPtr_t jsobj, cWebStringPtr_t name);
	AWS_EXPORT   cJSValuePtr_t           aws_jsobject_invoke (cJSObjectPtr_t jsobj, cWebStringPtr_t name, cJSArrayPtr_t args);
	AWS_EXPORT   cWebStringPtr_t         aws_jsobject_toString (cJSObjectPtr_t jsobj);

	// ====== JS ARRAY =======
	AWS_EXPORT   cJSArrayPtr_t           aws_jsarray_new_size (unsigned size);
	AWS_EXPORT   cJSArrayPtr_t           aws_jsarray_new ();

	AWS_EXPORT   void                    aws_jsarray_delete (cJSArrayPtr_t jsarray);

	AWS_EXPORT   unsigned                aws_jsarray_getSize (cJSArrayPtr_t jsarray);
	AWS_EXPORT   unsigned                aws_jsarray_getCapacity (cJSArrayPtr_t jsarray);
	AWS_EXPORT   const cJSValuePtr_t     aws_jsarray_getItemAt (cJSArrayPtr_t jsarray, unsigned pos);
	AWS_EXPORT   void                    aws_jsarray_push (cJSArrayPtr_t jsarray, cJSValuePtr_t item);
	AWS_EXPORT   void                    aws_jsarray_pop (cJSArrayPtr_t jsarray);
	AWS_EXPORT   void                    aws_jsarray_insert (cJSArrayPtr_t jsarray, cJSValuePtr_t item, unsigned pos);
	AWS_EXPORT   void                    aws_jsarray_erase (cJSArrayPtr_t jsarray, unsigned pos);
	AWS_EXPORT   void                    aws_jsarray_clear (cJSArrayPtr_t jsarray);

	// ====== WEB URL =======
	AWS_EXPORT   cWebUrlPtr_t            aws_weburl_new ();
	AWS_EXPORT   cWebUrlPtr_t            aws_weburl_new_cstring (cString str);
	AWS_EXPORT   cWebUrlPtr_t            aws_weburl_new_webstring (cWebStringPtr_t str);

	AWS_EXPORT   void                    aws_weburl_delete (cWebUrlPtr_t weburl);
	
	AWS_EXPORT   bool                    aws_weburl_isValid (cWebUrlPtr_t weburl);
	AWS_EXPORT   bool                    aws_weburl_isEmpty (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getSpec (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getScheme (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getUsername (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getPassword (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getHost (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getPort (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getPath (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getQuery (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getAnchor (cWebUrlPtr_t weburl);
	AWS_EXPORT   cWebStringPtr_t         aws_weburl_getFilename (cWebUrlPtr_t weburl);

	// ====== WEB SESSION =======
	AWS_EXPORT   void                    aws_websession_release (cWebSessionPtr_t sess);

	AWS_EXPORT   bool                    aws_websession_isOnDisk (cWebSessionPtr_t sess);
	AWS_EXPORT   cWebStringPtr_t         aws_websession_getDataPath (cWebSessionPtr_t sess);
	AWS_EXPORT   cWebPrefs               aws_websession_getPreferences (cWebSessionPtr_t sess);
	AWS_EXPORT   void                    aws_websession_addDataSource (cWebSessionPtr_t sess, cWebStringPtr_t asset_host, cDataSourcePtr_t source);
	AWS_EXPORT   void                    aws_websession_setCookie (cWebSessionPtr_t sess, cWebUrlPtr_t url, cWebStringPtr_t asset_host, bool http_only, bool force_session);
	AWS_EXPORT   void                    aws_websession_clearCookies (cWebSessionPtr_t sess);


	// ====== BITMAP SURFACE =======
	AWS_EXPORT   cBitSurfacePtr_t        aws_bitmapsurface_new (int x, int y);

	AWS_EXPORT   void                    aws_bitmapsurface_delete (cBitSurfacePtr_t surface);

	AWS_EXPORT   const unsigned char*    aws_bitmapsurface_getBuffer (cBitSurfacePtr_t surface);
	AWS_EXPORT   int                     aws_bitmapsurface_getWidth (cBitSurfacePtr_t surface);
	AWS_EXPORT   int                     aws_bitmapsurface_getHeight (cBitSurfacePtr_t surface);
	AWS_EXPORT   int                     aws_bitmapsurface_getRowSpan (cBitSurfacePtr_t surface);
	AWS_EXPORT   bool                    aws_bitmapsurface_isDirty (cBitSurfacePtr_t surface);
	AWS_EXPORT   void                    aws_bitmapsurface_setIsDirty (cBitSurfacePtr_t surface, bool val);
	AWS_EXPORT   void                    aws_bitmapsurface_copyTo (cBitSurfacePtr_t surface, unsigned char* dst_buffer, int dst_row_span, int dst_depth, bool to_rgba, bool flip_y);
	AWS_EXPORT   bool                    aws_bitmapsurface_saveToPNG (cBitSurfacePtr_t surface, cWebStringPtr_t path, bool preserve_transparency);
	AWS_EXPORT   bool                    aws_bitmapsurface_saveToJPEG (cBitSurfacePtr_t surface, cWebStringPtr_t path, int quality);
	AWS_EXPORT   unsigned char           aws_bitmapsurface_getAlphaAtPoint (cBitSurfacePtr_t surface, int x, int y);

	// --- factory methods, untested
	AWS_EXPORT   cSurfaceFactoryPtr_t    aws_surfacefactory_new ();
	AWS_EXPORT   void                    aws_surfacefactory_delete (cSurfaceFactoryPtr_t factory);

	AWS_EXPORT   cSurfacePtr_t           aws_bitmapsurface_create (cWebViewPtr_t webview, int width, int height);
	AWS_EXPORT   void                    aws_bitmapsurface_destroy (cSurfacePtr_t surface);

	//================================
	// JS HANDLER STUFF

	AWS_EXPORT   void                    aws_webview_setInternalJSHandler (cWebViewPtr_t webview);

	AWS_EXPORT   void                    aws_jshandler_addCallback (cWebViewPtr_t webview, cJSMethodCallback_t callback);
	AWS_EXPORT   void                    aws_jshandler_removeCallback (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_jshandler_removeCallbackAll ();

	//================================
	// WEBVIEW HANDLERS STUFF

	// this functions sets internal wrapper listener which allow setting callbacks to that events
	AWS_EXPORT   void                    aws_webview_setInternalLoadHandler (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_setInternalViewHandler (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_setInternalPrintHandler (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_setInternalProcessHandler (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_setInternalMenuHandler (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_setInternalDownloadHandler (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_setInternalDialogHandler (cWebViewPtr_t webview);
	AWS_EXPORT   void                    aws_webview_setInternalIMEHandler (cWebViewPtr_t webview);

	// set callbacks
	AWS_EXPORT   void                    aws_webview_setListenerLoad (cWebViewPtr_t webview, cWebView_Load loadclbks);
	AWS_EXPORT   void                    aws_webview_setListenerView (cWebViewPtr_t webview, cWebView_View viewclbks);
	AWS_EXPORT   void                    aws_webview_setListenerPrint (cWebViewPtr_t webview, cWebView_Print prntclbks);
	AWS_EXPORT   void                    aws_webview_setListenerProcess (cWebViewPtr_t webview, cWebView_Process procclbks);
	AWS_EXPORT   void                    aws_webview_setListenerMenu (cWebViewPtr_t webview, cWebView_Menu menuclbks);
	AWS_EXPORT   void                    aws_webview_setListenerDialog (cWebViewPtr_t webview, cWebView_Dialog dlgclbks);
	AWS_EXPORT   void                    aws_webview_setListenerDownload (cWebViewPtr_t webview, cWebView_Download dlclbks);
	AWS_EXPORT   void                    aws_webview_setListenerIME (cWebViewPtr_t webview, cWebView_IME imeclbks);

	//================================
	// RESOURCE INTERCEPTOR STUFF

	// ===== RESOURCE RESPONSE ======
	AWS_EXPORT   cResResponsePtr_t       aws_resresponse_create (unsigned numBytes, unsigned char* buffer, cWebStringPtr_t mimeType);
	AWS_EXPORT   cResResponsePtr_t       aws_resresponse_create_path (cWebStringPtr_t filePath);

	// ===== RESOURCE REQUEST ======
	AWS_EXPORT   void                    aws_resrequest_cancel (cResRequestPtr_t request);
	AWS_EXPORT   unsigned                aws_resrequest_originProcId (cResRequestPtr_t request);
	AWS_EXPORT   cWebUrlPtr_t            aws_resrequest_getUrl (cResRequestPtr_t request);
	AWS_EXPORT   cWebStringPtr_t         aws_resrequest_getMethod (cResRequestPtr_t request);
	AWS_EXPORT   void                    aws_resrequest_setMethod (cResRequestPtr_t request, cWebStringPtr_t method);
	AWS_EXPORT   cWebStringPtr_t         aws_resrequest_getReferrer (cResRequestPtr_t request);
	AWS_EXPORT   void                    aws_resrequest_setReferrer (cResRequestPtr_t request, cWebStringPtr_t referrer);
	AWS_EXPORT   cWebStringPtr_t         aws_resrequest_getExtraHeaders (cResRequestPtr_t request);
	AWS_EXPORT   void                    aws_resrequest_setExtraHeaders (cResRequestPtr_t request, cWebStringPtr_t headers);
	AWS_EXPORT   void                    aws_resrequest_appendExtraHeader (cResRequestPtr_t request, cWebStringPtr_t name, cWebStringPtr_t value);
	AWS_EXPORT   unsigned                aws_resrequest_getNumUploadedElements (cResRequestPtr_t request);
	AWS_EXPORT   cUploadElementPtr_t     aws_resrequest_getUploadElement (cResRequestPtr_t request);
	AWS_EXPORT   void                    aws_resrequest_clearUploadElements (cResRequestPtr_t request);
	AWS_EXPORT   void                    aws_resrequest_appendUploadFilePath (cResRequestPtr_t request, cWebStringPtr_t filePath);
	AWS_EXPORT   void                    aws_resrequest_appendUploadBytes (cResRequestPtr_t request, unsigned char* bytes, unsigned numBytes);

	// ===== UPLOAD ELEMENT ======
	AWS_EXPORT   bool                    aws_uploadelem_isFilePath (cUploadElementPtr_t upelem);
	AWS_EXPORT   bool                    aws_uploadelem_isBytes (cUploadElementPtr_t upelem);
	AWS_EXPORT   unsigned                aws_uploadelem_getNumBytes (cUploadElementPtr_t upelem);
	AWS_EXPORT   unsigned char*          aws_uploadelem_getBytes (cUploadElementPtr_t upelem);
	AWS_EXPORT   cWebStringPtr_t         aws_uploadelem_getFilePath (cUploadElementPtr_t upelem);

	// ===== OTHER STUFF ======
	/// type = awesomium keyboard event type
	AWS_EXPORT   cKeyboardEvtPtr_t       aws_keyboardevent_from_keycode (int virtkey, int scancode, int modifiers, int type, wchar16 text);
	AWS_EXPORT   void                    aws_keyboardevent_set_data (cKeyboardEvtPtr_t evt, cKeyEventData data);
	AWS_EXPORT   cKeyEventData           aws_keyboardevent_get_data (cKeyboardEvtPtr_t evt);

#ifdef __APPLE__
	AWS_EXPORT   cKeyboardEvtPtr_t       aws_keyboardevent_from_system (NSEvent* evt);
#elif defined _WIN32
	AWS_EXPORT   cKeyboardEvtPtr_t       aws_keyboardevent_from_system (UINT msg, WPARAM wparam, LPARAM lparam);
#else // other placeholders(x11/wayland, if any ...)

#endif 

	AWS_EXPORT   void                    aws_keyboardevent_delete (cKeyboardEvtPtr_t evt);


#ifdef __cplusplus
}
#endif

#endif