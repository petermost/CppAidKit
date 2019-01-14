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

#include "vectors_test.hpp"
#include <pera_software/aidkit/vectors.hpp>
#include <QTest>
#include <sstream>

namespace pera_software::aidkit {

using namespace std;

static VectorsTest vectorsTest;

void VectorsTest::testRemove() {
	vector< int > ints = { 1, 2, 2, 2, 3 };

	// It is enough to test remove() because it calls remove_if():

	vectors::remove( &ints, 2 );

	QVERIFY( ints.size() == 2 );
	QVERIFY( ints.at( 0 ) == 1 );
	QVERIFY( ints.at( 1 ) == 3 );
}

void VectorsTest::testPopFront() {
	vector< int > ints = { 1, 2, 3 };

	vectors::pop_front( &ints );

	QVERIFY( ints.size() == 2 );
	QVERIFY( ints.at( 0 ) == 2 );
	QVERIFY( ints.at( 1 ) == 3 );
}

void VectorsTest::testJoin() {
	vector< int > ints = { 1, 2, 3 };

	string str = vectors::join( ints, "[", ",", "]" );

	QVERIFY( str == "[1,2,3]" );
}

void VectorsTest::testStreamOperatorWithEmptyVector() {
	vector< int > ints;
	stringstream output;

	output << ints;

	QVERIFY( output.str() == "" );
}

void VectorsTest::testStreamOperatorWithOneElement() {
	vector< int > ints = { 1 };
	stringstream output;

	output << ints;

	QVERIFY( output.str() == "1" );
}

void VectorsTest::testStreamOperatorWithMultipleElements() {
	vector< int > ints = { 1, 2, 3 };
	stringstream output;

	output << ints;

	QVERIFY( output.str() == "1, 2, 3" );
}

}


