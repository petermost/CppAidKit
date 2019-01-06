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

#include <cerrno>
#include <system_error>
#include <pera_software/aidkit/aidkit.hpp>

namespace pera_software::aidkit::io {

	// There is no error constant for no error so we define our own:

	const int ENONE = 0;

	// Helper functions to make an error_code from errno:

	AIDKIT_API std::error_code make_errno_error_code();
	AIDKIT_API std::error_code make_errno_error_code( int errnoCode );

	AIDKIT_API std::system_error make_errno_system_error();
	AIDKIT_API std::system_error make_errno_system_error( int errnoCode );

}
