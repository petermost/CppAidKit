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

#include <pera_software/aidkit/aidkit.hpp>
#include <string>

namespace pera_software { namespace aidkit { namespace io {

	template < typename Char >
		class file_operations {
			public:
				typedef std::char_traits< Char > char_traits_type;
				typedef typename char_traits_type::int_type int_type;

				static int_type do_not_eof( int_type result ) {
					return char_traits_type::not_eof( result );
				}

				virtual std::FILE *do_open( const Char fileName[], const Char openMode[] ) = 0;
				virtual int do_close( std::FILE *fp ) = 0;

				virtual std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) = 0;
				virtual std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) = 0;

				virtual int do_eof( std::FILE *fp ) = 0;
				virtual int do_error( std::FILE *fp ) = 0;

			protected:
				virtual ~file_operations() {
				}
		};

	template < typename Char >
		class common_locked_file_operations : public file_operations< Char > {
			public:
				virtual int do_close( std::FILE *fp ) override {
					return std::fclose( fp );
				}

				virtual std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) override {
					return std::fwrite( buffer, size, count, fp );
				}

				virtual std::size_t do_read( std::FILE *fp, void *buffer, std::size_t size, std::size_t count ) override {
					return std::fread( buffer, size, count, fp );
				}

				virtual int do_eof( std::FILE *fp ) override {
					return std::feof( fp );
				}

				virtual int do_error( std::FILE *fp ) override {
					return std::ferror( fp );
				}
		};

	class locked_file_operations : public common_locked_file_operations< char > {
		public:
			virtual std::FILE *do_open( const char fileName[], const char openMode[] ) override {
				return std::fopen( fileName, openMode );
			}
	};

	class locked_wfile_operations : public common_locked_file_operations< wchar_t > {
		public:
			virtual std::FILE *do_open( const wchar_t fileName[], const wchar_t openMode[] ) override {
				return _wfopen( fileName, openMode );
			}
	};

#if defined( AIDKIT_GCC ) && !defined( AIDKIT_MINGW )

#else // AIDKIT_MINGW

	template < typename Char >
		class common_unlocked_file_operations : public common_locked_file_operations< Char > {
			public:
				virtual std::size_t do_write( std::FILE *fp, const void *buffer, std::size_t size, std::size_t count ) override {
					return _fwrite_nolock( buffer, size, count, fp );
				}
		};

	class unlocked_file_operations : public common_unlocked_file_operations< char >, public locked_file_operations {
		public:
	};

	class unlocked_wfile_operations : public common_unlocked_file_operations< wchar_t >, public locked_wfile_operations {
		public:
	};

#endif

} } }
