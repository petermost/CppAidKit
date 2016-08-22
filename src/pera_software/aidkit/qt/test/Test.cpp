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
#include <algorithm>

namespace pera_software { namespace aidkit { namespace qt {

using namespace std;

size_t Test::s_testsCount;
array< Test *, Test::SIZE > Test::s_tests;

//==================================================================================================

Test::Test() {

	// Append the test to the list of tests:

	s_tests[ s_testsCount++ ] = this;
}

//==================================================================================================

Test::~Test() {

	// We can't really remove anything from an std::array, so we move the destructed test to the end
	// of the tests:

	auto endIterator = remove( s_tests.begin(), s_tests.end(), this );

	// Adjust the size so the 'removed' test won't be accessed anymore:

	s_testsCount = endIterator - s_tests.begin();
}

//==================================================================================================

int Test::executeTests( const QStringList &arguments ) {
	int summaryResult = 0;

	for ( std::size_t i = 0; i < s_testsCount; ++i ) {
		int result = QTest::qExec( s_tests[ i ], arguments );
		summaryResult = summaryResult && result;
	}
	return summaryResult;
}

} } }
