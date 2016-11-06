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

#include "errno.hpp"
#include "file_error.hpp"
#include "system_error.hpp"
#include <pera_software/aidkit/aidkit.hpp>
#include <pera_software/aidkit/enum_flags.hpp>
#include <cstdio>

namespace pera_software { namespace aidkit { namespace io {

	struct file_category {
	};

	struct file_locked_category : file_category {
	};



	template < typename Category >
		class basic_file_functions;

	template < typename Char, typename Category >
		class file_functions;

	/**
	 * file functions which don't depend on the character type:
	 */
	template <>
		class basic_file_functions< file_locked_category > {
			public:
				static int do_close( std::FILE *fp ) noexcept {
					return std::fclose( fp );
				}

				static int do_wide( std::FILE *fp, int mode ) noexcept {
					return std::fwide( fp, mode );
				}

				static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) noexcept {
					return std::fwrite( buffer, size, count, fp );
				}

				static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) noexcept {
					return std::fread( buffer, size, count, fp );
				}

				static int do_seek( std::FILE *fp, long offset, int origin ) noexcept {
					return std::fseek( fp, offset, origin );
				}

				static long do_tell( std::FILE *fp ) noexcept {
					return std::ftell( fp );
				}

				static int do_setpos( std::FILE *fp, const std::fpos_t *position ) noexcept {
					return std::fsetpos( fp, position );
				}

				static int do_getpos( std::FILE *fp, std::fpos_t *position ) noexcept {
					return std::fgetpos( fp, position );
				}

				static int do_flush( std::FILE *fp ) noexcept {
					return std::fflush( fp );
				}

				static void do_setbuf( std::FILE *fp, char *buffer ) noexcept {
					return std::setbuf( fp, buffer );
				}

				static int do_setvbuf( std::FILE *fp, char *buffer, int mode, std::size_t size ) noexcept {
					return std::setvbuf( fp, buffer, mode, size );
				}

				static void do_rewind( std::FILE *fp ) noexcept {
					return std::rewind( fp );
				}

				static void do_clearerr( std::FILE *fp ) noexcept {
					return std::clearerr( fp );
				}

				static int do_eof( std::FILE *fp ) noexcept {
					return std::feof( fp );
				}

				static int do_error( std::FILE *fp ) noexcept {
					return std::ferror( fp );
				}
		};

	/**
	 * file functions for char(s):
	 */
	template <>
		class file_functions< char, file_locked_category > : public basic_file_functions< file_locked_category > {
			public:
				typedef std::char_traits< char > char_traits_t;

				static int do_not_eof( int result ) noexcept {
					return char_traits_t::not_eof( result );
				}

				static std::FILE *do_open( const char fileName[], const char openMode[] ) noexcept {
					return std::fopen( fileName, openMode );
				}

				static int do_putc( std::FILE *fp, char c ) noexcept {
					return std::putc( c, fp );
				}

				static int do_getc( std::FILE *fp ) noexcept {
					return std::getc( fp );
				}

				static int do_ungetc( std::FILE *fp, int c ) noexcept {
					return std::ungetc( c, fp );
				}

				static int do_puts( std::FILE *fp, const char s[] ) noexcept {
					return std::fputs( s, fp );
				}

				static char *do_gets( std::FILE *fp, char *str, int count ) noexcept {
					return std::fgets( str, count, fp );
				}

				static int do_vprintf( std::FILE *fp, const char format[], va_list args ) noexcept {
					return std::vfprintf( fp, format, args );
				}

				template < typename ... Args >
					static int do_printf( std::FILE *fp, const char format[], Args && ... args ) noexcept {
						return std::fprintf( fp, format, std::forward< Args >( args ) ... );
					}
		};

	/**
	 * file functions for wchar_t(s)
	 */
	template <>
		class file_functions< wchar_t, file_locked_category > : public basic_file_functions< file_locked_category > {
			public:
				typedef std::char_traits< wchar_t > char_traits_t;

				static wint_t do_not_eof( wint_t result ) noexcept {
					return char_traits_t::not_eof( result );
				}

				// There is no wfopen function, so we only provide a char based version:
				static std::FILE *do_open( const char fileName[], const char openMode[] ) noexcept {
					return std::fopen( fileName, openMode );
				}

				static wint_t do_putc( std::FILE *fp, wchar_t c ) noexcept {
					return std::putwc( c, fp );
				}

				static wint_t do_getc( std::FILE *fp ) noexcept {
					return std::getwc( fp );
				}

				static wint_t do_ungetc( std::FILE *fp, wint_t c ) noexcept {
					return std::ungetwc( c, fp );
				}

				static int do_puts( std::FILE *fp, const wchar_t s[] ) noexcept {
					return std::fputws( s, fp );
				}

				static wchar_t *do_gets( std::FILE *fp, wchar_t *str, int count ) noexcept {
					return std::fgetws( str, count, fp );
				}

				static int do_vprintf( std::FILE *fp, const wchar_t format[], va_list args ) noexcept {
					return std::vfwprintf( fp, format, args );
				}

				template < typename ... Args >
					static int do_printf( std::FILE *fp, const wchar_t format[], Args && ... args ) noexcept {
						return std::fwprintf( fp, format, std::forward< Args >( args ) ... );
					}
		};

	// TODO: Should we name the methods the same (without the prefixed 'f') as the C-functions?

	template < typename Char, typename Category = file_locked_category, typename Functions = file_functions< Char, Category >>
		class basic_file {
			public:
				typedef typename Functions::char_traits_t char_traits_t;

				/// Represents an int which can hold a char or an EOF value:

				typedef typename char_traits_t::int_type char_int_t;

				/// Represents an offset to be used by seek/tell:

				typedef long offset_t;

				/// The constant for checking with char_int_t get() methods:

				static const char_int_t eof = char_traits_t::eof();

				/// Indicates from where to start the seek:

				enum class origin {
					begin   = SEEK_SET,
					current = SEEK_CUR,
					end     = SEEK_END
				};

				/// Indicates what kind of buffering should be used:

				enum class buffer_mode {
					full = _IOFBF,
					line = _IOLBF,
					none = _IONBF
				};

				/// Indicates what orientation the file has:

				enum class orientation {
					byte = -1,
					none =  0,
					wide =  1
				};

				/// Indicates how the file should be open:

				enum class open_mode : unsigned {
					read,
					write,
					append,
					extended,
					binary
				};

				typedef enum_flags< open_mode > open_modes;

				basic_file() {
					file_ = nullptr;
				}

				// For now we forbid copying, becaue what should happen if two instances 'point' to
				// the same file? Should the first close be ignored and only the second close actually
				// closes the file? Or should the first close succeed and the second close then fails?

				basic_file( const basic_file & ) = delete;
				basic_file &operator = ( const basic_file & ) = delete;

				basic_file( const char fileName[], const enum_flags< open_mode > mode ) {
					open( fileName, mode );
				}

				~basic_file() noexcept {
					// Close the file with the non-throwing close method:

					std::error_code errorCode;
					close( &errorCode );
				}

				// Opening a file:

				bool open( const char fileName[], const enum_flags< open_mode > mode ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return open( fileName, mode, errorCode );
					});
				}

				bool open( const char fileName[], open_modes mode, std::error_code *errorCode ) noexcept {

					// Make the mode string:

					std::string modeString;
					if ( mode & open_mode::read )
						modeString += 'r';
					if ( mode & open_mode::write )
						modeString += 'w';
					if ( mode & open_mode::append )
						modeString += 'a';

					if ( mode & open_mode::extended )
						modeString += '+';

					if ( mode & open_mode::binary )
						modeString += 'b';

					// Open the file:

					file_ = Functions::do_open( fileName, modeString.c_str() );
					bool success = ( file_ != nullptr );

					*errorCode = get_error_code( success );
					return success;
				}

				// Closing a file:

				bool close() {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return close( errorCode );
					});
				}

				bool close( std::error_code *errorCode ) noexcept {
					if ( file_ == nullptr ) {
						*errorCode = std::make_error_code( std::errc::invalid_argument );
						return false;
					}
					auto result = Functions::do_close( file_ );
					bool success = ( result == 0 );

					// http://en.cppreference.com/w/cpp/io/c/fclose
					// "Whether or not the operation succeeds, the stream is no longer associated with a file"

					file_ = nullptr;

					*errorCode = get_error_code( success );
					return success;
				}

				// Putting a char:

				char_int_t put( Char c ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return put( c, errorCode );
					});
				}

				char_int_t put( Char c, std::error_code *errorCode ) noexcept {
					auto result = Functions::do_putc( file_, c );
					bool success = Functions::do_not_eof( result );

					*errorCode = get_error_code( success );
					return result;
				}

				// Getting a char:

				char_int_t get() {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return get( errorCode );
					});
				}

				char_int_t get( std::error_code *errorCode ) noexcept {
					if ( file_ == nullptr ) {
						*errorCode = std::make_error_code( std::errc::invalid_argument );
						return eof;
					}
					auto result = Functions::do_getc( file_ );
					bool success = Functions::do_not_eof( result );

					*errorCode = get_error_code( success );
					return result;
				}

				// Ungetting a char:

				char_int_t unget( Char c ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return unget( c, errorCode );
					});
				}

				char_int_t unget( Char c, std::error_code *errorCode ) noexcept {
					auto result = Functions::do_ungetc( file_, c );
					bool success = Functions::do_not_eof( result );

					*errorCode = get_error_code( success );
					return result;
				}

				// Putting a string:

				const Char *put( const Char s[] ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return put( s, errorCode );
					});
				}

				const Char *put( const Char s[], std::error_code *errorCode ) noexcept {
					auto result = Functions::do_puts( file_, s );
					bool success = Functions::do_not_eof( result );

					*errorCode = get_error_code( success );
					return success ? s : nullptr;
				}

				// Getting a string:

				Char *get( Char *s, int count ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return get( s, count, errorCode );
					});
				}

				Char *get( Char *s, int count, std::error_code *errorCode ) noexcept {
					Char *result = Functions::do_gets( file_, s, count );
					bool success = ( result != nullptr );

					*errorCode = get_error_code( success );
					return result;
				}

				// Writing raw data:

				std::size_t write( const void *buffer, std::size_t size, std::size_t count ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return write( buffer, size, count, errorCode );
					});
				}

				std::size_t write( const void *buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) noexcept {
					return call_transfer( Functions::do_write, buffer, size, count, errorCode );
				}

				// Reading raw data:

				std::size_t read( void *buffer, std::size_t size, std::size_t count ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return read( buffer, size, count, errorCode );
					});
				}

				std::size_t read( void *buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) noexcept {
					return call_transfer( Functions::do_read, buffer, size, count, errorCode );
				}

				// Printing a formatted string:

				int print( const Char format[], va_list args ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return print( format, args, errorCode );
					});
				}

				int print( const Char format[], va_list args, std::error_code *errorCode ) noexcept {
					auto result = Functions::do_vprintf( file_, format, args );
					bool success = Functions::do_not_eof( result );

					*errorCode = get_error_code( success );
					return result;
				}

				template < typename ... Args >
					int print( const Char format[], Args && ... args ) {
						return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
							return print( errorCode, format, std::forward< Args >( args ) ... );
						});
					}

				template < typename ... Args >
					int print( std::error_code *errorCode, const Char format[], Args && ... args ) noexcept {
						auto result = Functions::do_printf( file_, format, std::forward< Args >( args ) ... );
						bool success = Functions::do_not_eof( result );

						*errorCode = get_error_code( success );
						return result;
					}

				// Seeking to an offset:

				bool seek( offset_t offset, origin origin ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return seek( offset, origin, errorCode );
					});
				}

				bool seek( offset_t offset, origin origin, std::error_code *errorCode ) noexcept {
					auto result = Functions::do_seek( file_, offset, static_cast< int >( origin ));
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return success;
				}

				// Telling the offset:

				offset_t tell() {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return tell( errorCode );
					});
				}

				offset_t tell( std::error_code *errorCode ) noexcept {
					auto result = Functions::do_tell( file_ );
					bool success = ( result != offset_t( -1 ));

					*errorCode = get_error_code( success );
					return result;
				}

				// Setting a position:

				bool set_position( const fpos_t &position ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return set_position( position, errorCode );
					});
				}

				bool set_position( const std::fpos_t &position, std::error_code *errorCode ) noexcept {
					auto result = Functions::do_setpos( file_, &position );
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return success;
				}

				// Getting the position:

				std::fpos_t get_position() {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return get_position( errorCode );
					});
				}

				std::fpos_t get_position( std::error_code *errorCode ) noexcept {
					fpos_t position;
					auto result = Functions::do_getpos( file_, &position );
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return position;
				}

				// Setting an orientation:

				void set_orientation( orientation newOrientation ) noexcept {
					// The value 0 (orientation::none) is used to query the orientation, so it doesn't
					// makes sense to allow that value.

					if ( newOrientation == orientation::byte || newOrientation == orientation::wide )
						Functions::do_wide( file_, static_cast< int >( newOrientation ));
				}

				// Getting the orientation:

				orientation get_orientation() noexcept {
					auto result = Functions::do_wide( file_, 0 );
					if( result < 0 )
						return orientation::byte;
					else if ( result > 0 )
						return orientation::wide;
					else // if ( result == 0 )
						return orientation::none;
				}

				// Flushing the file:

				bool flush() {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return flush( errorCode );
					});
				}

				bool flush( std::error_code *errorCode ) noexcept {
					auto result = Functions::do_flush( file_ );
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return success;
				}

				void rewind() noexcept {
					Functions::do_rewind( file_ );
				}

				// Setting a buffer:

				void set_buffer( void *buffer ) noexcept {
					Functions::do_setbuf( file_, static_cast< char * >( buffer ));
				}

				bool set_buffer( void *buffer, buffer_mode mode, std::size_t bufferSize ) {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return set_buffer( buffer, mode, bufferSize, errorCode );
					});
				}

				bool set_buffer( void *buffer, buffer_mode mode, std::size_t bufferSize, std::error_code *errorCode ) noexcept {
					auto result = Functions::do_setvbuf( file_, static_cast< char * >( buffer ), static_cast< int >( mode ), bufferSize );
					bool success = ( result == 0 );

					*errorCode = get_error_code( success );
					return success;
				}

				void clear_error() noexcept {
					Functions::do_clearerr( file_ );
				}

				// Checking for end of file:

				bool is_eof() const {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return is_eof( errorCode );
					});

				}

				bool is_eof( std::error_code *errorCode ) const noexcept {
					if ( file_ != nullptr ) {
						errorCode->clear();
						return Functions::do_eof( file_ ) != 0;
					} else {
						*errorCode = std::make_error_code( std::errc::invalid_argument );
						return false;
					}
				}

				// Checking for error:

				bool is_error() const {
					return call_and_throw_if_error([ & ]( std::error_code *errorCode ) {
						return is_error( errorCode );
					});
				}

				bool is_error( std::error_code *errorCode ) const noexcept {
					if ( file_ != nullptr ) {
						errorCode->clear();
						return Functions::do_error( file_ ) != 0;
					} else {
						*errorCode = std::make_error_code( std::errc::invalid_argument );
						return false;
					}
				}

			private:
				// Wrapper function for calling fread()/fwrite() and evaluating the result:

				template < typename T, typename Function >
					std::size_t call_transfer( Function &&transferFunction, T buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) noexcept {
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

				template < typename Functor >
					auto call_and_set_error_code( std::error_code *errorCode, Functor &&functor ) const noexcept -> decltype( functor() ) {
						int oldErrNo = errno;
						errno = ENONE;
						auto result = functor();
						bool success = ( errno == ENONE );
						if ( success )
							errorCode->clear();
						else
							*errorCode = make_errno_error_code( errno );

						errno = oldErrNo;
						return result;
					}

				std::error_code get_error_code( bool success ) const noexcept {
					std::error_code errorCode;

					if ( !success ) {
						if ( file_ != nullptr ) {
							if ( is_eof( &errorCode ) && !errorCode )
								errorCode = make_error_code( file_error::eof );
							else if ( is_error( &errorCode ) && !errorCode ) {
								if ( errno != ENONE )
									errorCode = make_errno_error_code( errno );
								else
									errorCode = make_error_code( file_error::unspecific );
							}
						} else {
							if ( errno != ENONE )
								errorCode = make_errno_error_code( errno );
							else
								errorCode = make_error_code( file_error::unspecific );
						}
					}
					return errorCode;
				}

				std::FILE *file_;
			};
} } }

