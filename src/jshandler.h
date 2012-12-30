#ifndef _JSHANDLER_H_
#define _JSHANDLER_H_

#include "wrap_core.h"

#include <Awesomium/JSObject.h>
#include <Awesomium/JSValue.h>

#include <map>
#include <list>
#include <functional>

typedef std::map<Awesomium::WebView*, cJSMethodCallback_t> JSCallHandlers_t;

class JSHandler : public Awesomium::JSMethodHandler
{
public:
	virtual void OnMethodCall(Awesomium::WebView* caller,
		unsigned int remote_object_id, 
		const Awesomium::WebString& method_name,
		const Awesomium::JSArray& args);


	virtual Awesomium::JSValue OnMethodCallWithReturnValue(Awesomium::WebView* caller,
		unsigned int remote_object_id,
		const Awesomium::WebString& method_name,
		const Awesomium::JSArray& args);

	virtual void addCallback(Awesomium::WebView* view, cJSMethodCallback_t clbk);

	virtual void removeCallback(Awesomium::WebView* view);

	virtual void removeCallbackAll();

	virtual ~JSHandler() { _callbacks.clear(); }

protected:
	JSCallHandlers_t _callbacks;
};

extern JSHandler _aws_jshandler;

#endif