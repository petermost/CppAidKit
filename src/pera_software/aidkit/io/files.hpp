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

#include "file_exception.hpp"
#include <cstdio>

namespace pera_software {
	namespace aidkit {
		namespace io {

			// Put implementations for char/wchar_t:

			template < typename C, typename F, typename I >
				void fput_char_impl( std::FILE *file, C c, F put_function, const I eof ) {
					file_exception error;
					if ( !fput_char_impl( file, c, &error, put_function, eof ))
						throw error;
				}

			template < typename C, typename F, typename I >
				bool fput_char_impl( std::FILE *file, C c, file_exception *error, F put_function, const I eof ) {
					auto result = put_function( c, file );
					if ( result == eof ) {
						*error = file_exception::last_error();
						return false;
					} else
						return true;
				}

			// Get implementations for char/wchar_t:

			template < typename C, typename F, typename I >
				void fget_char_impl( std::FILE *file, C *c, F get_function, const I eof ) {
					file_exception error;
					if ( !fget_char_impl( file, c, &error, get_function, eof ))
						throw error;
				}

			template < typename C, typename F, typename I >
				bool fget_char_impl( std::FILE *file, C *c, file_exception *error, F get_function, const I eof ) {
					auto result = get_function( file );
					if ( result == eof ) {
						*error = file_exception::last_error();
						return false;
					} else {
						*c = result;
						return true;
					}
				}

			// Put implementations for char/wchar_t arrays:

			template < typename C, typename F, typename I >
				void fput_string_impl( std::FILE *file, const C str[], F put_function, const I eof ) {
					file_exception error;
					if ( !fput_string_impl( file, str, &error, put_function, eof ))
						throw error;
				}

			template < typename C, typename F, typename I >
				bool fput_string_impl( std::FILE *file, const C str[], file_exception *error, F put_function, const I eof ) {
					if ( put_function( str, file ) == eof ) {
						*error = file_exception::last_error();
						return false;
					} else
						return true;
				}

			// Print implementations for char/wchar_t format strings:

			template < typename C, typename F, typename ... Args >
				void fprint_format_impl( std::FILE *file, const C format[], F print_function, Args && ... args ) {
					file_exception error;
					if ( !fprint_format_impl( file, &error, format, print_function, std::forward< Args >( args ) ... ))
						throw error;
				}

			template < typename C, typename F, typename ... Args >
				bool fprint_format_impl( std::FILE *file, file_exception *error, const C format[], F print_function, Args && ... args ) {
					if ( print_function( file, format, std::forward< Args >( args ) ... ) < 0 ) {
						*error = file_exception::last_error();
						return false;
					} else
						return true;
				}

			// Put functions for char/wchar_t:

			inline void fput_char( std::FILE *file, char c ) {
				fput_char_impl( file, c, std::putc, EOF );
			}

			inline bool fput_char( std::FILE *file, char c, file_exception *error ) {
				return fput_char_impl( file, c, error, std::putc, EOF );
			}

			inline void fput_char( std::FILE *file, wchar_t c ) {
				fput_char_impl( file, c, std::putwc, WEOF );
			}

			inline bool fput_char( std::FILE *file, wchar_t c, file_exception *error ) {
				return fput_char_impl( file, c, error, std::putwc, WEOF );
			}

			// Get functions for char/wchar_t:

			inline void fget_char( std::FILE *file, char *c ) {
				fget_char_impl( file, c, std::getc, EOF );
			}

			inline bool fget_char( std::FILE *file, char *c, file_exception *error ) {
				return fget_char_impl( file, c, error, std::getc, EOF );
			}

			inline void fget_char( std::FILE *file, wchar_t *c ) {
				fget_char_impl( file, c, std::getwc, WEOF );
			}

			inline bool fget_char( std::FILE *file, wchar_t *c, file_exception *error ) {
				return fget_char_impl( file, c, error, std::getwc, WEOF );
			}

			// Put functions for char/wchar_t arrays:

			inline void fput_string( std::FILE *file, const char str[] ) {
				fput_string_impl( file, str, std::fputs, EOF );
			}

			inline bool fput_string( std::FILE *file, const char str[], file_exception *error ) {
				return fput_string_impl( file, str, error, std::fputs, EOF );
			}

			inline void fput_string( std::FILE *file, const wchar_t str[] ) {
				fput_string_impl( file, str, std::fputws, WEOF );
			}

			inline bool fput_string( std::FILE *file, const wchar_t str[], file_exception *error ) {
				return fput_string_impl( file, str, error, std::fputws, WEOF );
			}

			// Print functions for char/wchar_t arrays:

			template < typename ... Args >
				void fprint_format( std::FILE *file, const char format[], Args ... args ) {
					fprint_format_impl( file, format, std::fprintf, std::forward< Args >( args ) ... );
				}

			template < typename ... Args >
				bool fprint_format( std::FILE *file, file_exception *error, const char format[], Args ... args ) {
					return fprint_format_impl( file, error, format, std::fprintf, std::forward< Args >( args ) ... );
				}

			template < typename ... Args >
				void fprint_format( std::FILE *file, const wchar_t format[], Args ... args ) {
					fprint_format_impl( file, format, std::fwprintf, std::forward< Args >( args ) ... );
				}

			template < typename ... Args >
				bool fprint_format( std::FILE *file, file_exception *error, const wchar_t format[], Args ... args ) {
					return fprint_format_impl( file, error, format, std::fwprintf, std::forward< Args >( args ) ... );
				}

		}
	}
}
