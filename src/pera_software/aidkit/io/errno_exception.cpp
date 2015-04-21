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

#include "errno_exception.hpp"
#include <cstring>

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

errno_exception errno_exception::last_error() {
	return errno_exception( errno );
}


errno_exception::errno_exception( int errNo, const string &errorMessage ) {
	errNo_ = errNo;
	if ( !errorMessage.empty() )
		errorMessage_ = errorMessage;
	else
		errorMessage_ = strerror( errNo );
}


const char *errno_exception::what() const noexcept {
	return errorMessage_.c_str();
}

} } }
