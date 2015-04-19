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

#include <pera_software/aidkit/AidKit.hpp>
#include "ErrNoException.hpp"
#include "UnlockedFile.hpp"
#include <memory>
#include <string>
#include <cstdio>

namespace pera_software {
	namespace aidkit {
		namespace io {

			typedef ErrNoExceptionTemplate< class File > FileException;

			class AIDKIT_EXPORT FileNotFoundException : public FileException {
				public:
					FileNotFoundException( const std::string &fileName );

					const std::string &fileName() const;

				private:
					std::string fileName_;
			};


			class AIDKIT_EXPORT EndOfFileException : public FileException {
				public:
					EndOfFileException();
			};


			class AIDKIT_EXPORT File {
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

					File();
					File( std::shared_ptr< std::FILE > file );
					File( const std::string &fileName, open_mode mode );
					virtual ~File();

					// Open/Close a file:

					void open( const std::string &fileName, open_mode mode );
					void close();

					// Set the buffer:

					void set_buffer( void *buffer, buffer_mode mode, size_t size );

					// Write/Read characters:

					int put( int c )
					{
						if (( c = AIDKIT_UNLOCKED_PUTC( c, file_.get() )) == EOF && error() )
							throw FileException::lastError();
						else
							return c;
					}

					wint_t put( wchar_t c )
					{
						wint_t result;

						if (( result = AIDKIT_UNLOCKED_PUTWC( c, file_.get() )) == WEOF && error() )
							throw FileException::lastError();
						else
							return c;
					}

					int getc()
					{
						int c;

						if (( c = AIDKIT_UNLOCKED_GETC( file_.get() )) == EOF && error() )
							throw FileException::lastError();
						else
							return c;
					}

					wint_t getwc()
					{
						wint_t c;

						if (( c = AIDKIT_UNLOCKED_GETWC( file_.get() )) == WEOF && error() )
							throw FileException::lastError();
						else
							return c;
					}

					// Write strings:

					void put( const std::string &str );
					void put( const std::wstring &str );

					int print( const char format[], ... );
					int print( const wchar_t format[], ... );

					size_t write( const void *buffer, size_t size, size_t count )
					{
						size_t writeCount;

						if (( writeCount = AIDKIT_UNLOCKED_FWRITE( buffer, size, count, file_.get() )) < count && error() )
							throw FileException::lastError();
						else
							return writeCount;
					}

					// Write/Read binary data:

					size_t write( const void *buffer, size_t size )
					{
						return write( buffer, 1, size );
					}

					size_t read( void *buffer, size_t size, size_t count )
					{
						size_t readCount;

						if (( readCount = AIDKIT_UNLOCKED_FREAD( buffer, size, count, file_.get() )) < count && error() )
							throw FileException::lastError();
						else
							return readCount;
					}

					size_t read( void *buffer, size_t size )
					{
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

					bool error() const
					{
						return AIDKIT_UNLOCKED_FERROR( file_.get() ) != 0;
					}

					bool eof() const
					{
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
