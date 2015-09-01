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

#include "static_array_test.hpp"
#include <pera_software/aidkit/container/static_array.hpp>
#include <QTest>

namespace pera_software { namespace aidkit { namespace container {

using namespace std;

static StaticArrayTest staticArrayTest;

template class static_array< int, 10 >;

// static static_array< int, 10 > s_array;

void StaticArrayTest::test() {
//	QCOMPARE( s_array.size(), 0u );
//	s_array = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

//	QCOMPARE( s_array.size(), 10u );

//	s_array.erase( s_array.begin() + 4 );
//	QCOMPARE( s_array.size(), 9u );
}

} } }
