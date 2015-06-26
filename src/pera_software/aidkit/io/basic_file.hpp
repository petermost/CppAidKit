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

//#include "file_impl.hpp"
#include "file_error.hpp"
#include <pera_software/aidkit/aidkit.hpp>
#include <pera_software/aidkit/unicode.hpp>
#include <memory>
#include <string>
#include <cstdio>

namespace pera_software { namespace aidkit { namespace io {

	struct file_category {
	};

	struct file_locked_category : file_category {
	};

	struct file_functions_base {

		static int do_not_eof( int result ) {
			return std::char_traits< char >::not_eof( result );
		}

		static wint_t do_not_eof( wint_t result ) {
			return std::char_traits< wchar_t >::not_eof( result );
		}
	};


	template < typename Category >
		struct file_functions : file_functions_base {
		};

	template <>
		struct file_functions< file_locked_category > : file_functions_base {

			static std::FILE *do_open( const char fileName[], const char openMode[] ) {
				return std::fopen( fileName, openMode );
			}

			static int do_close( std::FILE *fp ) {
				return std::fclose( fp );
			}

			static int do_seek( std::FILE *fp, long offset, int origin ) {
				return std::fseek( fp, offset, origin );
			}

			static long do_tell( std::FILE *fp ) {
				return std::ftell( fp );
			}

			static int do_putc( std::FILE *fp, char c ) {
				return std::putc( c, fp );
			}

			static wint_t do_putwc( std::FILE *fp, wchar_t c ) {
				return std::putwc( c, fp );
			}

			static int do_getc( std::FILE *fp ) {
				return std::getc( fp );
			}

			static wint_t do_getwc( std::FILE *fp ) {
				return std::getwc( fp );
			}

			static int do_puts( std::FILE *fp, const char s[] ) {
				return std::fputs( s, fp );
			}

			static int do_putws( std::FILE *fp, const wchar_t s[] ) {
				return std::fputws( s, fp );
			}

			static char *do_gets( std::FILE *fp, char *str, int count ) {
				return std::fgets( str, count, fp );
			}

			static wchar_t *do_getws( std::FILE *fp, wchar_t *str, int count ) {
				return std::fgetws( str, count, fp );
			}

			static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
				return std::fwrite( buffer, size, count, fp );
			}

			static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
				return std::fread( buffer, size, count, fp );
			}

			template < typename ... Args >
				static int do_printf( std::FILE *fp, const char format[], Args && ... args ) {
					return std::fprintf( fp, format, std::forward< Args >( args ) ... );
				}

			template < typename ... Args >
				static int do_wprintf( std::FILE *fp, const wchar_t format[], Args && ... args ) {
					return std::fwprintf( fp, format, std::forward< Args >( args ) ... );
				}

			static int do_eof( std::FILE *fp ) {
				return std::feof( fp );
			}

			static int do_error( std::FILE *fp ) {
				return std::ferror( fp );
			}
		};


	template < typename Category, typename Functions = file_functions< Category >>
		class basic_file {
			public:
				typedef long offset_t;

				enum class origin {
					begin = SEEK_SET,
					current = SEEK_CUR,
					end = SEEK_END
				};

				basic_file( const basic_file & ) = delete;
				basic_file &operator = ( const basic_file & ) = delete;

				basic_file() {
					file_ = nullptr;
				}

				bool open( const char fileName[], const char openMode[], std::error_code *errorCode ) {
					file_ = Functions::do_open( fileName, openMode );
					bool success = ( file_ != nullptr );
					if ( success )
						fileName_ = fileName;

					*errorCode = get_error_code( success );
					return success;
				}

				bool close( std::error_code *errorCode ) {
					auto result = Functions::do_close( file_ );
					bool success = Functions::do_not_eof( result );

					*errorCode = get_error_code( success );
					return success;
				}

				bool seek( offset_t offset, origin origin, std::error_code *errorCode ) {
					auto result = Functions::do_seek( file_, offset, static_cast< int >( origin ));
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return success;
				}

				bool tell( offset_t *offset, std::error_code *errorCode ) {
					*offset = Functions::do_tell( file_ );
					bool success = ( *offset != offset_t( -1 ));

					*errorCode = get_error_code( success );
					return success;
				}

				bool put( char c, std::error_code *errorCode ) {
					return call_putc( Functions::do_putc, c, errorCode );
				}

				bool put( wchar_t c, std::error_code *errorCode ) {
					return call_putc( Functions::do_putwc, c, errorCode );
				}

				bool get( char *c, std::error_code *errorCode ) {
					return call_getc( Functions::do_getc, c, errorCode );
				}

				bool get( wchar_t *c, std::error_code *errorCode ) {
					return call_getc( Functions::do_getwc, c, errorCode );
				}

				bool put( const char s[], std::error_code *errorCode ) {
					return call_puts( Functions::do_puts, s, errorCode );
				}

				bool put( const wchar_t s[], std::error_code *errorCode ) {
					return call_puts( Functions::do_putws, s, errorCode );
				}

				bool get( char *s, int count, std::error_code *errorCode ) {
					return call_gets( Functions::do_gets, s, count, errorCode );
				}

				bool get( wchar_t *s, int count, std::error_code *errorCode ) {
					return call_gets( Functions::do_getws, s, count, errorCode );
				}

				bool write( const void *buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) {
					return call_transfer( Functions::do_write, buffer, size, count, errorCode );
				}

				bool read( void *buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) {
					return call_transfer( Functions::do_read, buffer, size, count, errorCode );
				}

				template < typename ... Args >
					bool print( std::error_code *errorCode, const char format[], Args && ... args ) {
						return call_printf( Functions::template do_printf< Args ... >, errorCode, format, std::forward< Args >( args ) ... );
					}

				template < typename ... Args >
					bool print( std::error_code *errorCode, const wchar_t format[], Args && ... args ) {
						return call_printf( Functions::template do_wprintf< Args ... >, errorCode, format, std::forward< Args >( args ) ... );
					}

				bool is_eof() const {
					return Functions::do_eof( file_ ) != 0;
				}

				bool is_error() const {
					return Functions::do_error( file_ ) != 0;
				}

			private:
				template < typename Char, typename Function >
					bool call_putc( Function putcFunction, Char c, std::error_code *errorCode ) {
						auto result = putcFunction( file_, c );
						bool success = Functions::do_not_eof( result );

						*errorCode = get_error_code( success );
						return success;
					}

				template < typename Char, typename Function >
					bool call_getc( Function getcFunction, Char *c, std::error_code *errorCode ) {
						auto result = getcFunction( file_ );
						bool success = Functions::do_not_eof( result );
						if ( success )
							*c = result;

						*errorCode = get_error_code( success );
						return success;
					}

				template < typename Char, typename Function >
					bool call_puts( Function putsFunction, const Char s[], std::error_code *errorCode ) {
						auto result = putsFunction( file_, s );
						bool success = Functions::do_not_eof( result );

						*errorCode = get_error_code( success );
						return success;
					}

				template < typename Char, typename Function >
					bool call_gets( Function getsFunction, Char *s, int count, std::error_code *errorCode ) {
						Char *result = getsFunction( file_, s, count );
						bool success = ( result != nullptr );

						*errorCode = get_error_code( success );
						return success;
					}

				template < typename T, typename Function >
					bool call_transfer( Function transferFunction, T buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) {
						std::size_t result = transferFunction( file_, buffer, size, count );
						bool success = ( result == count );

						if ( success )
							errorCode->clear();
						else if ( size == 0 || count == 0 )
							errorCode->clear();
						else
							*errorCode = get_error_code( success );

						return success;
					}

				template < typename Char, typename Function, typename ... Args >
					bool call_printf( Function printfFunction, std::error_code *errorCode, const Char format[], Args && ... args ) {
						auto result = printfFunction( file_, format, std::forward< Args >( args ) ... );
						bool success = Functions::do_not_eof( result );

						*errorCode = get_error_code( success );
						return success;
					}

				std::error_code get_error_code( bool success ) {
					if ( success )
						return std::error_code();
					else {
						if ( is_error() )
							return make_errno_error_code();
						else if ( is_eof() )
							return make_error_code( file_error::eof );
					}
				}

				std::FILE *file_;
				std::string fileName_;

		};
} } }

