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
#include <codecvt>
#include <pera_software/aidkit/io/errno.hpp>

// TODO: Check which codecvt-templates are deprecated in C++17

namespace pera_software::aidkit {

using namespace io;
using namespace std;

static_assert( sizeof( char8_t ) == sizeof( char ), "Wrong size for char8_t" );

//==================================================================================================

// https://sourceforge.net/p/mingw-w64/bugs/538/
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=69703
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66855

using wstring_u8string_converter = wstring_convert< codecvt_utf8< wchar_t >, wchar_t >;

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

//==================================================================================================

template < typename TargetChar, typename SourceChar >
	basic_string< TargetChar > convert( const basic_string< SourceChar > &sourceString,
			size_t ( *convertFunction )( TargetChar *dst, const SourceChar **src, size_t len, mbstate_t *state )) {

		constexpr auto LENGTH_ERROR = static_cast< size_t >( -1 );

		mbstate_t state = mbstate_t();

		// Find out how much space we need:

		const SourceChar *sourceStringData = sourceString.data();
		size_t expectedTargetStringLength = convertFunction( nullptr, &sourceStringData, sourceString.length(), &state );
		if ( expectedTargetStringLength == LENGTH_ERROR )
			throw make_errno_system_error();

		// Convert the string:

		basic_string< TargetChar > targetString( expectedTargetStringLength, TargetChar() );
		size_t actualTargetStringLength = convertFunction( &targetString[ 0 ], &sourceStringData, sourceString.length(), &state );
		if ( actualTargetStringLength == LENGTH_ERROR )
			throw make_errno_system_error();

		// Could all characters be converted?

		if ( expectedTargetStringLength != actualTargetStringLength )
			throw system_error( make_error_code( errc::illegal_byte_sequence ));

		return targetString;
	}

string wstring_to_string( const wstring &wideString ) {
	return convert< char, wchar_t >( wideString, wcsrtombs );
}

wstring string_to_wstring( const string &narrowString ) {
	return convert< wchar_t, char >( narrowString, mbsrtowcs );
}

}

namespace std {

	wostream &operator << ( wostream &outputStream, const string &str ) {
		return outputStream << ::pera_software::aidkit::string_to_wstring( str );
	}

}

