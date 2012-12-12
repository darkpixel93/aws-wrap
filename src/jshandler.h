#ifndef _JSHANDLER_H_
#define _JSHANDLER_H_

#include "wrap_core.h"

#include <Awesomium/JSObject.h>
#include <Awesomium/JSValue.h>

#include <map>
#include <list>
#include <functional>

struct JSCallback
{
	JSCallback( Awesomium::WebView* view, jshnd_onMethodCall clbk ) : target(view), func(clbk) /*func(std::function<jshnd_onMethodCall>(&clbk))*/ {}

	void operator()(Awesomium::WebView* caller,
                            unsigned int remote_id, 
                            const Awesomium::WebString& method_name,
							const Awesomium::JSArray& args);

	Awesomium::WebView* target;

	/* what the ...
	// visual studio bug again?
	std::function<jshnd_onMethodCall> func;
	*/
	jshnd_onMethodCall func;

	bool operator==(const JSCallback& other);
};


struct JSCallbackValue
{
	JSCallbackValue( Awesomium::WebView* view, jshnd_onMethodCallValue clbk ) : target(view), func(clbk) /*func(std::function<jshnd_onMethodCallValue>(&clbk))*/ {}

	Awesomium::JSValue operator()(Awesomium::WebView* caller,
                            unsigned int remote_id, 
                            const Awesomium::WebString& method_name,
							const Awesomium::JSArray& args);

	Awesomium::WebView* target;
	
	//std::function<jshnd_onMethodCallValue> func;
	jshnd_onMethodCallValue func;
};

typedef std::list<JSCallback> JSCallHandlers_t;
typedef std::map<Awesomium::WebView*, JSCallbackValue> JSCallValueHandlers_t;

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

	virtual void addCallback(Awesomium::WebView* view, jshnd_onMethodCall clbk);

	virtual void addCallback(Awesomium::WebView* view, jshnd_onMethodCallValue clbk);

	virtual void removeCallback(Awesomium::WebView* view, jshnd_onMethodCall clbk);

	virtual void removeCallbackValue(Awesomium::WebView* view);

	virtual void removeCallbackAll(Awesomium::WebView* view);

	virtual ~JSHandler() { _callbacks.clear(); _valcallbacks.clear(); }

protected:
	JSCallHandlers_t _callbacks;
	JSCallValueHandlers_t _valcallbacks;
};

extern JSHandler _aws_jshandler;

#endif