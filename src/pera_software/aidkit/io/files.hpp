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
			template < typename C, typename F, typename I >
				void fput_char_impl( std::FILE *file, C c, F put_function, const I eof ) {
					file_exception error;
					if ( !fput_char_impl( file, c, &error, put_function, eof ))
						throw error;
				}

			template < typename C, typename F, typename I >
				bool fput_char_impl( std::FILE *file, C c, file_exception *error, F put_function, const I eof ) {
					decltype( put_function( c, file )) result = put_function( c, file );
					if ( result == eof ) {
						*error = file_exception::last_error();
						return false;
					} else
						return true;
				}

			template < typename C, typename F, typename I >
				void fget_char_impl( std::FILE *file, C *c, F get_function, const I eof ) {
					file_exception error;
					if ( !fget_char_impl( file, c, &error, get_function, eof ))
						throw error;
				}

			template < typename C, typename F, typename I >
				bool fget_char_impl( std::FILE *file, C *c, file_exception *error, F get_function, const I eof ) {
					decltype( get_function( file )) result = get_function( file );
					if ( result == eof ) {
						*error = file_exception::last_error();
						return false;
					} else {
						*c = result;
						return true;
					}
				}

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

		}
	}
}
