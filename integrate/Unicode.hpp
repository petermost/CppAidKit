#pragma once

#include <UtilityCpp/UtilityCpp.h>
#include <string>

namespace std 
{
	UTILITYCPP_API wostream &operator << ( wostream &outputStream, const string &str );
}

{
	namespace Strings 
	{
		typedef unsigned char char8_t;
		typedef std::basic_string< char8_t, std::char_traits< char8_t >, std::allocator< char8_t >> u8string;

		UTILITYCPP_API std::wstring u8string_to_wstring( const u8string & );
		UTILITYCPP_API u8string wstring_to_u8string( const std::wstring & );

		UTILITYCPP_API std::string wstring_to_string( const std::wstring & );
		UTILITYCPP_API std::wstring string_to_wstring( const std::string & );
	}
}



