module awesomium.webstring;

import awesomium.capi, awesomium.util;


string fromWebString(cWebStringPtr_t wstr)
{
	char[] buf;
	auto len = aws_webstring_to_utf8(wstr, buf.ptr);

	return buf[0..len].idup;
}

final class WebString
{
public:
	/// new empty string
	this()
	{
		_internal = aws_webstring_new();
	}

	/// new string from utf8 data
	this(string str)
	{
		_internal = aws_webstring_new_utf8(str.ptr, str.length);
	}

	/// new string from substring
	this(WebString other, uint start, uint len)
	{
		_internal = aws_webstring_new_substring(other, start, len);
	}

	
	~this()
	{
		aws_webstring_delete(this);
		_internal = null;
	}

package:
	this(cWebStringPtr_t other)
	{
		_internal = other;
	}

package:
	alias _internal this;
	cWebStringPtr_t _internal;
}