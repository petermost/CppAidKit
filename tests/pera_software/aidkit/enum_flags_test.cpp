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

#include "enum_flags_test.hpp"
#include <pera_software/aidkit/enum_flags.hpp>
#include <QTest>

namespace pera_software { namespace aidkit {

using namespace std;

static EnumFlagsTest enumFlagsTest;

enum class Option : unsigned {
	A,
	B,
	C
};

// Explicit template instantion to detect compile errors early:

template class enum_flags< Option >;

static void evaluate( enum_flags< Option > ) {
}

//#########################################################################################################

void EnumFlagsTest::testFunctionCall() {
	evaluate({ Option::C, Option::A });
}

void EnumFlagsTest::testConstructor() {
	enum_flags< Option > options = { Option::A, Option::C };

	QCOMPARE( options.to_int(), 5u );

	// QVERIFY( alignment.to_int(), 10 );
}

void EnumFlagsTest::testOr() {
	enum_flags< Option > options = { Option::A };
	enum_flags< Option > result = options | Option::C;

	QCOMPARE( result.to_int(), 5u );
}

} }
