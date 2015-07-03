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


file::file( shared_ptr< FILE > file , error_code *errorCode ) {
	if ( file )
		file_ = file;
	else {
		error_code ctorErrorCode = make_error_code( errc::invalid_argument );
		if ( errorCode != nullptr )
			*errorCode = ctorErrorCode;
		else
			throw system_error( ctorErrorCode );
	}
}

file::file( const string &fileName, open_mode mode, error_code *errorCode ) {
	error_code openErrorCode;
	if ( !open( fileName, mode, &openErrorCode )) {
		if ( errorCode != nullptr )
			*errorCode = openErrorCode;
		else
			throw system_error( openErrorCode );
	}
}


file::~file() {
}

//==================================================================================================

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
			return nullptr;
	}
}


void file::open( const string &fileName, open_mode mode ) {
	error_code errorCode;
	if ( !open( fileName, mode, &errorCode ))
		throw system_error( errorCode );
}

bool file::open( const string &fileName, open_mode mode, error_code *errorCode ) {
	const char *mode_string = make_mode_string( mode );
	if ( mode_string == nullptr ) {
		*errorCode = make_error_code( errc::invalid_argument );
		return false;
	}

	FILE *file_ptr = fopen( fileName.c_str(), mode_string );
	if ( file_ptr == nullptr ) {
		*errorCode = make_errno_error_code();
		return false;
	}

	// We don't bind the deleter to file::close to prevent exceptions from the destructor.
	file_ = shared_ptr< FILE >( file_ptr, fclose );
	fileName_ = fileName;

	return true;
}

void file::close() {
	error_code errorCode;
	if ( !close( &errorCode ))
		throw system_error( errorCode );
}

bool file::close( error_code *errorCode ) {
	if ( !is_file_open( file_.get(), errorCode ))
		return false;

	// Close the file via the deleter because we don't necessary know whether to use fclose!

	auto deleter = get_deleter< int (*)( FILE * )>( file_ );
	if ( deleter != nullptr && ( *deleter )( file_.get() ) == 0 ) {
		return true;
	} else {
		*errorCode = make_errno_error_code();
		return false;
	}
}

//==================================================================================================

void file::set_buffer( void *buffer, size_t size, buffer_mode mode ) {
	setvbuf( file_.get(), static_cast< char * >( buffer ), static_cast< int >( mode ), size );
}

//==================================================================================================

void file::tell( offset_t *offset ) {
	error_code errorCode;
	if ( !tell( offset, &errorCode ))
		throw system_error( errorCode );
}

bool file::tell( offset_t *offset, error_code *errorCode ) {
	*offset = ftell( file_.get() );
	if ( *offset == -1 ) {
		*errorCode = make_errno_error_code();
		return false;
	}
	else
		return true;
}


void file::seek( offset_t offset, origin origin ) {
	error_code errorCode;
	if ( !seek( offset, &errorCode, origin ))
		throw system_error( errorCode );
}


bool file::seek( offset_t offset, error_code *errorCode, origin origin ) {
	if ( fseek( file_.get(), offset, static_cast< int >( origin )) != 0 ) {
		*errorCode = make_errno_error_code();
		return false;
	} else
		return true;
}

void file::rewind() {
	::rewind( file_.get() );
}

void file::get_position( fpos_t *position ) {
	error_code errorCode;
	if ( !get_position( position, &errorCode ))
		throw system_error( errorCode );
}


bool file::get_position( fpos_t *position, error_code *errorCode ) {
	if ( fgetpos( file_.get(), position ) != 0 ) {
		*errorCode = make_errno_error_code();
		return false;
	}
	else
		return true;
}


void file::set_position( const fpos_t &position ) {
	error_code errorCode;
	if ( !set_position( position, &errorCode ))
		throw system_error( errorCode );
}


bool file::set_position( const fpos_t &position, error_code *errorCode ) {
	if ( fsetpos( file_.get(), &position ) != 0 ) {
		*errorCode = make_errno_error_code();
		return false;
	} else
		return true;
}

void file::flush() {
	error_code errorCode;
	if ( !flush( &errorCode ))
		throw system_error( errorCode );
}

bool file::flush( error_code *errorCode ) {
	if ( fflush( file_.get() ) == EOF ) {
		*errorCode = make_errno_error_code();
		return false;
	} else
		return true;
}

} } }
