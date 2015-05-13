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

#include "file_exception.hpp"
#include <cerrno>
#include <cstdarg>

// TODO: Derive file_exception from std::system_exception

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

//#########################################################################################################

file_not_found_exception::file_not_found_exception( const string &fileName )
	: file_exception( ENOENT ) {
	fileName_ = fileName;
}

const string &file_not_found_exception::fileName() const {
	return fileName_;
}




end_of_file_exception::end_of_file_exception()
	: file_exception( EOF, "EOF" ) {
}

} } }

