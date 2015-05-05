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

//==================================================================================================

file::file() {
}


file::file( shared_ptr< FILE > file ) {
	if ( file )
		file_ = file;
	else
		throw file_exception( EINVAL );
}

file::file(const string &fileName, open_mode mode , file_exception *error ) {
	open( fileName, mode, error );
}


file::~file() {
}

//==================================================================================================

static const char *make_mode_string( file::open_mode mode, file_exception *error ) {
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
			*error = file_exception( EINVAL );
			return nullptr;
	}
}


void file::open( const string &fileName, open_mode mode ) {
	file_exception error;
	if ( !open( fileName, mode, &error ))
		throw error;
}

bool file::open( const string &fileName, open_mode mode, file_exception *error ) {
	const char *mode_string = make_mode_string( mode, error );
	if ( mode_string != nullptr ) {
		FILE *file_ptr = fopen( fileName.c_str(), mode_string );
		if ( file_ptr != nullptr ) {
			// We don't bind the deleter to file::close to prevent exceptions from the destructor.
			file_ = shared_ptr< FILE >( file_ptr, fclose );
			fileName_ = fileName;
			return true;
		} else {
			*error = file_exception::last_error();
			return false;
		}
	} else
		return false;
}

void file::close() {
	file_exception error;
	if ( !close( &error ))
		throw error;
}

bool file::close( file_exception *error ) {
	if ( file_ ) {
		// Close the file via the deleter because we don't necessary know whether to use fclose!

		auto deleter = get_deleter< int (*)( FILE * )>( file_ );
		if ( deleter != nullptr && ( *deleter )( file_.get() ) == 0 ) {
			return true;
		} else {
			*error = file_exception::last_error();
			return false;
		}
	} else
		return false;
}

//==================================================================================================

void file::set_buffer( void *buffer, buffer_mode mode, size_t size ) {
	setvbuf( file_.get(), static_cast< char * >( buffer ), static_cast< int >( mode ), size );
}

//==================================================================================================

void file::write( const void *buffer, size_t size ) {
	file_exception error;
	if ( !write( buffer, size, &error ))
		throw error;
}

void file::read( void *buffer, size_t size ) {
	file_exception error;
	if ( !read( buffer, size, &error ))
		throw error;
}


const size_t COUNT = 1;

bool file::write( const void *buffer, size_t size, file_exception *error ) {
	size_t writeCount = fwrite( buffer, size, COUNT, file_.get() );
	if ( writeCount < COUNT ) {
		*error = file_exception::last_error();
		return false;
	} else
		return true;
}

bool file::read( void *buffer, size_t size, file_exception *error ) {
	size_t readCount = fread( buffer, size, COUNT, file_.get() );
	if ( readCount < COUNT ) {
		*error = file_exception::last_error();
		return false;
	} else
		return true;
}

//==================================================================================================

void file::tell( offset_t *offset ) {
	file_exception error;
	if ( !tell( offset, &error ))
		throw error;
}

bool file::tell( offset_t *offset, file_exception *error ) {
	*offset = ftell( file_.get() );
	if ( *offset == -1 ) {
		*error = file_exception::last_error();
		return false;
	}
	else
		return true;
}


void file::seek( offset_t offset, origin origin ) {
	file_exception error;
	if ( !seek( offset, &error, origin ))
		throw error;
}


bool file::seek( offset_t offset, file_exception *error, origin origin ) {
	if ( fseek( file_.get(), offset, static_cast< int >( origin )) != 0 ) {
		*error = file_exception::last_error();
		return false;
	} else
		return true;
}

void file::rewind() {
	::rewind( file_.get() );
}

void file::get_position( fpos_t *position ) {
	file_exception error;
	if ( !get_position( position, &error ))
		throw error;
}


bool file::get_position( fpos_t *position, file_exception *error ) {
	if ( fgetpos( file_.get(), position ) != 0 ) {
		*error = file_exception::last_error();
		return false;
	}
	else
		return true;
}


void file::set_position( const fpos_t &position ) {
	file_exception error;
	if ( !set_position( position, &error ))
		throw error;
}


bool file::set_position( const fpos_t &position, file_exception *error ) {
	if ( fsetpos( file_.get(), &position ) != 0 ) {
		*error = file_exception::last_error();
		return false;
	} else
		return true;
}

void file::flush() {
	file_exception error;
	if ( !flush( &error ))
		throw error;
}

bool file::flush( file_exception *error ) {
	if ( fflush( file_.get() ) == EOF ) {
		*error = file_exception::last_error();
		return false;
	} else
		return true;
}

error_code make_last_errno_error_code() {
	return error_code( errno, generic_category() );
}

void file::test_function( error_code *error ) {
	*error = make_last_errno_error_code();
}

} } }
