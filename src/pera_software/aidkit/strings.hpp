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
#include <locale>
#include <limits>
#include <cstddef>
#include <functional>
#include <algorithm>
#include <pera_software/aidkit/io/errno.hpp>

#define STRINGIZE( name ) #name
#define STRINGIZE_SYMBOL( symbol ) STRINGIZE( symbol )

#define WSTRINGIZE( name ) L#name
#define WSTRINGIZE_SYMBOL( symbol ) WSTRINGIZE( symbol )


namespace pera_software::aidkit {

	// General trim_left, trim_right functions:

	template < typename Char, typename Predicate >
		const std::basic_string< Char > trim_left( const std::basic_string< Char > &s, Predicate predicate ) {
			return std::basic_string< Char >( std::find_if( s.begin(), s.end(), predicate ), s.end() );
		}

	template < typename Char, typename Predicate >
		const std::basic_string< Char > trim_right( const std::basic_string< Char > &s, Predicate predicate ) {
			return std::basic_string< Char >( s.begin(), std::find_if( s.rbegin(), s.rend(), predicate ).base() );
		}

	// More specialized trim_left, trim_right functions:

	template < typename Char >
		bool is_space( Char c ) {
			return std::isspace( c, std::locale() );
		}

	template < typename Char >
		bool is_not_space( Char c ) {
			return !is_space( c );
		}

	template < typename Char >
		bool is_not_char( Char c, Char oc ) {
			return c != oc;
		}

	template < typename Char >
		const std::basic_string< Char > trim_left( const std::basic_string< Char > &s ) {
			return trim_left( s, is_not_space< Char > );
		}

	template < typename Char >
		const std::basic_string< Char > trim_right( const std::basic_string< Char > &s ) {
			return trim_right( s, is_not_space< Char > );
		}

	template< typename Char >
		const std::basic_string< Char > trim_left( const std::basic_string< Char > &s, Char c ) {
			return trim_left( s, std::bind( std::not_equal_to< Char >(), c, std::placeholders::_1 ));
		}

	template< typename Char >
		const std::basic_string< Char > trim_right( const std::basic_string< Char > &s, Char c ) {
			return trim_right( s, std::bind( std::not_equal_to< Char >(), c, std::placeholders::_1 ));
		}


	template < typename Char, size_t SIZE >
		constexpr bool is_string_literal( const Char ( & )[ SIZE ] ) noexcept {
			return true;
		}

	template < typename Char >
		constexpr bool is_string_literal( const Char * const & ) noexcept {
			return false;
		}

	//=============================================================================================

	template < typename Int, typename Char >
		struct StringToInteger;

	template <>
		struct StringToInteger< long, char > {
			static long convert( const char *str, char **str_end, int base ) {
				return std::strtol( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< long long, char > {
			static long long convert( const char *str, char **str_end, int base ) {
				return std::strtoll( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< unsigned long, char > {
			static unsigned long convert( const char *str, char **str_end, int base ) {
				return std::strtoul( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< unsigned long long, char > {
			static unsigned long long convert( const char *str, char **str_end, int base ) {
				return std::strtoull( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< long, wchar_t > {
			static long convert( const wchar_t *str, wchar_t **str_end, int base ) {
				return std::wcstol( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< long long, wchar_t > {
			static long long convert( const wchar_t *str, wchar_t **str_end, int base ) {
				return std::wcstoll( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< unsigned long, wchar_t > {
			static unsigned long convert( const wchar_t *str, wchar_t **str_end, int base ) {
				return std::wcstoul( str, str_end, base );
			}
		};

	template <>
		struct StringToInteger< unsigned long long, wchar_t > {
			static unsigned long long convert( const wchar_t *str, wchar_t **str_end, int base ) {
				return std::wcstoull( str, str_end, base );
			}
		};

	template < typename Int, typename Char >
		bool try_stoi( const std::basic_string< Char > &str, Int *integer, std::error_code *errorCode ) {
			const Char *begin = str.c_str();
			const Char *end = begin + str.size();
			Char *ptr;

			errno = 0;
			auto result = StringToInteger< Int, Char >::convert( begin, &ptr, 10 );
			if ( errno == 0 && ptr == end && std::numeric_limits< Int >::min() <= result && result <= std::numeric_limits< Int >::max() ) {
				*integer = static_cast< Int >( result );
				return true;
			} else {
				*errorCode = io::make_errno_error_code();
				return false;
			}
		}



}

