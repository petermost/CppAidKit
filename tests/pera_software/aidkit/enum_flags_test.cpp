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

namespace pera_software::aidkit {

using namespace std;

static EnumFlagsTest enumFlagsTest;

enum class open_mode : unsigned {
	read,
	write,
	append,
	extended,
	binary
};

// Explicit template instantion to detect compile errors early:

template class enum_flags< open_mode >;

using open_modes = enum_flags< open_mode >;

static void open_file( const open_modes modes  ) {
	if (( modes & open_mode::append ) == open_mode::append ) {
	}
	if ( modes & open_mode::binary ) {
	}
}

//#########################################################################################################

void EnumFlagsTest::testFunctionCall() {
	open_file( open_modes( open_mode::append ) | open_mode::extended );
}

void EnumFlagsTest::testConstructor() {
	open_modes modes( open_mode::append );

	QCOMPARE( modes.to_int(), 4u );
}

void EnumFlagsTest::testDefaultConstructor() {
	open_modes modes;

	QCOMPARE( modes.to_int(), 0u );
}

void EnumFlagsTest::testOr1() {
	open_modes modes = open_modes( open_mode::read ) | open_mode::extended;

	QCOMPARE( modes.to_int(), 9u );
}

void EnumFlagsTest::testOr2() {
	open_modes modes = open_modes( open_mode::read ) | open_mode::write | open_mode::extended;
	open_modes mask = open_modes( open_mode::read ) | open_mode::write;

	open_modes result = modes & mask;

	QVERIFY( result == mask );
}

void EnumFlagsTest::testAnd() {
	open_modes modes = open_modes( open_mode::read ) | open_mode::extended | open_mode::binary;
	open_modes result = modes & open_mode::binary;

	QVERIFY( result == open_mode::binary );
}

}
