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

#include "files.hpp"
#include "file_exception.hpp"
#include <pera_software/aidkit/aidkit.hpp>
#include <memory>
#include <string>
#include <cstdio>

namespace pera_software {
	namespace aidkit {
		namespace io {


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
					file( std::shared_ptr< std::FILE > file );
					file( const std::string &fileName, open_mode mode, file_exception *error = nullptr );
					virtual ~file();

					// Open/Close a file:
					void open( const std::string &fileName, open_mode mode );
					bool open( const std::string &fileName, open_mode mode, file_exception *error );

					void close();
					bool close( file_exception *error );

					// Set the buffer:

					void set_buffer( void *buffer, buffer_mode mode, size_t size );

					// Write/Read characters:

					void put( char c ) {
						fput_char( file_.get(), c );
					}

					bool put( char c, file_exception *error ) {
						return fput_char( file_.get(), c, error );
					}

					void put( wchar_t c ) {
						fput_char( file_.get(), c );
					}

					bool put( wchar_t c, file_exception *error ) {
						return fput_char( file_.get(), c, error );
					}

					void get( char *c ) {
						fget_char( file_.get(), c );
					}

					bool get( char *c, file_exception *error ) {
						return fget_char( file_.get(), c, error );
					}

					void get( wchar_t *c ) {
						fget_char( file_.get(), c );
					}

					bool get( wchar_t *c, file_exception *error ) {
						return fget_char( file_.get(), c, error );
					}

					// Write strings:

					void put( const std::string &str ) {
						fput_string( file_.get(), str );
					}

					bool put( const std::string &str, file_exception *error ) {
						return fput_string( file_.get(), str, error );
					}

					void put( const std::wstring &str ) {
						fput_string( file_.get(), str );
					}

					bool put( const std::wstring &str, file_exception *error ) {
						return fput_string( file_.get(), str, error );
					}

					int print( const char format[], ... );
					int print( const wchar_t format[], ... );

					size_t write( const void *buffer, size_t size, size_t count ) {
						size_t writeCount;

						if (( writeCount = std::fwrite( buffer, size, count, file_.get() )) < count && error() )
							throw file_exception::last_error();
						else
							return writeCount;
					}

					// Write/Read binary data:

					size_t write( const void *buffer, size_t size ) {
						return write( buffer, 1, size );
					}

					size_t read( void *buffer, size_t size, size_t count ) {
						size_t readCount;

						if (( readCount = std::fread( buffer, size, count, file_.get() )) < count && error() )
							throw file_exception::last_error();
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
						return std::ferror( file_.get() ) != 0;
					}

					bool eof() const {
						return std::feof( file_.get() ) != 0;
					}

					const std::string &name() const;

				private:
					std::string fileName_;
					std::shared_ptr< std::FILE > file_;
			};
		}
	}
}
