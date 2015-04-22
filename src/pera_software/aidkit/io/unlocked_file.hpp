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
#include <pera_software/aidkit/platform.hpp>
#include "file_exception.hpp"
#include <memory>
#include <string>
#include <cstdio>

#if defined( AIDKIT_GCC )
	#if defined( AIDKIT_MINGW )
		#define AIDKIT_UNLOCKED_PUTC   _putc_nolock
		#define AIDKIT_UNLOCKED_PUTWC  _putwc_nolock
		#define AIDKIT_UNLOCKED_GETC   _getc_nolock
		#define AIDKIT_UNLOCKED_GETWC  _fgetwc_nolock
		#define AIDKIT_UNLOCKED_FWRITE _fwrite_nolock
		#define AIDKIT_UNLOCKED_FREAD  _fread_nolock

		// These *_nolock functions exist in the mingw491 stdio.h but result in a linker error!

		#define AIDKIT_UNLOCKED_FSEEK  ::_fseeki64
		#define AIDKIT_UNLOCKED_FTELL  ::_ftelli64
		#define AIDKIT_UNLOCKED_FFLUSH ::std::fflush
		#define AIDKIT_UNLOCKED_FCLOSE ::std::fclose

		// Missing unlocked functions:

		#define AIDKIT_UNLOCKED_FOPEN    ::std::fopen
		#define AIDKIT_UNLOCKED_FERROR   ::std::ferror
		#define AIDKIT_UNLOCKED_FEOF     ::std::feof
		#define AIDKIT_UNLOCKED_FPUTS    ::std::fputs
		#define AIDKIT_UNLOCKED_FPUTWS   ::std::fputws
		#define AIDKIT_UNLOCKED_REWIND   ::std::rewind
		#define AIDKIT_UNLOCKED_FGETPOS  ::std::fgetpos
		#define AIDKIT_UNLOCKED_FSETPOS  ::std::fsetpos
		#define AIDKIT_UNLOCKED_CLEARERR ::std::clearerr
	#else
		#define AIDKIT_UNLOCKED_PUTC     putc_unlocked
		#define AIDKIT_UNLOCKED_PUTWC    putwc_unlocked
		#define AIDKIT_UNLOCKED_GETC     getc_unlocked
		#define AIDKIT_UNLOCKED_GETWC    getwc_unlocked
		#define AIDKIT_UNLOCKED_FWRITE   fwrite_unlocked
		#define AIDKIT_UNLOCKED_FREAD    fread_unlocked
		#define AIDKIT_UNLOCKED_FPUTS    fputs_unlocked
		#define AIDKIT_UNLOCKED_FPUTWS   fputws_unlocked
		#define AIDKIT_UNLOCKED_FFLUSH   fflush_unlocked
		#define AIDKIT_UNLOCKED_FERROR   ferror_unlocked
		#define AIDKIT_UNLOCKED_FEOF     feof_unlocked
		#define AIDKIT_UNLOCKED_CLEARERR clearerr_unlocked

		// Missing unlocked functions:

		#define AIDKIT_UNLOCKED_FOPEN   ::std::fopen
		#define AIDKIT_UNLOCKED_FCLOSE  ::std::fclose
		#define AIDKIT_UNLOCKED_FTELL   ::std::ftell
		#define AIDKIT_UNLOCKED_FSEEK   ::std::fseek
		#define AIDKIT_UNLOCKED_REWIND  ::std::rewind
		#define AIDKIT_UNLOCKED_FGETPOS ::std::fgetpos
		#define AIDKIT_UNLOCKED_FSETPOS ::std::fsetpos
	#endif
#elif defined( AIDKIT_MSVC )
	#define AIDKIT_UNLOCKED_PUTC   _putc_nolock
	#define AIDKIT_UNLOCKED_PUTWC  _putwc_nolock
	#define AIDKIT_UNLOCKED_GETC   _getc_nolock
	#define AIDKIT_UNLOCKED_FWRITE _fwrite_nolock
	#define AIDKIT_UNLOCKED_FREAD  _fread_nolock
	#define AIDKIT_UNLOCKED_FTELL  _ftelli64_nolock
	#define AIDKIT_UNLOCKED_FSEEK  _fseeki64_nolock
	#define AIDKIT_UNLOCKED_FFLUSH _fflush_nolock
	#define AIDKIT_UNLOCKED_FCLOSE _fclose_nolock

	// Missing unlocked functions:

	#define AIDKIT_UNLOCKED_FOPEN    ::std::fopen
	#define AIDKIT_UNLOCKED_GETWC    ::std::getwc
	#define AIDKIT_UNLOCKED_FERROR   ::std::ferror
	#define AIDKIT_UNLOCKED_FEOF     ::std::feof
	#define AIDKIT_UNLOCKED_FPUTS    ::std::fputs
	#define AIDKIT_UNLOCKED_FPUTWS   ::std::fputws
	#define AIDKIT_UNLOCKED_REWIND   ::std::rewind
	#define AIDKIT_UNLOCKED_FGETPOS  ::std::fgetpos
	#define AIDKIT_UNLOCKED_FSETPOS  ::std::fsetpos
	#define AIDKIT_UNLOCKED_CLEARERR ::std::clearerr
#else
	#error Missing unlocked file functions!
#endif


namespace pera_software {
	namespace aidkit {
		namespace io {

			class AIDKIT_EXPORT unlocked_file {
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

					unlocked_file();
					unlocked_file( std::shared_ptr< std::FILE > file );
					unlocked_file( const std::string &fileName, open_mode mode );
					virtual ~unlocked_file();

					// Open/Close a file:

					void open( const std::string &fileName, open_mode mode );
					void close();

					// Set the buffer:

					void set_buffer( void *buffer, buffer_mode mode, size_t size );

					// Write/Read characters:

					int put( int c ) {
						if (( c = AIDKIT_UNLOCKED_PUTC( c, file_.get() )) == EOF && error() )
							throw file_exception::lastError();
						else
							return c;
					}

					wint_t put( wchar_t c ) {
						wint_t result;

						if (( result = AIDKIT_UNLOCKED_PUTWC( c, file_.get() )) == WEOF && error() )
							throw file_exception::lastError();
						else
							return c;
					}

					int getc() {
						int c;

						if (( c = AIDKIT_UNLOCKED_GETC( file_.get() )) == EOF && error() )
							throw file_exception::lastError();
						else
							return c;
					}

					wint_t getwc() {
						wint_t c;

						if (( c = AIDKIT_UNLOCKED_GETWC( file_.get() )) == WEOF && error() )
							throw file_exception::lastError();
						else
							return c;
					}

					// Write strings:

					void put( const std::string &str );
					void put( const std::wstring &str );

					int print( const char format[], ... );
					int print( const wchar_t format[], ... );

					size_t write( const void *buffer, size_t size, size_t count ) {
						size_t writeCount;

						if (( writeCount = AIDKIT_UNLOCKED_FWRITE( buffer, size, count, file_.get() )) < count && error() )
							throw file_exception::lastError();
						else
							return writeCount;
					}

					// Write/Read binary data:

					size_t write( const void *buffer, size_t size ) {
						return write( buffer, 1, size );
					}

					size_t read( void *buffer, size_t size, size_t count ) {
						size_t readCount;

						if (( readCount = AIDKIT_UNLOCKED_FREAD( buffer, size, count, file_.get() )) < count && error() )
							throw file_exception::lastError();
						else
							return readCount;
					}

					size_t read( void *buffer, size_t size ) {
						return read( buffer, 1, size );
					}

					// Positioning:

					offset_t tell();
					void seek( offset_t offset, origin origin = origin::begin );
					void rewind();

					fpos_t get_position() const;
					void set_position( const fpos_t &position );

					void flush();

					void clear_error();

					bool error() const {
						return AIDKIT_UNLOCKED_FERROR( file_.get() ) != 0;
					}

					bool eof() const {
						return AIDKIT_UNLOCKED_FEOF( file_.get() ) != 0;
					}

					const std::string &name() const;

				private:
					std::string fileName_;
					std::shared_ptr< FILE > file_;
			};
		}
	}
}
