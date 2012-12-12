#include "jshandler.h"
#include <algorithm>
#include <thread>

void JSHandler::OnMethodCall(Awesomium::WebView* caller,
                            unsigned int remote_object_id, 
                            const Awesomium::WebString& method_name,
                            const Awesomium::JSArray& args)
{
	// not bad o_O
	for (auto& cb : _callbacks) {
		if ( cb.target == caller )
			cb(caller, remote_object_id, method_name, args );
	}

	/*
	// let it be here for a moment in case if platform has no compiler able to compile code above
	std::for_each( _callbacks.begin(), _callbacks.end(), [&](JSCallback& clbk) {
		if ( clbk.target == caller ) {
			 clbk(caller, remote_object_id, method_name, args );
		}
	});
	*/
}

	
Awesomium::JSValue JSHandler::OnMethodCallWithReturnValue(Awesomium::WebView* caller,
                                              unsigned int remote_object_id,
                                              const Awesomium::WebString& method_name,
                                              const Awesomium::JSArray& args)
{
	auto k = _valcallbacks.find(caller);
	
	if ( k != _valcallbacks.end() )
	{
		return k->second(caller, remote_object_id, method_name, args);
	}
	
	return Awesomium::JSValue::Undefined();
}


void JSHandler::addCallback(Awesomium::WebView* view, jshnd_onMethodCall clbk)
{
	_callbacks.push_back( JSCallback(view, clbk) );
}

void JSHandler::addCallback(Awesomium::WebView* view, jshnd_onMethodCallValue clbk)
{
	_valcallbacks.emplace( view, JSCallbackValue(view, clbk) );
}

void JSHandler::removeCallback(Awesomium::WebView* view, jshnd_onMethodCall clbk)
{
	for (auto& cb : _callbacks) {
		if ( cb.target == view ) {
			//auto ptr = cb.func.target<jshnd_onMethodCall>();
			auto ptr = cb.func;
			if ( ptr == clbk )
				_callbacks.remove(cb);
		}
	}
}

void JSHandler::removeCallbackValue(Awesomium::WebView* view)
{
	_valcallbacks.erase(view);
}

void JSHandler::removeCallbackAll(Awesomium::WebView* view)
{
	auto t1 = std::thread([&](){
		for (auto& cb : _callbacks) {
			if ( cb.target == view )
				_callbacks.remove(cb);
		}
	});

	auto t2 = std::thread([&](){
		_valcallbacks.erase(view);
	});

	t1.join();
	t2.join();
}


// ======================================================

void JSCallback::operator()(Awesomium::WebView* caller,
                            unsigned int remote_id, 
                            const Awesomium::WebString& method_name,
							const Awesomium::JSArray& args) 
{
	func(
		reinterpret_cast<cWebViewPtr_t>(caller),
		remote_id, 
		reinterpret_cast<cWebStringPtr_t>(new Awesomium::WebString(method_name)),
		reinterpret_cast<cJSArrayPtr_t>(new Awesomium::JSArray(args)) 
		);
}

bool JSCallback::operator==(const JSCallback& other)
{
	return ( target == other.target && 
		//func.target<jshnd_onMethodCall>() == other.func.target<jshnd_onMethodCall>()
		func == other.func
		);
}

Awesomium::JSValue JSCallbackValue::operator()(Awesomium::WebView* caller,
                            unsigned int remote_id, 
                            const Awesomium::WebString& method_name,
							const Awesomium::JSArray& args)
{
	// return new js value from pointer to js value received from callback
	return Awesomium::JSValue(
			*reinterpret_cast<Awesomium::JSValue*>(
				func(
					reinterpret_cast<cWebViewPtr_t>(caller),
					remote_id, 
					reinterpret_cast<cWebStringPtr_t>(new Awesomium::WebString(method_name)),
					reinterpret_cast<cJSArrayPtr_t>(new Awesomium::JSArray(args)) 
				)
			)
	);
}