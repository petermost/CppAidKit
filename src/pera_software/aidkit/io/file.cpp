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

#include "file.hpp"
#include <cerrno>
#include <cstdarg>
#include "file_exception.hpp"

namespace pera_software { namespace aidkit { namespace io {

using namespace std;


file::file() {
}


file::file( shared_ptr< FILE > file ) {
	if ( file )
		file_ = file;
	else
		throw file_exception( EINVAL );
}

file::file( const string &fileName, open_mode mode ) {
	open( fileName, mode );
}


file::~file() {
}


static const char *make_mode_string( file::open_mode mode ) {
	switch ( mode ) {
		case file::open_mode::read:
			return "rb";

		case file::open_mode::write:
			return "wb";

		case file::open_mode::append:
			return "ab";

		case file::open_mode::read_write:
			return "r+b";

		case file::open_mode::write_read:
			return "w+b";

		case file::open_mode::append_read_write:
			return "a+b";

		default:
			return "";
	}
}


void file::open( const string &fileName, open_mode mode ) {
	FILE *file;

	if (( file = fopen( fileName.c_str(), make_mode_string( mode ))) != nullptr ) {
		// We don't bind the deleter to file::close to prevent exceptions from the destructor.

		file_ = shared_ptr< FILE >( file, fclose );
		fileName_ = fileName;
	} else {
		if ( errno == ENOENT )
			throw file_not_found_exception( fileName );
		else
			throw file_exception::last_error();
	}
}


void file::close() {
	if ( file_ ) {
		// Close the file via the deleter because we don't necessary know whether to use fclose!

		auto deleter = get_deleter< int (*)( FILE * )>( file_ );
		if ( deleter != nullptr && ( *deleter )( file_.get() ) == EOF )
			throw file_exception::last_error();
	}
}


void file::set_buffer( void *buffer, buffer_mode mode, size_t size ) {
	setvbuf( file_.get(), static_cast< char * >( buffer ), static_cast< int >( mode ), size );
}


void file::put( const string &str ) {
	if ( fputs( str.c_str(), file_.get() ) == EOF && error() )
		throw file_exception::last_error();
}


void file::put( const wstring &str ) {
	if ( fputws( str.c_str(), file_.get() ) == WEOF && error() )
		throw file_exception::last_error();
}


int file::print( const char format[], ... ) {
	va_list arguments;

	va_start( arguments, format );
	int count = vfprintf( file_.get(), format, arguments );
	va_end( arguments );

	if ( count < 0 )
		throw file_exception::last_error();

	return count;
}


int file::print( const wchar_t format[], ... ) {
	va_list arguments;

	va_start( arguments, format );
	int count = vfwprintf( file_.get(), format, arguments );
	va_end( arguments );

	if ( count < 0 )
		throw file_exception::last_error();

	return count;
}


file::offset_t file::tell() {
	offset_t offset;

	if (( offset = ftell( file_.get() )) != -1 )
		return offset;
	else
		throw file_exception::last_error();
}


void file::seek( offset_t offset, origin origin ) {
	if ( fseek( file_.get(), offset, static_cast< int >( origin )) != 0 )
		throw file_exception::last_error();
}


void file::rewind() {
	::rewind( file_.get() );
}


fpos_t file::get_position() const {
	fpos_t position;

	if ( fgetpos( file_.get(), &position ) == 0 )
		return position;
	else
		throw file_exception::last_error();
}


void file::set_position( const fpos_t &position ) {
	if ( fsetpos( file_.get(), &position ) != 0 )
		throw file_exception::last_error();
}


void file::flush() {
	if ( fflush( file_.get() ) == EOF )
		throw file_exception::last_error();
}

void file::clear_error() {
	clearerr( file_.get() );
}

const string &file::name() const {
	return fileName_;
}

} } }
