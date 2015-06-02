#include "stdafx.h"
#include "Unicode.hpp"
#include <UtilityCpp/Exceptions/ErrNoException.hpp>
#include <locale>
#include <codecvt>

namespace std {

wostream &operator << ( wostream &outputStream, const string &str ) 
{
	return outputStream << ::Strings::string_to_wstring( str );
}

}



using namespace std;
using namespace Exceptions;

BOOST_STATIC_ASSERT( sizeof( char8_t ) == sizeof( char ));

typedef wstring_convert< codecvt_utf8_utf16< wchar_t >, wchar_t > wstring_u8string_converter;
typedef wstring_convert< codecvt< wchar_t, char, mbstate_t >, wchar_t > wstring_string_converter;


wstring u8string_to_wstring( const u8string &s )
{
	wstring_u8string_converter converter;

	string bytes( s.begin(), s.end() );
	return converter.from_bytes( bytes );
}


u8string wstring_to_u8string( const wstring &s )
{
	wstring_u8string_converter converter;

	string bytes( converter.to_bytes( s ));
	return u8string( bytes.begin(), bytes.end() );
}

string wstring_to_string( const wstring &s )
{
	wstring_string_converter converter;

	return converter.to_bytes( s );
}

wstring string_to_wstring( const string &s )
{
	wstring_string_converter converter;

	return converter.from_bytes( s );
}


//string wstring_to_string( const wstring &wideString )
//{
//	mbstate_t state = mbstate_t();
//
//	// Find out how much space we need:
//
//	const wchar_t *wideStringData = wideString.data();
//	size_t length = wcsrtombs( nullptr, &wideStringData, wideString.length(), &state );
//
//	// Allocate the needed space:
//
//	string narrowString( length, char() );
//
//	// Convert the string:
//
//	if (( length = wcsrtombs( &narrowString[ 0 ], &wideStringData, wideString.length(), &state )) == -1 )
//		return narrowString;
//	else
//		BOOST_THROW_EXCEPTION( ErrNoException::LastError() );
//}



//wstring string_to_wstring( const string &narrowString )
//{
//	mbstate_t state = mbstate_t();
//
//	// Find out how much space we need:
//
//	const char *narrowStringData = narrowString.data();
//	auto length = mbsrtowcs( nullptr, &narrowStringData, narrowString.length(), &state );
//	
//	// Allocate the needed space:
//
//	wstring wideString( length, wchar_t() );
//
//	// Convert the string:
//
//	if (( length = mbsrtowcs( &wideString[ 0 ], &narrowStringData, narrowString.length(), &state )) != -1 )
//		return wideString;
//	else
//		BOOST_THROW_EXCEPTION( ErrNoException::LastError() );
//}


} }
