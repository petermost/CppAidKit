// Copyright 2016 Peter Most, PERA Software Solutions GmbH
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

#include "stdlib_test.hpp"
#include <pera_software/aidkit/cpp/stdlib.hpp>
#include <QTest>
#include <vector>
#include <iterator>

namespace pera_software { namespace aidkit { namespace cpp {

using namespace std;

static StdLibTest stdLibTest;

void StdLibTest::testCountOf() {
	int ints[] = { 1, 2, 2, 2, 3 };

	QCOMPARE( countof( ints ), size_t( 5 ));
}

void StdLibTest::testSize() {
	vector< int > ints = { 1, 2, 3 };

	QCOMPARE( std::size( ints ), size_t( 3 ));
}

} } }
