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

#include <pera_software/aidkit/io/temporary_file.hpp>

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

void runFileTests() {
	char c = 'c';
	wchar_t wc = L'c';
	string s = "";
	wstring ws = L"";
	char buffer[ 10 ];

	temporary_file file;
	error_code error;

	if ( error == errc::invalid_argument )
		;

	file.put( c );
	file.put( c, &error );
	file.put( wc );
	file.put( wc, &error );

	file.get( &c );
	file.get( &c, &error );
	file.get( &wc );
	file.get( &wc, &error );

	file.put( "" );
	file.put( "", &error );
	file.put( L"" );
	file.put( L"", &error );
	file.put( s );
	file.put( s, &error );
	file.put( ws );
	file.put( wc, &error );

	file.print( "%s, %d", "", 0 );
	file.print( &error, "%s, %d", "", 0 );
	file.print( L"%s, %d", "", 0 );
	file.print( &error, L"%s, %d", "", 0 );

	file.write( buffer, sizeof( buffer ));
	file.write( buffer, sizeof( buffer ), &error );
	file.read( buffer, sizeof( buffer ));
	file.read( buffer, sizeof( buffer ), &error );
}

} } }
