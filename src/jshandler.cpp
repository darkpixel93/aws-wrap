#include "jshandler.h"
#include <algorithm>
#include <thread>

void JSHandler::OnMethodCall(Awesomium::WebView* caller,
                            unsigned int remote_object_id, 
                            const Awesomium::WebString& method_name,
                            const Awesomium::JSArray& args)
{
	// find handler, if exists call it
	auto cb = _callbacks.find(caller);
	if ( cb != _callbacks.end() )
	{
		if ( cb->second.call )
		{
			cb->second.call(reinterpret_cast<cWebViewPtr_t>(caller),
					remote_object_id, 
					reinterpret_cast<cWebStringPtr_t>(new Awesomium::WebString(method_name)),
					reinterpret_cast<cJSArrayPtr_t>(new Awesomium::JSArray(args)),
					cb->second.userptr
				);
		}
	}
}

	
Awesomium::JSValue JSHandler::OnMethodCallWithReturnValue(Awesomium::WebView* caller,
                                              unsigned int remote_object_id,
                                              const Awesomium::WebString& method_name,
                                              const Awesomium::JSArray& args)
{
	auto cb = _callbacks.find(caller);
	if ( cb != _callbacks.end() )
	{
		if ( cb->second.callval )
		{
			// return new js value from pointer to js value received from callback
			return Awesomium::JSValue( *reinterpret_cast<Awesomium::JSValue*> ( 
				cb->second.callval( 
							reinterpret_cast<cWebViewPtr_t>(caller),
							remote_object_id, 
							reinterpret_cast<cWebStringPtr_t>(new Awesomium::WebString(method_name)),
							reinterpret_cast<cJSArrayPtr_t>(new Awesomium::JSArray(args)),
							cb->second.userptr
				)
			));
		}
	}
	return Awesomium::JSValue::Undefined();
}


void JSHandler::addCallback(Awesomium::WebView* view, cJSMethodCallback_t clbk)
{
	_callbacks.emplace( view,clbk );
}

void JSHandler::removeCallback(Awesomium::WebView* view)
{
	auto cb = _callbacks.find(view);
	if ( cb != _callbacks.end() )
		_callbacks.erase(cb);
}

void JSHandler::removeCallbackAll()
{
	_callbacks.clear();
}
