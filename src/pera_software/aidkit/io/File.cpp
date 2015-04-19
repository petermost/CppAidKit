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

#include "File.hpp"
#include <cerrno>
#include <cstdarg>

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

//#########################################################################################################

FileNotFoundException::FileNotFoundException( const string &fileName )
	: FileException( ENOENT )
{
	fileName_ = fileName;
}

const string &FileNotFoundException::fileName() const
{
	return fileName_;
}

//#########################################################################################################

EndOfFileException::EndOfFileException()
	: FileException( EOF, "EOF" )
{
}

//#########################################################################################################

File::File()
{
}


File::File( shared_ptr< FILE > file )
{
	if ( file )
		file_ = file;
	else
		throw FileException( EINVAL );
}

File::File( const string &fileName, open_mode mode )
{
	open( fileName, mode );
}


File::~File()
{
}


static const char *make_mode_string( File::open_mode mode )
{
	switch ( mode ) {
		case File::open_mode::read:
			return "rb";

		case File::open_mode::write:
			return "wb";

		case File::open_mode::append:
			return "ab";

		case File::open_mode::read_write:
			return "r+b";

		case File::open_mode::write_read:
			return "w+b";

		case File::open_mode::append_read_write:
			return "a+b";

		default:
			return "";
	}
}


void File::open( const string &fileName, open_mode mode )
{
	FILE *file;

	if (( file = AIDKIT_UNLOCKED_FOPEN( fileName.c_str(), make_mode_string( mode ))) != nullptr ) {
		// We don't bind the deleter to File::close to prevent exceptions from the destructor.

		file_ = shared_ptr< FILE >( file, AIDKIT_UNLOCKED_FCLOSE );
		fileName_ = fileName;
	} else {
		if ( errno == ENOENT )
			throw FileNotFoundException( fileName );
		else
			throw FileException::lastError();
	}
}


void File::close()
{
	if ( file_ ) {
		// Close the file via the deleter because we don't necessary know whether to use fclose!

		auto deleter = get_deleter< int (*)( FILE * )>( file_ );
		if ( deleter != nullptr && ( *deleter )( file_.get() ) == EOF )
			throw FileException::lastError();
	}
}


void File::set_buffer( void *buffer, buffer_mode mode, size_t size )
{
	setvbuf( file_.get(), static_cast< char * >( buffer ), static_cast< int >( mode ), size );
}


void File::put( const string &str )
{
	if ( AIDKIT_UNLOCKED_FPUTS( str.c_str(), file_.get() ) == EOF && error() )
		throw FileException::lastError();
}


void File::put( const wstring &str )
{
	if ( AIDKIT_UNLOCKED_FPUTWS( str.c_str(), file_.get() ) == WEOF && error() )
		throw FileException::lastError();
}


int File::print( const char format[], ... )
{
	va_list arguments;

	va_start( arguments, format );
	int count = vfprintf( file_.get(), format, arguments );
	va_end( arguments );

	if ( count < 0 )
		throw FileException::lastError();

	return count;
}


int File::print( const wchar_t format[], ... )
{
	va_list arguments;

	va_start( arguments, format );
	int count = vfwprintf( file_.get(), format, arguments );
	va_end( arguments );

	if ( count < 0 )
		throw FileException::lastError();

	return count;
}


File::offset_t File::tell()
{
	offset_t offset;

	if (( offset = AIDKIT_UNLOCKED_FTELL( file_.get() )) != -1 )
		return offset;
	else
		throw FileException::lastError();
}


void File::seek( offset_t offset, origin origin )
{
	if ( AIDKIT_UNLOCKED_FSEEK( file_.get(), offset, static_cast< int >( origin )) != 0 )
		throw FileException::lastError();
}


void File::rewind()
{
	AIDKIT_UNLOCKED_REWIND( file_.get() );
}


fpos_t File::get_position() const
{
	fpos_t position;

	if ( AIDKIT_UNLOCKED_FGETPOS( file_.get(), &position ) == 0 )
		return position;
	else
		throw FileException::lastError();
}


void File::set_position( const fpos_t &position )
{
	if ( AIDKIT_UNLOCKED_FSETPOS( file_.get(), &position ) != 0 )
		throw FileException::lastError();
}


void File::flush()
{
	if ( AIDKIT_UNLOCKED_FFLUSH( file_.get() ) == EOF )
		throw FileException::lastError();
}

void File::clear_error()
{
	AIDKIT_UNLOCKED_CLEARERR( file_.get() );
}

const string &File::name() const
{
	return fileName_;
}

} } }
