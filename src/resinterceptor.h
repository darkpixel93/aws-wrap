#ifndef _RESOURCE_INTERCEPTOR_H_
#define _RESOURCE_INTERCEPTOR_H_

#include <Awesomium/ResourceInterceptor.h>


class ResInterceptor : public Awesomium::ResourceInterceptor
{
public:

	virtual Awesomium::ResourceResponse* OnRequest(Awesomium::ResourceRequest* request);
	virtual ~ResInterceptor() {}
};

#endif