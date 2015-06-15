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

	// TODO: Write file_traits<> for file_null_category.

	struct file_null_category : file_category {
	};

	struct file_locked_category : file_category {
	};

	struct file_unlocked_category : file_category {
	};

	// TODO: Write file_traits<> for file_temporary_category.

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

	// file_traits<> for char/wchar_t, locked:

	template <>
		struct file_traits< char, file_locked_category > : file_traits_base< char > {

			static std::FILE *do_open( const char fileName[], const char openMode[] ) {
				return std::fopen( fileName, openMode );
			}

			static int do_close( std::FILE *fp ) {
				return std::fclose( fp );
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

			static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
				return std::fwrite( buffer, size, count, fp );
			}

			static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
				return std::fread( buffer, size, count, fp );
			}

			template < typename ... Args >
				static int do_print( std::FILE *fp, const char format[], Args && ... args ) {
					return std::fprintf( fp, format, std::forward< Args >( args ) ... );
				}

			static int do_eof( std::FILE *fp ) {
				return std::feof( fp );
			}

			static int do_error( std::FILE *fp ) {
				return std::ferror( fp );
			}
		};
	template <>
		struct file_traits< wchar_t, file_locked_category > : file_traits_base< char > {

			static std::FILE *do_open( const wchar_t fileName[], const wchar_t openMode[] ) {
				return std::fopen( wstring_to_string( fileName ).c_str(), wstring_to_string( openMode ).c_str() );
			}

			static int do_close( std::FILE *fp ) {
				return std::fclose( fp );
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

			static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
				return std::fwrite( buffer, size, count, fp );
			}

			static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
				return std::fread( buffer, size, count, fp );
			}

			template < typename ... Args >
				static int do_print( std::FILE *fp, const wchar_t format[], Args && ... args ) {
					return std::fwprintf( fp, format, std::forward< Args >( args ) ... );
				}

			static int do_eof( std::FILE *fp ) {
				return std::feof( fp );
			}

			static int do_error( std::FILE *fp ) {
				return std::ferror( fp );
			}
		};

	// file_traits<> for char/wchar_t, unlocked:

#if defined( AIDKIT_GCC ) && !defined( AIDKIT_MINGW )

		template <>
			struct file_traits< char, file_unlocked_category > : file_traits_base< char > {

				static std::FILE *do_open( const char fileName[], const char openMode[] ) {
					return std::fopen( fileName, openMode );
				}

				static int do_close( std::FILE *fp ) {
					return std::fclose( fp );
				}

				static int do_putc( std::FILE *fp, char c ) {
					return putc_unlocked( c, fp );
				}

				static int do_getc( std::FILE *fp ) {
					return getc_unlocked( fp );
				}

				static int do_puts( std::FILE *fp, const char s[] ) {
					return fputs_unlocked( s, fp );
				}

				static char *do_gets( std::FILE *fp, char *str, int count ) {
					return fgets_unlocked( str, count, fp );
				}

				static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
					return fwrite_unlocked( buffer, size, count, fp );
				}

				static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
					return fread_unlocked( buffer, size, count, fp );
				}

				template < typename ... Args >
					static int do_print( std::FILE *fp, const char format[], Args && ... args ) {
						return std::fprintf( fp, format, std::forward< Args >( args ) ... );
					}

				static int do_eof( std::FILE *fp ) {
					return feof_unlocked( fp );
				}

				static int do_error( std::FILE *fp ) {
					return ferror_unlocked( fp );
				}
			};

		template <>
			struct file_traits< wchar_t, file_unlocked_category > : file_traits_base< wchar_t > {

				static std::FILE *do_open( const wchar_t fileName[], const wchar_t openMode[] ) {
					return std::fopen( wstring_to_string( fileName ).c_str(), wstring_to_string( openMode ).c_str() );
				}

				static int do_close( std::FILE *fp ) {
					return std::fclose( fp );
				}

				static wint_t do_putc( std::FILE *fp, wchar_t c ) {
					return putwc_unlocked( c, fp );
				}

				static wint_t do_getc( std::FILE *fp ) {
					return getwc_unlocked( fp );
				}

				static int do_puts( std::FILE *fp, const wchar_t s[] ) {
					return fputws_unlocked( s, fp );
				}

				static wchar_t *do_gets( std::FILE *fp, wchar_t *str, int count ) {
					return fgetws_unlocked( str, count, fp );
				}

				static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
					return fwrite_unlocked( buffer, size, count, fp );
				}

				static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
					return fread_unlocked( buffer, size, count, fp );
				}

				template < typename ... Args >
					static int do_print( std::FILE *fp, const wchar_t format[], Args && ... args ) {
						return std::fwprintf( fp, format, std::forward< Args >( args ) ... );
					}

				static int do_eof( std::FILE *fp ) {
					return feof_unlocked( fp );
				}

				static int do_error( std::FILE *fp ) {
					return ferror_unlocked( fp );
				}
			};

#else // AIDKIT_MINGW

		template <>
			struct file_traits< char, file_unlocked_category > : file_traits_base< char > {

				static std::FILE *do_open( const char fileName[], const char openMode[] ) {
					return std::fopen( fileName, openMode );
				}

				static int do_close( std::FILE *fp ) {
					return _fclose_nolock( fp );
				}

				static int do_getc( std::FILE *fp ) {
					return _getc_nolock( fp );
				}

				static int do_putc( std::FILE *fp, char c ) {
					return _putc_nolock( c, fp );
				}

				static int do_puts( std::FILE *fp, const char s[] ) {
					return std::fputs( s, fp );
				}

				static char *do_gets( std::FILE *fp, char *str, int count ) {
					return std::fgets( str, count, fp );
				}

				static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
					return _fwrite_nolock( buffer, size, count, fp );
				}

				static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
					return _fread_nolock( buffer, size, count, fp );
				}

				template < typename ... Args >
					static int do_print( std::FILE *fp, const char format[], Args && ... args ) {
						return std::fprintf( fp, format, std::forward< Args >( args ) ... );
					}

				static int do_eof( std::FILE *fp ) {
					return std::feof( fp );
				}

				static int do_error( std::FILE *fp ) {
					return std::ferror( fp );
				}
			};

		template <>
			struct file_traits< wchar_t, file_unlocked_category > : file_traits_base< wchar_t > {

				static std::FILE *do_open( const wchar_t fileName[], const wchar_t openMode[] ) {
					return _wfopen( fileName, openMode );
				}

				static int do_close( std::FILE *fp ) {
					return _fclose_nolock( fp );
				}

				static wint_t do_getc( std::FILE *fp ) {
					return _getwc_nolock( fp );
				}

				static wint_t do_putc( std::FILE *fp, wchar_t c ) {
					return _putwc_nolock( c, fp );
				}

				static int do_puts( std::FILE *fp, const wchar_t s[] ) {
					return std::fputws( s, fp );
				}

				static wchar_t *do_gets( std::FILE *fp, wchar_t str[], int count ) {
					return std::fgetws( str, count, fp );
				}

				static std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) {
					return _fwrite_nolock( buffer, size, count, fp );
				}

				static std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) {
					return _fread_nolock( buffer, size, count, fp );
				}

				template < typename ... Args >
					static int do_print( std::FILE *fp, const wchar_t format[], Args && ... args ) {
						return std::fwprintf( fp, format, std::forward< Args >( args ) ... );
					}

				static int do_eof( std::FILE *fp ) {
					return std::feof( fp );
				}

				static int do_error( std::FILE *fp ) {
					return std::ferror( fp );
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
						set_error_code( errorCode );
						return false;
					}
				}

				bool close( std::error_code *errorCode ) {
					auto result = Traits::do_close( file_ );
					if ( Traits::is_not_eof( result )) {
						return true;
					} else {
						set_error_code( file_, errorCode );
						return false;
					}
				}

				bool put( Char c, std::error_code *errorCode ) {
					auto result = Traits::do_putc( file_, c );
					if ( Traits::is_not_eof( result ))
						return true;
					else {
						set_error_code( file_, errorCode );
						return false;
					}
				}

				bool get( Char *c, std::error_code *errorCode ) {
					auto result = Traits::do_getc( file_ );
					if ( Traits::is_not_eof( result )) {
						*c = static_cast< Char >( result );
						return true;
					} else {
						set_error_code( file_, errorCode );
						return false;
					}
				}

				bool put( const Char s[], std::error_code *errorCode ) {
					auto result = Traits::do_puts( file_, s );
					if ( Traits::is_not_eof( result ))
						return true;
					else {
						set_error_code( file_, errorCode );
						return false;
					}
				}

				bool get( Char *s, int count, std::error_code *errorCode ) {
					Char *result = Traits::do_gets( file_, s, count );
					if ( result != nullptr )
						return true;
					else {
						set_error_code( file_, errorCode );
						return false;
					}
				}

				bool write( const void *buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) {
					std::size_t result = Traits::do_write( file_, buffer, size, count );
					if ( result == count )
						return true;
					else {
						set_error_code( file_, errorCode );
						return false;
					}
				}

				bool read( void *buffer, std::size_t size, std::size_t count, std::error_code *errorCode ) {
					std::size_t result = Traits::do_read( file_, buffer, size, count );
					if ( result == count )
						return true;
					else {
						set_error_code( file_, errorCode );
						return false;
					}
				}


				template < typename ... Args >
					bool print( std::error_code *errorCode, const Char format[], Args && ... args ) {
						auto result = Traits::do_print( file_, format, std::forward< Args >( args ) ... );
						if ( Traits::is_not_eof( result ))
							return true;
						else {
							set_error_code( file_, errorCode );
							return false;
						}
					}

				bool is_eof() const {
					return Traits::do_eof( file_ );
				}

				bool is_error() const {
					return Traits::do_error( file_ );
				}

			private:
				static void set_error_code( std::error_code *errorCode ) {
					if ( errno != 0 )
						*errorCode = make_errno_error_code();
					else
						errorCode->clear();
				}

				static void set_error_code( std::FILE *fp, std::error_code *errorCode ) {
					if ( Traits::do_error( fp ))
						*errorCode = make_errno_error_code();
					else if ( Traits::do_eof( fp ))
						*errorCode = file_error::eof;
					else
						errorCode->clear();
				}

				std::FILE *file_;
				std::basic_string< Char > fileName_;

		};
} } }

