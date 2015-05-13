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

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

//==================================================================================================

file::file() {
}


file::file( shared_ptr< FILE > file ) {
	if ( file )
		file_ = file;
	else
		throw system_error( make_error_code( errc::invalid_argument ));
}

file::file(const string &fileName, open_mode mode , error_code *error ) {
	open( fileName, mode, error );
}


file::~file() {
}

//==================================================================================================

static const char *make_mode_string( file::open_mode mode, error_code *error ) {
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
			*error = make_error_code( errc::invalid_argument );
			return nullptr;
	}
}


void file::open( const string &fileName, open_mode mode ) {
	error_code error;
	if ( !open( fileName, mode, &error ))
		throw error;
}

bool file::open( const string &fileName, open_mode mode, error_code *error ) {
	const char *mode_string = make_mode_string( mode, error );
	if ( mode_string != nullptr ) {
		FILE *file_ptr = fopen( fileName.c_str(), mode_string );
		if ( file_ptr != nullptr ) {
			// We don't bind the deleter to file::close to prevent exceptions from the destructor.
			file_ = shared_ptr< FILE >( file_ptr, fclose );
			fileName_ = fileName;
			return true;
		} else {
			*error = make_errno_error_code();
			return false;
		}
	} else {
		// error has already been set by make_mode_string
		return false;
	}
}

void file::close() {
	error_code error;
	if ( !close( &error ))
		throw error;
}

bool file::close( error_code *error ) {
	if ( file_ ) {
		// Close the file via the deleter because we don't necessary know whether to use fclose!

		auto deleter = get_deleter< int (*)( FILE * )>( file_ );
		if ( deleter != nullptr && ( *deleter )( file_.get() ) == 0 ) {
			return true;
		} else {
			*error = make_errno_error_code();
			return false;
		}
	} else
		return false;
}

//==================================================================================================

void file::set_buffer( void *buffer, size_t size, buffer_mode mode ) {
	setvbuf( file_.get(), static_cast< char * >( buffer ), static_cast< int >( mode ), size );
}

//==================================================================================================

void file::write( const void *buffer, size_t size ) {
	error_code error;
	if ( !write( buffer, size, &error ))
		throw error;
}

void file::read( void *buffer, size_t size ) {
	error_code error;
	if ( !read( buffer, size, &error ))
		throw error;
}


const size_t COUNT = 1;

bool file::write( const void *buffer, size_t size, error_code *error ) {
	size_t writeCount = fwrite( buffer, size, COUNT, file_.get() );
	if ( writeCount < COUNT ) {
		*error = make_errno_error_code();
		return false;
	} else
		return true;
}

bool file::read( void *buffer, size_t size, error_code *error ) {
	size_t readCount = fread( buffer, size, COUNT, file_.get() );
	if ( readCount < COUNT ) {
		*error = make_errno_error_code();
		return false;
	} else
		return true;
}

//==================================================================================================

void file::tell( offset_t *offset ) {
	error_code error;
	if ( !tell( offset, &error ))
		throw error;
}

bool file::tell( offset_t *offset, error_code *error ) {
	*offset = ftell( file_.get() );
	if ( *offset == -1 ) {
		*error = make_errno_error_code();
		return false;
	}
	else
		return true;
}


void file::seek( offset_t offset, origin origin ) {
	error_code error;
	if ( !seek( offset, &error, origin ))
		throw error;
}


bool file::seek( offset_t offset, error_code *error, origin origin ) {
	if ( fseek( file_.get(), offset, static_cast< int >( origin )) != 0 ) {
		*error = make_errno_error_code();
		return false;
	} else
		return true;
}

void file::rewind() {
	::rewind( file_.get() );
}

void file::get_position( fpos_t *position ) {
	error_code error;
	if ( !get_position( position, &error ))
		throw error;
}


bool file::get_position( fpos_t *position, error_code *error ) {
	if ( fgetpos( file_.get(), position ) != 0 ) {
		*error = make_errno_error_code();
		return false;
	}
	else
		return true;
}


void file::set_position( const fpos_t &position ) {
	error_code error;
	if ( !set_position( position, &error ))
		throw error;
}


bool file::set_position( const fpos_t &position, error_code *error ) {
	if ( fsetpos( file_.get(), &position ) != 0 ) {
		*error = make_errno_error_code();
		return false;
	} else
		return true;
}

void file::flush() {
	error_code error;
	if ( !flush( &error ))
		throw error;
}

bool file::flush( error_code *error ) {
	if ( fflush( file_.get() ) == EOF ) {
		*error = make_errno_error_code();
		return false;
	} else
		return true;
}

} } }
