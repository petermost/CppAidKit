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

#include "ErrNoException.hpp"
#include <cstring>

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

ErrNoException ErrNoException::LastError()
{
	return ErrNoException( errno );
}

ErrNoException::ErrNoException( int errNo, const string &errorMessage )
{
	errNo_ = errNo;
	if ( !errorMessage.empty() )
		errorMessage_ = errorMessage;
	else
		errorMessage_ = strerror( errNo );
}

const char *ErrNoException::what() const noexcept
{
	return errorMessage_.c_str();
}

} } }
