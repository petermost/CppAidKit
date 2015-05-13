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

#include "file_error.hpp"
#include <cstdio>

namespace pera_software {
	namespace aidkit {
		namespace io {

			// Put implementations for char/wchar_t:

			template < typename C, typename F, typename I >
				bool fput_char_impl( std::FILE *file, C c, std::error_code *errorCode, F put_function, const I eof ) {
					auto result = put_function( c, file );
					if ( result == eof ) {
						if ( std::ferror( file ))
							*errorCode = make_errno_error_code();
						else
							*errorCode = file_error::eof;
						return false;
					} else
						return true;
				}

			template < typename C, typename F, typename I >
				void fput_char_impl( std::FILE *file, C c, F put_function, const I eof ) {
					std::error_code errorCode;
					if ( !fput_char_impl( file, c, &errorCode, put_function, eof ))
						throw std::system_error( errorCode );
				}

			// Get implementations for char/wchar_t:

			template < typename C, typename F, typename I >
				bool fget_char_impl( std::FILE *file, C *c, std::error_code *errorCode, F get_function, const I eof ) {
					auto result = get_function( file );
					if ( result == eof ) {
						if ( std::ferror( file ))
							*errorCode = make_errno_error_code();
						else
							*errorCode = file_error::eof;
						return false;
					} else {
						*c = result;
						return true;
					}
				}

			template < typename C, typename F, typename I >
				void fget_char_impl( std::FILE *file, C *c, F get_function, const I eof ) {
					std::error_code errorCode;
					if ( !fget_char_impl( file, c, &errorCode, get_function, eof ))
						throw std::system_error( errorCode );
				}

			// Put implementations for char/wchar_t arrays:

			template < typename C, typename F, typename I >
				bool fput_string_impl( std::FILE *file, const C str[], std::error_code *errorCode, F put_function, const I eof ) {
					if ( put_function( str, file ) == eof ) {
						*errorCode = make_errno_error_code();
						return false;
					} else
						return true;
				}

			template < typename C, typename F, typename I >
				void fput_string_impl( std::FILE *file, const C str[], F put_function, const I eof ) {
					std::error_code errorCode;
					if ( !fput_string_impl( file, str, &errorCode, put_function, eof ))
						throw std::system_error( errorCode );
				}

			// Print implementations for char/wchar_t format strings:

			template < typename C, typename F, typename ... Args >
				bool fprint_format_impl( std::FILE *file, std::error_code *errorCode, const C format[], F print_function, Args && ... args ) {
					if ( print_function( file, format, std::forward< Args >( args ) ... ) < 0 ) {
						*errorCode = make_errno_error_code();
						return false;
					} else
						return true;
				}


			template < typename C, typename F, typename ... Args >
				void fprint_format_impl( std::FILE *file, const C format[], F print_function, Args && ... args ) {
					std::error_code errorCode;
					if ( !fprint_format_impl( file, &errorCode, format, print_function, std::forward< Args >( args ) ... ))
						throw std::system_error( errorCode );
				}

		}
	}
}
