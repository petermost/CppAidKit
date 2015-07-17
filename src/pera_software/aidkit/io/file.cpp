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

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

static error_code get_error_code( bool success ) noexcept {
	if ( success )
		return error_code();
	else {
		if ( errno != ENONE )
			return make_errno_error_code( errno );
		else
			return make_error_code( file_error::unspecific );
	}
}

//==================================================================================================

string make_temporary_filename() {
	char temporaryName[ L_tmpnam ];

	if ( tmpnam( temporaryName ) != nullptr )
		return temporaryName;
	else
		return string();
}

//==================================================================================================

bool remove_file( const char fileName[] ) {
	return call_and_throw_if_error([ & ]( error_code *errorCode ) {
		return remove_file( fileName, errorCode );
	});
}

//==================================================================================================

bool remove_file( const char fileName[], error_code *errorCode ) {
	auto result = ::remove( fileName );
	bool success = ( result == 0 );

	*errorCode = get_error_code( success );
	return success;
}

} } }
