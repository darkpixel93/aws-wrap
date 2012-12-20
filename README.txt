Description:

  This wrapper provides D bindings for Awesomium library(http://awesomium.com)
  and also implements unofficial C API for Awesomium version 1.7.

  There is a lot of untested code, errorous code and other sad things,
  which may gift you with a joy of happy debugging time.

  At this moment there is no implementation for such things like resource handlers,
  javascript handlers, and other similar stuff, but they are all in the plan,
  so it's just a matter of time.



Building:
  Simplest way to go is just to put your repository clone into awesomium sdk folder.

Using with C language:
  All you need to use C API is to include 'include/wrap_core.h"

Using with D language:
  there is 2 ways of using D bindings:
  - build D bindings as static library, then in your project 
    just link with that library and add import path
  - or just drop whole awesomium package to your project



If you have any questions or suggestions write me at evilrat666@gmail.com.