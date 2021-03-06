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

#include "errno.hpp"

namespace pera_software::aidkit::io {

using namespace std;

error_code make_errno_error_code() {
	return make_errno_error_code( errno );
}

error_code make_errno_error_code( int errnoCode ) {
	return error_code( errnoCode, generic_category() );
}

system_error make_errno_system_error() {
	return system_error( make_errno_error_code() );
}

system_error make_errno_system_error( int errnoCode ) {
	return system_error( make_errno_error_code( errnoCode ));
}

}

