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

#include "strings_test.hpp"
#include <pera_software/aidkit/strings.hpp>
#include <QTest>

namespace pera_software::aidkit {

using namespace std;

// Explicitly instantiate the templates to detect compiler errors:

template const string trim_left( const string & );
template const string trim_right( const string & );
template const string trim_left( const string &, char c );
template const string trim_right( const string &, char c );
template const wstring trim_left( const wstring & );
template const wstring trim_right( const wstring & );
template const wstring trim_left( const wstring &, wchar_t c );
template const wstring trim_right( const wstring &, wchar_t c );

template bool try_stoi( const string &, long *, error_code * );
template bool try_stoi( const string &, long long *, error_code *  );
template bool try_stoi( const string &, unsigned long *, error_code *  );
template bool try_stoi( const string &, unsigned long long *, error_code *  );
template bool try_stoi( const wstring &, long *, error_code *  );
template bool try_stoi( const wstring &, long long *, error_code *  );
template bool try_stoi( const wstring &, unsigned long *, error_code *  );
template bool try_stoi( const wstring &, unsigned long long *, error_code *  );

static StringsTest stringsTest;

void StringsTest::testStringLiteral() {
	const char stringLiteral[] = "unimportend";

	QVERIFY( is_string_literal( stringLiteral ));
}

void StringsTest::testNonStringLiteral() {
	const char *nonStringLiteral = "unimportend";

	QVERIFY( !is_string_literal( nonStringLiteral ));
}

void StringsTest::testTrimLeftSpace() {
	string actual = trim_left( string( "\t\r\n   123   " ));
	string expected( "123   " );

	QCOMPARE( actual, expected );

}

void StringsTest::testTrimRightSpace() {
	string actual = trim_right( string( "   123\t\r\n  " ));
	string expected( "   123" );

	QCOMPARE( actual, expected );
}

void StringsTest::testTrimLeftChars() {
	string actual = trim_left( string( "...123   " ), '.' );
	string expected( "123   " );

	QCOMPARE( actual, expected );
}

void StringsTest::testTrimRightChars() {
	string actual = trim_right( string( "   123..." ), '.' );
	string expected( "   123" );

	QCOMPARE( actual, expected );
}

void StringsTest::testTrySToI() {
	string value( "123" );
	long integer;
	error_code errorCode;

	bool success = try_stoi( value, &integer, &errorCode );
	QVERIFY( success );
	QCOMPARE( integer, 123l );
}


}
