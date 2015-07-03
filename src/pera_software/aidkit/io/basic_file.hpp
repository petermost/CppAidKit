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



	template < typename Category >
		struct basic_file_functions;

	template < typename Char, typename Category >
		struct file_functions;


	template <>
		struct basic_file_functions< file_locked_category > {

			static int do_close( std::FILE *fp ) {
				return std::fclose( fp );
			}

			static int do_wide( std::FILE *fp, int mode ) {
				return std::fwide( fp, mode );
			}

			static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
				return std::fwrite( buffer, size, count, fp );
			}

			static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
				return std::fread( buffer, size, count, fp );
			}

			static int do_seek( std::FILE *fp, long offset, int origin ) {
				return std::fseek( fp, offset, origin );
			}

			static long do_tell( std::FILE *fp ) {
				return std::ftell( fp );
			}

			static int do_setpos( std::FILE *fp, const std::fpos_t *position ) {
				return std::fsetpos( fp, position );
			}

			static int do_getpos( std::FILE *fp, std::fpos_t *position ) {
				return std::fgetpos( fp, position );
			}

			static int do_flush( std::FILE *fp ) {
				return std::fflush( fp );
			}

			static void do_rewind( std::FILE *fp ) {
				std::rewind( fp );
			}

			static void do_clearerr( std::FILE *fp ) {
				std::clearerr( fp );
			}

			static int do_eof( std::FILE *fp ) {
				return std::feof( fp );
			}

			static int do_error( std::FILE *fp ) {
				return std::ferror( fp );
			}
		};

	template <>
		struct file_functions< char, file_locked_category > : basic_file_functions< file_locked_category > {

			static int do_not_eof( int result ) {
				return std::char_traits< char >::not_eof( result );
			}

			static std::FILE *do_open( const char fileName[], const char openMode[] ) {
				return std::fopen( fileName, openMode );
			}

			static int do_putc( std::FILE *fp, char c ) {
				return std::putc( c, fp );
			}

			static int do_getc( std::FILE *fp ) {
				return std::getc( fp );
			}

			static int do_puts( std::FILE *fp, const char s[] ) {
				return std::fputs( s, fp );
			}

			static char *do_gets( std::FILE *fp, char *str, int count ) {
				return std::fgets( str, count, fp );
			}

			template < typename ... Args >
				static int do_printf( std::FILE *fp, const char format[], Args && ... args ) {
					return std::fprintf( fp, format, std::forward< Args >( args ) ... );
				}

		};

	template <>
		struct file_functions< wchar_t, file_locked_category > : basic_file_functions< file_locked_category > {

			static wint_t do_not_eof( wint_t result ) {
				return std::char_traits< wchar_t >::not_eof( result );
			}

			// There is no wfopen function, so we only provide a char based version:
			static std::FILE *do_open( const char fileName[], const char openMode[] ) {
				return std::fopen( fileName, openMode );
			}

			static wint_t do_putc( std::FILE *fp, wchar_t c ) {
				return std::putwc( c, fp );
			}

			static wint_t do_getc( std::FILE *fp ) {
				return std::getwc( fp );
			}

			static int do_puts( std::FILE *fp, const wchar_t s[] ) {
				return std::fputws( s, fp );
			}

			static wchar_t *do_gets( std::FILE *fp, wchar_t *str, int count ) {
				return std::fgetws( str, count, fp );
			}

			template < typename ... Args >
				static int do_printf( std::FILE *fp, const wchar_t format[], Args && ... args ) {
					return std::fwprintf( fp, format, std::forward< Args >( args ) ... );
				}

		};


	template < typename Char, typename Category = file_locked_category, typename Functions = file_functions< Char, Category >>
		class basic_file {
			public:
				typedef long offset_t;

				enum class origin {
					begin   = SEEK_SET,
					current = SEEK_CUR,
					end     = SEEK_END
				};

				enum class orientation {
					byte = -1,
					none =  0,
					wide =  1
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

				Char put( Char c, std::error_code *errorCode ) {
					auto result = Functions::do_putc( file_, c );
					bool success = Functions::do_not_eof( result );

					*errorCode = get_error_code( success );
					return result;
				}

				Char get( std::error_code *errorCode ) {
					auto result = Functions::do_getc( file_ );
					bool success = Functions::do_not_eof( result );

					*errorCode = get_error_code( success );
					return result;
				}

				const Char *put( const Char s[], std::error_code *errorCode ) {
					auto result = Functions::do_puts( file_, s );
					bool success = Functions::do_not_eof( result );

					*errorCode = get_error_code( success );
					return success ? s : nullptr;
				}

				Char *get( Char *s, int count, std::error_code *errorCode ) {
					Char *result = Functions::do_gets( file_, s, count );
					bool success = ( result != nullptr );

					*errorCode = get_error_code( success );
					return result;
				}

				size_t write( const void *buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) {
					return call_transfer( Functions::do_write, buffer, size, count, errorCode );
				}

				size_t read( void *buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) {
					return call_transfer( Functions::do_read, buffer, size, count, errorCode );
				}

				template < typename ... Args >
					int print( std::error_code *errorCode, const Char format[], Args && ... args ) {
						auto result = Functions::do_printf( file_, format, std::forward< Args >( args ) ... );
						bool success = Functions::do_not_eof( result );

						*errorCode = get_error_code( success );
						return result;
					}

				bool seek( offset_t offset, origin origin, std::error_code *errorCode ) {
					auto result = Functions::do_seek( file_, offset, static_cast< int >( origin ));
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return success;
				}

				offset_t tell( std::error_code *errorCode ) {
					auto result = Functions::do_tell( file_ );
					bool success = ( result != offset_t( -1 ));

					*errorCode = get_error_code( success );
					return result;
				}

				bool set_position( const std::fpos_t &position, std::error_code *errorCode ) {
					auto result = Functions::do_setpos( file_, &position );
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return success;
				}

				std::fpos_t get_position( std::error_code *errorCode ) {
					fpos_t position;
					auto result = Functions::do_getpos( file_, &position );
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return position;
				}

				void set_orientation( orientation newOrientation ) {
					// The value 0 (orientation::none) is used to query the orientation, so it doesn't
					// makes sense to allow that value.

					if ( newOrientation == orientation::byte || newOrientation == orientation::wide )
						Functions::do_wide( file_, static_cast< int >( newOrientation ));
				}

				orientation get_orientation() {
					auto result = Functions::do_wide( file_, 0 );
					if( result < 0 )
						return orientation::byte;
					else if ( result > 0 )
						return orientation::wide;
					else // if ( result == 0 )
						return orientation::none;
				}

				bool flush( std::error_code *errorCode ) {
					auto result = Functions::do_flush( file_ );
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return success;
				}

				void rewind() {
					Functions::do_rewind( file_ );
				}

				void clear_error() {
					Functions::do_clearerr( file_ );
				}

				bool is_eof() const {
					return Functions::do_eof( file_ ) != 0;
				}

				bool is_error() const {
					return Functions::do_error( file_ ) != 0;
				}

			private:

				template < typename T, typename Function >
					size_t call_transfer( Function transferFunction, T buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) {
						std::size_t result = transferFunction( file_, buffer, size, count );
						bool success = ( result == count );

						if ( success )
							errorCode->clear();
						else if ( size == 0 || count == 0 )
							errorCode->clear();
						else
							*errorCode = get_error_code( success );

						return result;
					}


				std::error_code get_error_code( bool success ) {
					if ( success )
						return std::error_code();
					else {
						if ( is_error() )
							return make_errno_error_code();
						else if ( is_eof() )
							return make_error_code( file_error::eof );
						else
							return make_errno_error_code();
					}
				}

				std::FILE *file_;
				std::string fileName_;

		};
} } }

