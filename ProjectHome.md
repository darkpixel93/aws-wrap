This library provides unofficial C API and D wrapper for Awesomium library version 1.7

Awesomium is closed source off-screen and native window browser engine based on the same engine as chrome browser. it can be used for free in non-commercial projects, has indie license, and commercial license. current version(1.7 RC3) has only OS X and Windows builds, but there is also 1.6.5 version available which contains Linux build and official C API.


**Build notes:**
  * simplest way to build wrapper is to put your cloned repo in the awesomium sdk folder
  * we don't provide COFF to OMF conversion tool needed to make Optlink(DMD) library format on Windows, you could get it from there [ftp://ftp.digitalmars.com/coffimplib.zip](ftp://ftp.digitalmars.com/coffimplib.zip)


**Using C API:**
  * just include "include/wrap\_core.h".


**Using with D language:**
  * build awesomium wrapper D API as static lib(DMD -lib flag), link it with your project and add "import" path to import search paths(-I flag on DMD)
  * or simply put whole D API code to your project

once you've done this you could "import awesomium.dapi" to get all related stuff imported. don't forget to link with aws\_wrap.lib on windows(aws\_wrap\_omf.lib for DMD)