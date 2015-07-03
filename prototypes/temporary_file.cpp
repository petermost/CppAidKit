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

#include "temporary_file.hpp"

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

template < typename C, typename F >
	basic_string< C > make_name_impl( F tmpnam_function ) {
		C fileName[ L_tmpnam ];
		if ( tmpnam_function( fileName ) != nullptr )
			return fileName;
		else
			return basic_string< C >();
	}

string temporary_file::make_name() {
	return make_name_impl< char >( tmpnam );
}

#if defined( AIDKIT_MINGW )

	wstring temporary_file::make_wname() {
		return make_name_impl< wchar_t >( _wtmpnam );
	}

#endif

temporary_file::temporary_file()
	: file( shared_ptr< FILE >( tmpfile(), fclose )) {
}

} } }
