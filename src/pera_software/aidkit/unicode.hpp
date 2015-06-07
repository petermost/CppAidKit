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

#pragma once

#include <pera_software/aidkit/aidkit.hpp>
#include <string>


namespace pera_software { namespace aidkit {

	typedef unsigned char char8_t;
	typedef std::basic_string< char8_t, std::char_traits< char8_t >, std::allocator< char8_t >> u8string;

#if __GNUC__ >= 5
	AIDKIT_API std::wstring u8string_to_wstring( const u8string & );
	AIDKIT_API u8string wstring_to_u8string( const std::wstring & );

	AIDKIT_API std::wstring string_to_wstring( const std::string & );
#endif
	AIDKIT_API std::string wstring_to_string( const std::wstring & );

} }

namespace std {
#if __GNUC__ >= 5
	AIDKIT_API wostream &operator << ( wostream &outputStream, const string &str );
#endif
}
