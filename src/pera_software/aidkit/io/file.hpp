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

#include "file_impl.hpp"
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

	struct file_unlocked_category : file_category {
	};

	struct file_temporary_category : file_category {
	};

	template < typename Char >
		struct file_traits_base {
			typedef std::char_traits< Char > char_traits_type;
			typedef typename char_traits_type::int_type int_type;

			static bool is_not_eof( int_type result ) {
				return char_traits_type::not_eof( result );
			}


		};

	template < typename Char, typename Category >
		struct file_traits : file_traits_base< Char > {
		};

	template <>
		struct file_traits< char, file_locked_category > : file_traits_base< char > {

			static bool do_error( std::FILE *fp ) {
				return std::ferror( fp );
			}

			static std::FILE *do_open( const char fileName[], const char openMode[] ) {
				return std::fopen( fileName, openMode );
			}

			static int do_close( std::FILE *fp ) {
				return std::fclose( fp );
			}

			static int do_putc( std::FILE *fp, char c ) {
				return std::fputc( c, fp );
			}

			static int do_getc( std::FILE *fp ) {
				return std::fgetc( fp );
			}

			static int do_puts( std::FILE *fp, const char s[] ) {
				return std::fputs( s, fp );
			}

			static char *do_gets( std::FILE *fp, char *str, int count ) {
				return std::fgets( str, count, fp );
			}

			static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
				return std::fwrite( buffer, size, count, fp );
			}

			static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
				return std::fread( buffer, size, count, fp );
			}
		};
	template <>
		struct file_traits< wchar_t, file_locked_category > : file_traits_base< char > {

			static bool do_error( std::FILE *fp ) {
				return std::ferror( fp );
			}

			static std::FILE *do_open( const wchar_t fileName[], const wchar_t openMode[] ) {
				return std::fopen( wstring_to_string( fileName ).c_str(), wstring_to_string( openMode ).c_str() );
			}

			static int do_close( std::FILE *fp ) {
				return std::fclose( fp );
			}

			static wint_t do_putc( std::FILE *fp, wchar_t c ) {
				return std::fputwc( c, fp );
			}

			static wint_t do_getc( std::FILE *fp ) {
				return std::fgetwc( fp );
			}

			static int do_puts( std::FILE *fp, const wchar_t s[] ) {
				return std::fputws( s, fp );
			}

			static wchar_t *do_gets( std::FILE *fp, wchar_t *str, int count ) {
				return std::fgetws( str, count, fp );
			}

			static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
				return std::fwrite( buffer, size, count, fp );
			}

			static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
				return std::fread( buffer, size, count, fp );
			}
		};

#if defined( AIDKIT_GCC ) && defined( AIDKIT_MINGW )
		template <>
			struct file_traits< char, file_unlocked_category > : file_traits< char, file_locked_category > {

				static int do_close( std::FILE *fp ) {
					return _fclose_nolock( fp );
				}

				static int do_putc( std::FILE *fp, char c ) {
					return _putc_nolock( c, fp );
				}

				static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
					return _fwrite_nolock( buffer, size, count, fp );
				}

				static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
					return _fread_nolock( buffer, size, count, fp );
				}
			};

		template <>
			struct file_traits< wchar_t, file_unlocked_category > : file_traits< wchar_t, file_locked_category > {

				static int do_close( std::FILE *fp ) {
					return _fclose_nolock( fp );
				}

				static wint_t do_putc( std::FILE *fp, wchar_t c ) {
					return _putwc_nolock( c, fp );
				}
			};
#else // AIDKIT_MINGW
		template <>
			struct file_traits< char, file_unlocked_category > : file_traits< char, file_locked_category > {

				static bool do_error( std::FILE *fp ) {
					return ferror_unlocked( fp );
				}

				static int do_putc( std::FILE *fp, char c ) {
					return putc_unlocked( c, fp );
				}

				static int do_puts( std::FILE *fp, const char s[] ) {
					return fputs_unlocked( s, fp );
				}
			};

		template <>
			struct file_traits< wchar_t, file_unlocked_category > : file_traits< wchar_t, file_locked_category > {

				static bool do_error( std::FILE *fp ) {
					return ferror_unlocked( fp );
				}

				static wint_t do_putc( std::FILE *fp, wchar_t c ) {
					return fputwc_unlocked( c, fp );
				}

				static int do_puts( std::FILE *fp, const wchar_t s[] ) {
					return fputws_unlocked( s, fp );
				}
			};
#endif

	template < typename Char, typename Category, typename Traits = file_traits< Char, Category >>
		class basic_file {
			public:
				basic_file( const basic_file & ) = delete;
				basic_file &operator = ( const basic_file & ) = delete;

				basic_file() {
					file_ = nullptr;
				}

				bool open( const Char fileName[], const Char openMode[], std::error_code *errorCode ) {
					file_ = Traits::do_open( fileName, openMode );
					if ( file_ != nullptr ) {
						fileName_ = fileName;
						return true;
					} else {
						*errorCode = make_errno_error_code();
						return false;
					}
				}

				bool close( std::error_code *errorCode ) {
					auto result = Traits::do_close( file_ );
					if ( Traits::is_not_eof( result )) {
						return true;
					} else {
						*errorCode = make_errno_error_code();
						return false;
					}
				}

				bool put( Char c, std::error_code *errorCode ) {
					auto result = Traits::do_putc( file_, c );
					if ( Traits::is_not_eof( result ))
						return true;
					else {
						*errorCode = make_errno_error_code();
						return false;
					}
				}

				bool put( const Char s[], std::error_code *errorCode ) {
					auto result = Traits::do_puts( file_, s );
					if ( Traits::is_not_eof( result ))
						return true;
					else {
						*errorCode = make_errno_error_code();
						return false;
					}
				}

				bool write( const void *buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) {
					std::size_t result = Traits::do_write( file_, buffer, size, count );
					if ( result == count )
						return true;
					else {
						*errorCode = make_errno_error_code();
						return false;
					}
				}

			private:
				void get_error_code( std::FILE *file, std::error_code *errorCode ) {
					if ( Traits::is_error( file ))
						*errorCode = make_errno_error_code();
					else
						*errorCode = file_error::eof;
				}

				std::FILE *file_;
				std::basic_string< Char > fileName_;

		};

	class AIDKIT_API file {
		public:
			typedef long offset_t;

			enum class open_mode {
				read,
				write,
				append,
				read_write,
				write_read,
				append_read_write
			};

			enum class origin {
				begin = SEEK_SET,
				current = SEEK_CUR,
				end = SEEK_END
			};

			enum class buffer_mode {
				full = _IOFBF,
				line = _IOLBF,
				none = _IONBF
			};

			file();
			file( std::shared_ptr< std::FILE > file, std::error_code *errorCode = nullptr );
			file( const std::string &fileName, open_mode mode, std::error_code *errorCode = nullptr );
			virtual ~file();

			// Open/Close a file:

			void open( const std::string &fileName, open_mode mode );
			bool open( const std::string &fileName, open_mode mode, std::error_code *errorCode );

			void close();
			bool close( std::error_code *errorCode );

			// Set the buffer:

			void set_buffer( void *buffer, size_t size, buffer_mode mode = buffer_mode::full );

			// Put characters:

			void put( char c ) {
				file_put_char_impl( file_.get(), c, std::putc, EOF );
			}

			bool put( char c, std::error_code *errorCode ) {
				return file_put_char_impl( file_.get(), c, errorCode, std::putc, EOF );
			}

			void put( wchar_t c ) {
				file_put_char_impl( file_.get(), c, std::putwc, WEOF );
			}

			bool put( wchar_t c, std::error_code *errorCode ) {
				return file_put_char_impl( file_.get(), c, errorCode, std::putwc, WEOF );
			}

			// Get characters:

			void get( char *c ) {
				file_get_char_impl( file_.get(), c, std::getc, EOF );
			}

			bool get( char *c, std::error_code *errorCode ) {
				return file_get_char_impl( file_.get(), c, errorCode, std::getc, EOF );
			}

			void get( wchar_t *c ) {
				file_get_char_impl( file_.get(), c, std::getwc, WEOF );
			}

			bool get( wchar_t *c, std::error_code *errorCode ) {
				return file_get_char_impl( file_.get(), c, errorCode, std::getwc, WEOF );
			}

			// Put strings:

			void put( const char str[] ) {
				file_put_string_impl( file_.get(), str, std::fputs, EOF );
			}

			bool put( const char str[], std::error_code *errorCode ) {
				return file_put_string_impl( file_.get(), str, errorCode, std::fputs, EOF );
			}

			void put( const wchar_t str[] ) {
				file_put_string_impl( file_.get(), str, std::fputws, WEOF );
			}

			bool put( const wchar_t str[], std::error_code *errorCode ) {
				return file_put_string_impl( file_.get(), str, errorCode, std::fputws, WEOF );
			}

			void put( const std::string &str ) {
				put( str.c_str() );
			}

			bool put( const std::string &str, std::error_code *errorCode ) {
				return put( str.c_str(), errorCode );
			}

			void put( const std::wstring &str ) {
				put( str.c_str() );
			}

			bool put( const std::wstring &str, std::error_code *errorCode ) {
				return put( str.c_str(), errorCode );
			}

			// Print strings:

			template < typename ... Args >
				void print( const char format[], Args &&... args ) {
					file_print_impl( file_.get(), format, std::fprintf, std::forward< Args >( args ) ... );
				}

			template < typename ... Args >
				bool print( std::error_code *errorCode, const char format[], Args && ... args ) {
					return file_print_impl( file_.get(), errorCode, format, std::fprintf, std::forward< Args >( args ) ... );
				}

			template < typename ... Args >
				void print( const wchar_t format[], Args &&... args ) {
					file_print_impl( file_.get(), format, std::fwprintf, std::forward< Args >( args ) ... );
				}

			template < typename ... Args >
				bool print( std::error_code *errorCode, const wchar_t format[], Args && ... args ) {
					return file_print_impl( file_.get(), errorCode, format, std::fwprintf, std::forward< Args >( args ) ... );
				}

			// Write/Read binary data:

			bool read( void *buffer, size_t size, size_t count, std::error_code *errorCode ) {
				size_t readCount = std::fread( buffer, size, count, file_.get() );
				if ( readCount < count ) {
					get_error_code( file_.get(), errorCode );
					return false;
				} else
					return true;
			}

			void read( void *buffer, size_t size, size_t count ) {
				std::error_code errorCode;
				if ( !read( buffer, size, count, &errorCode ))
					throw std::system_error( errorCode );
			}

			bool read( void *buffer, size_t size, std::error_code *errorCode ) {
				return read( buffer, size, 1, errorCode );
			}

			void read( void *buffer, size_t size ) {
				read( buffer, size, 1 );
			}


			bool write( const void *buffer, size_t size, size_t count, std::error_code *errorCode ) {
				size_t writeCount = std::fwrite( buffer, size, count, file_.get() );
				if ( writeCount < count ) {
					get_error_code( file_.get(), errorCode );
					return false;
				} else
					return true;
			}

			void write( const void *buffer, size_t size, size_t count ) {
				std::error_code errorCode;
				if ( !write( buffer, size, count, &errorCode ))
					throw std::system_error( errorCode );
			}

			bool write( const void *buffer, size_t size, std::error_code *errorCode ) {
				return write( buffer, size, 1, errorCode );
			}

			void write( const void *buffer, size_t size ) {
				write( buffer, size, 1 );
			}

			// Positioning:

			void tell( offset_t *offset );
			bool tell( offset_t *offset, std::error_code *errorCode );

			void seek( offset_t offset, origin origin = origin::begin );
			bool seek( offset_t offset, std::error_code *errorCode, origin origin = origin::begin );

			void rewind();

			void get_position( fpos_t *position );
			bool get_position( fpos_t *position, std::error_code *errorCode );

			void set_position( const fpos_t &position );
			bool set_position( const fpos_t &position, std::error_code *errorCode );

			void flush();
			bool flush( std::error_code *errorCode );

			void clear_error() {
				std::clearerr( file_.get() );
			}

			const std::string &name() const {
				return fileName_;
			}

		private:
			std::string fileName_;
			std::shared_ptr< std::FILE > file_;
	};

} } }
