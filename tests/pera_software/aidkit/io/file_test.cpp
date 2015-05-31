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

#include <pera_software/aidkit/io/file.hpp>
#include "file_test.hpp"
#include <QTest>

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

//template class basic_file< char, file_locked_category >;
//template class basic_file< wchar_t, file_locked_category >;

//template class basic_file< char, file_unlocked_category >;
//template class basic_file< wchar_t, file_unlocked_category >;

void FileTest::testOpen() {
//	error_code error;
//	basic_file< wchar_t, file_locked_category > wfile;

//	ufile.open( "", "", &error );
//	file.open( "", "", &error );

//	file.put( 'c', &error );
//	file.put( "s", &error );

//	file.close( &error );

//	wfile.open( L"", L"", &error );
//	wfile.close( &error );

}

// static FileTest fileTest;

//void runFileTests() {
//	char c = 'c';
//	wchar_t wc = L'c';
//	string s = "";
//	wstring ws = L"";
//	char buffer[ 10 ];

//	temporary_file file;

//	error_code errorCode;

//	if ( errorCode == errc::invalid_argument )
//		;

//	if ( errorCode == file_error::not_open )
//		;

//	file.put( c );
//	file.put( c, &errorCode );
//	file.put( wc );
//	file.put( wc, &errorCode );

//	file.get( &c );
//	file.get( &c, &errorCode );
//	file.get( &wc );
//	file.get( &wc, &errorCode );

//	file.put( "" );
//	file.put( "", &errorCode );
//	file.put( L"" );
//	file.put( L"", &errorCode );
//	file.put( s );
//	file.put( s, &errorCode );
//	file.put( ws );
//	file.put( wc, &errorCode );

//	file.print( "%s, %d", "", 0 );
//	file.print( &errorCode, "%s, %d", "", 0 );
//	file.print( L"%s, %d", "", 0 );
//	file.print( &errorCode, L"%s, %d", "", 0 );

//	file.write( buffer, sizeof( buffer ));
//	file.write( buffer, sizeof( buffer ), &errorCode );
//	file.read( buffer, sizeof( buffer ));
//	file.read( buffer, sizeof( buffer ), &errorCode );
//}


} } }
