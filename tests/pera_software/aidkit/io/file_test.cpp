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

#include <pera_software/aidkit/io/basic_file.hpp>
#include "file_test.hpp"
#include <QTest>

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

// Explicit template instantiations to catch compiler errors early:

template class basic_file< char, file_locked_category >;
template class basic_file< wchar_t, file_locked_category >;

//template bool basic_file< char, file_locked_category >::print< int, int >( error_code *, const char *, int, int  );
//template bool basic_file< char, file_locked_category >::is_eof() const;

// Convenience typedefs:

typedef basic_file< char > file;
typedef basic_file< wchar_t > wfile;

//template < typename File, typename Char >
//	void testOpen() {
//		error_code errorCode;
//		Char fileName[] = { 0 };
//		Char openMode[] = { 0 };

//		File file;
//		file.open( fileName, openMode, &errorCode );
//	}

//template < typename File, typename Char >
//	void testPutChar() {
//		error_code errorCode;
//		Char c = Char();

//		File file;
//		file.put( c, &errorCode );
//	}

//template < typename File >
//	void testWrite() {
//		error_code errorCode;
//		File file;
//		file.write( nullptr, 0, 0, &errorCode );
//	}

//template < typename Char >
//	void testPrint() {
//		error_code errorCode;
//		Char format[] = { 0 };

//		basic_file< Char, file_locked_category > file;
//		file.print( &errorCode, format );
//		file.put( format[ 0 ], &errorCode );
//	}

//void FileTest::test() {

////	testOpen< locked_file, char >();
////	testOpen< locked_wfile, wchar_t >();
////	testOpen< unlocked_file, char >();
////	testOpen< unlocked_wfile, wchar_t >();

////	testPutChar< locked_file, char >();
////	testPutChar< locked_wfile, wchar_t >();
////	testPutChar< unlocked_file, char >();
////	testPutChar< unlocked_wfile, wchar_t >();

////	testWrite< locked_file >();
////	testWrite< locked_wfile >();
////	testWrite< unlocked_file >();
////	testWrite< unlocked_wfile >();

//	testPrint< char >();
//	testPrint< wchar_t >();
//}

void FileTest::testOpenFailed() {
	file file;
	error_code errorCode;

	QVERIFY( !file.open( "", "", &errorCode ));
	QVERIFY( static_cast< bool >( errorCode ));
	QVERIFY( !file.close( &errorCode ));
}

void FileTest::testOpenSucceeded() {
	file file;
	error_code errorCode;

	char temporaryName[ L_tmpnam ];
	tmpnam( temporaryName );

	char c;
	QVERIFY( file.open( temporaryName, "w+", &errorCode ));
	c = file.get( &errorCode );
	QVERIFY( errorCode == file_error::eof );
}

static FileTest fileTest;

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
