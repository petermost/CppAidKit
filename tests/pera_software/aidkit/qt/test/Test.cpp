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

#include "Test.hpp"
#include <QTest>

namespace pera_software { namespace aidkit { namespace qt {

using namespace std;

//==================================================================================================

Test::Test() {

	// Append this test to the list of tests:

	tests().append( this );
}

//==================================================================================================

Test::~Test() {

	// Remove this test from the list of tests:

	tests().removeOne( this );
}

//==================================================================================================

// TODO: Return a list of the failed tests

int Test::executeTests( const QStringList &arguments ) {
	int failedTests = 0;

	for ( Test *test : tests() ) {
		int hasFailed = QTest::qExec( test, arguments );
		failedTests += ( hasFailed != 0 ) ? 1 : 0;
	}
	return failedTests;
}

//==================================================================================================

QVector< Test * > &Test::tests() {
	// Use a function level static container so we don't get a problem with the undefined
	// initialization order of file level statics:

	static QVector< Test * > s_tests;

	return s_tests;
}

} } }
