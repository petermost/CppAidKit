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

#include <string>
#include <limits>
#include <functional>
#include <pera_software/aidkit/io/errno.hpp>

#define AIDKIT_STRINGIFY(name) #name
#define AIDKIT_STRINGIFY_MACRO(macro) AIDKIT_STRINGIFY(macro)

#define AIDKIT_JOIN(x,y) x##y
#define AIDKIT_JOIN_STRINGIFY(x,y) AIDKIT_STRINGIFY(x##y)

namespace pera_software::aidkit {

	// General trim_left, trim_right functions:

	AIDKIT_API const std::string trim_left( const std::string &s );
	AIDKIT_API const std::string trim_left( const std::string &s, char c );
	AIDKIT_API const std::string trim_left( const std::string &s, const std::function< bool ( char ) > &predicate );

	AIDKIT_API const std::string trim_right( const std::string &s );
	AIDKIT_API const std::string trim_right( const std::string &s, char c );
	AIDKIT_API const std::string trim_right( const std::string &s, const std::function< bool ( char ) > &predicate );

	template < typename Char, size_t SIZE >
		constexpr bool is_string_literal( const Char ( & )[ SIZE ] ) noexcept {
			return true;
		}

	template < typename Char >
		constexpr bool is_string_literal( const Char * const & ) noexcept {
			return false;
		}

	//=============================================================================================

	template < typename Int >
		struct StringToInteger;

	template <>
		struct StringToInteger< int > {
			static int convert( const char *str, char **str_end, int base ) {
				return static_cast< int >( std::strtol( str, str_end, base ));
			}
		};

	template <>
		struct StringToInteger< long > {
			static long convert( const char *str, char **str_end, int base ) {
				return std::strtol( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< long long > {
			static long long convert( const char *str, char **str_end, int base ) {
				return std::strtoll( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< unsigned long > {
			static unsigned long convert( const char *str, char **str_end, int base ) {
				return std::strtoul( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< unsigned long long > {
			static unsigned long long convert( const char *str, char **str_end, int base ) {
				return std::strtoull( str, str_end, base );
			}
		};

	template < typename Int >
		bool try_stoi( const std::string &str, Int *integer, std::error_code *errorCode ) {
			const char *begin = str.c_str();
			const char *end = begin + str.size();
			char *ptr;

			errno = 0;
			auto result = StringToInteger< Int >::convert( begin, &ptr, 10 );
			if ( errno == 0 && ptr == end && std::numeric_limits< Int >::min() <= result && result <= std::numeric_limits< Int >::max() ) {
				*integer = static_cast< Int >( result );
				return true;
			} else {
				*errorCode = io::make_errno_error_code();
				return false;
			}
		}
}

