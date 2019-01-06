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

#include "file_error.hpp"
#include "errno.hpp"

namespace pera_software::aidkit::io {

using namespace std;

const file_error_category &file_error_category::instance() {
	static file_error_category s_instance;

	return s_instance;
}


const char *file_error_category::name() const noexcept {
	return "file";
}

string file_error_category::message( int error ) const {

	// The messages in boost.asio (error.ipp) start with an uppercase letter so we do the same:

	switch ( static_cast< file_error >( error )) {
		case file_error::unspecific:
			return "Unspecific file error";

		case file_error::eof:
			return "End of file";

		default:
			return "Unknown file error";
	}
}

error_code make_error_code( file_error error ) {
	return error_code( static_cast< int >( error ), file_error_category::instance() );
}

error_condition make_error_condition( file_error error ) {
	return error_condition( static_cast< int >( error ), file_error_category::instance() );
}

error_code get_file_error_code( bool success ) noexcept {
	if ( success )
		return error_code();
	else {
		if ( errno != ENONE )
			return make_errno_error_code( errno );
		else
			return make_error_code( file_error::unspecific );
	}
}

}
