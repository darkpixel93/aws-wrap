/**
 * This is a simple "Hello World!" example of using Awesomium.
 *
 * It loads a page and saves a rendered bitmap of it to a JPEG.
 *
 * Procedure:
 * -- Create the WebCore singleton
 * -- Create a new WebView and request for it to load a URL.
 * -- Wait for the WebView to finish loading.
 * -- Retrieve the BitmapSurface from the WebView.
 * -- Save the BitmapSurface to 'result.jpg'.
 * -- Clean up.
 */

// import everything we may need
import awesomium.dapi;
import std.stdio : writeln;

// Various definitions
enum WIDTH = 800;
enum HEIGHT = 600;
enum URL = "http://www.google.com";

// Our main program
void main() 
{
	// initialize our WebCore with default settings
	WebCore.Initialize( WebConfig() );

	// just a shortcut
	auto wc = WebCore.instance;
	
	// get awesomium version, at this moment it's "1.7.0 RC3"
	writeln( "awesomium version: ", wc.version_string);

	// create new WebView with requested size
	auto view = wc.CreateWebView(WIDTH,HEIGHT);

	// load page into WebView
	view.loadURL( URL );

	writeln("Page is now loading...");

	// Wait for our WebView to finish loading
	while ( view.IsLoading() )
		Update(50);
	
	writeln("Page has finished loading.");

	writeln("Page title is: ", view.title );
	
	// Update once more a little longer to allow scripts and plugins
	// to finish loading on the page.
	Update(300);

	// Get the WebView's rendering Surface. The default Surface is of
	// type 'BitmapSurface', we must cast it before we can use it.
	auto surface = cast(BitmapSurface)view.surface;

	// Make sure our surface is not NULL-- it may be NULL if the WebView 
	// process has crashed.
	if (surface !is null) {
		// Save our BitmapSurface to a JPEG image
		surface.SaveToJPEG("./result.jpg");

		writeln("Saved a render of the page to 'result.jpg'.");
	}

	// Destroy our WebView instance
	view.Destroy();

	// Update once more before we shutdown for good measure
	Update(100);

	// Destroy our WebCore instance
	WebCore.Shutdown();
}

// put current thread to sleep for @sleep_ms msecs
void Update(int sleep_ms) 
{
	import core.thread;
	
	Thread.sleep( dur!("msecs")( sleep_ms ) );
	
	// You must call WebCore.update periodically
	// during the lifetime of your application.
	WebCore.instance.Update();
}