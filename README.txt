Description:

  This wrapper provides unofficial C API to the Awesomium library,
  and also implements D interface to that library.

  There is a lot of untested code, errorous code and other sad things,
  which may gift you with a joy of happy debugging time.

  At this moment there is no implementation for such things like resource handlers,
  javascript handlers, and other similar stuff, but they are all in the plan,
  so it's just a matter of time.

  I'm planning release sources when, stuff listed above would be ready to avoid
  unneded redistributions by third parties.


Package folders:
  include -- this is C/C++ API header files
  import -- this is D API wrapper
  examples -- a sample(s) ported from official(or not) examples
  bin -- compiled release binaries
  lib -- import library files
  src -- sorry, not this time


Note:
  for windows there is two version of import lib file,
  if you don't know what is OMF and what is COFF just link against aws_wrap.lib.

  yes i know that OS X lib is half broken, can't adapt to xcode after visual studio.

p.s. Please keep in mind that this is early preview version, so
  no sources, documentation, examples or anything else provided at this moment.


If you have any questions or suggestions write me at evilrat666@gmail.com.