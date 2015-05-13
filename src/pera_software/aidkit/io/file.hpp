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
					file( const std::string &fileName, open_mode mode, std::error_code *errorCode = nullptr );
					virtual ~file();

					// Open/Close a file:

					void open( const std::string &fileName, open_mode mode );
					bool open( const std::string &fileName, open_mode mode, std::error_code *error );

					void close();
					bool close( std::error_code *error );

					// Set the buffer:

					void set_buffer( void *buffer, size_t size, buffer_mode mode = buffer_mode::full );

					// Put characters:

					void put( char c ) {
						fput_char_impl( file_.get(), c, std::putc, EOF );
					}

					bool put( char c, std::error_code *error ) {
						return fput_char_impl( file_.get(), c, error, std::putc, EOF );
					}

					void put( wchar_t c ) {
						fput_char_impl( file_.get(), c, std::putwc, WEOF );
					}

					bool put( wchar_t c, std::error_code *error ) {
						return fput_char_impl( file_.get(), c, error, std::putwc, WEOF );
					}

					// Get characters:

					void get( char *c ) {
						fget_char_impl( file_.get(), c, std::getc, EOF );
					}

					bool get( char *c, std::error_code *error ) {
						return fget_char_impl( file_.get(), c, error, std::getc, EOF );
					}

					void get( wchar_t *c ) {
						fget_char_impl( file_.get(), c, std::getwc, WEOF );
					}

					bool get( wchar_t *c, std::error_code *error ) {
						return fget_char_impl( file_.get(), c, error, std::getwc, WEOF );
					}

					// Put strings:

					void put( const char str[] ) {
						fput_string_impl( file_.get(), str, std::fputs, EOF );
					}

					bool put( const char str[], std::error_code *error ) {
						return fput_string_impl( file_.get(), str, error, std::fputs, EOF );
					}

					void put( const wchar_t str[] ) {
						fput_string_impl( file_.get(), str, std::fputws, WEOF );
					}

					bool put( const wchar_t str[], std::error_code *error ) {
						return fput_string_impl( file_.get(), str, error, std::fputws, WEOF );
					}

					void put( const std::string &str ) {
						put( str.c_str() );
					}

					bool put( const std::string &str, std::error_code *error ) {
						return put( str.c_str(), error );
					}

					void put( const std::wstring &str ) {
						put( str.c_str() );
					}

					bool put( const std::wstring &str, std::error_code *error ) {
						return put( str.c_str(), error );
					}

					// Print strings:

					template < typename ... Args >
						void print( const char format[], Args &&... args ) {
							fprint_format_impl( file_.get(), format, std::fprintf, std::forward< Args >( args ) ... );
						}

					template < typename ... Args >
						bool print( std::error_code *error, const char format[], Args && ... args ) {
							return fprint_format_impl( file_.get(), error, format, std::fprintf, std::forward< Args >( args ) ... );
						}

					template < typename ... Args >
						void print( const wchar_t format[], Args &&... args ) {
							fprint_format_impl( file_.get(), format, std::fwprintf, std::forward< Args >( args ) ... );
						}

					template < typename ... Args >
						bool print( std::error_code *error, const wchar_t format[], Args && ... args ) {
							return fprint_format_impl( file_.get(), error, format, std::fwprintf, std::forward< Args >( args ) ... );
						}

					size_t write( const void *buffer, size_t size, size_t count ) {
						size_t writeCount;

						if (( writeCount = std::fwrite( buffer, size, count, file_.get() )) < count && error() )
							throw std::system_error( make_errno_error_code() );
						else
							return writeCount;
					}

					// Write/Read binary data:

					void write( const void *buffer, size_t size );
					bool write( const void *buffer, size_t size, std::error_code *error );

					void read( void *buffer, size_t size );
					bool read( void *buffer, size_t size, std::error_code *error );

					// Positioning:

					void tell( offset_t *offset );
					bool tell( offset_t *offset, std::error_code *error );

					void seek( offset_t offset, origin origin = origin::begin );
					bool seek( offset_t offset, std::error_code *error, origin origin = origin::begin );

					void rewind();

					void get_position( fpos_t *position );
					bool get_position( fpos_t *position, std::error_code *error );

					void set_position( const fpos_t &position );
					bool set_position( const fpos_t &position, std::error_code *error );

					void flush();
					bool flush( std::error_code *error );

					void clear_error() {
						std::clearerr( file_.get() );
					}

					bool error() const {
						return std::ferror( file_.get() ) != 0;
					}

					bool eof() const {
						return std::feof( file_.get() ) != 0;
					}

					const std::string &name() const {
						return fileName_;
					}

				private:
					std::string fileName_;
					std::shared_ptr< std::FILE > file_;
			};
		}
	}
}
