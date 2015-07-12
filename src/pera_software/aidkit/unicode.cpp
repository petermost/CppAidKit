// Copyright 2015 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#include "unicode.hpp"
#include <locale>

#if __GNUC__ >= 5
	#include <codecvt>
#endif

namespace pera_software { namespace aidkit {

using namespace std;

static_assert( sizeof( char8_t ) == sizeof( char ), "Wrong size for char8_t" );

// TODO: Fix for g++ 5.x

#if __GNUC__ >= 5

typedef wstring_convert< codecvt_utf8_utf16< wchar_t >, wchar_t > wstring_u8string_converter;
typedef wstring_convert< codecvt< wchar_t, char, mbstate_t >, wchar_t > wstring_string_converter;

wstring u8string_to_wstring( const u8string &s ) {
	wstring_u8string_converter converter;

	string bytes( s.begin(), s.end() );
	return converter.from_bytes( bytes );
}


u8string wstring_to_u8string( const wstring &s ) {
	wstring_u8string_converter converter;

	string bytes( converter.to_bytes( s ));
	return u8string( bytes.begin(), bytes.end() );
}

string wstring_to_string( const wstring &s ) {
	wstring_string_converter converter;

	return converter.to_bytes( s );
}

wstring string_to_wstring( const string &s ) {
	wstring_string_converter converter;

	return converter.from_bytes( s );
}

#else

string wstring_to_string( const wstring &s ) {
	return string( s.begin(), s.end() );
}

#endif

} }

namespace std {

#if __GNUC__ >= 5

wostream &operator << ( wostream &outputStream, const string &str ) {
	return outputStream << ::pera_software::aidkit::string_to_wstring( str );
}
#endif

}
