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
#include "system_error.hpp"
#include <cstdio>

namespace pera_software::aidkit::io {

using namespace std;

//==================================================================================================

bool remove_file( const char fileName[] ) {
	return call_and_throw_if_error([ & ]( error_code *errorCode ) {
		return remove_file( fileName, errorCode );
	});
}

//==================================================================================================

bool remove_file( const char fileName[], error_code *errorCode ) noexcept {
	auto result = ::remove( fileName );
	bool success = ( result == 0 );

	*errorCode = get_file_error_code( success );
	return success;
}

//==================================================================================================

void remove_file_if_exists( const char fileName[] ) {
	error_code errorCode;

	// We want to be notified when the remove fails, so we throw an exception:

	if ( !remove_file( fileName, &errorCode ) && errorCode != errc::no_such_file_or_directory )
		throw system_error( errorCode );
}

//==================================================================================================

file_deleter::file_deleter( const string &fileName ) {
	fileName_ = fileName;
}

//==================================================================================================

file_deleter::~file_deleter() noexcept( false ) {
	remove_file_if_exists( fileName_.c_str() );
}


}

/*
Under gcc/glibc the usage of tmpnam() results in the linker! warning:
"the use of `tmpnam' is dangerous, better use `mkstemp'"
I've tried other versions like tmpnam_r(), mktemp() etc. but they all resulted in a similar warning.

string make_temporary_filename() {
	char temporaryName[ L_tmpnam ];

	if ( tmpnam( temporaryName ) != nullptr )
		return temporaryName;
	else
		return string();
}
*/
