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

#include "enum_class_test.hpp"
#include <pera_software/aidkit/enum_class.hpp>
#include <QTest>

namespace pera_software { namespace aidkit {

//#########################################################################################################

// Enum for testing default value assignment:

class Color : public enum_class< Color, int, wchar_t > {
	public:
		static const Color Red;
		static const Color Green;
		static const Color Blue;

	private:
		Color( const wchar_t *name )
			: enum_class( name ) {
		}
};

const Color Color::Red( L"Red" );
const Color Color::Green( L"Green" );
const Color Color::Blue( L"Blue" );

static void colorFunction( Color ) {
}

static void compileTestCallByValue() {
	colorFunction( Color::Blue );
}

void compileTestAssignment() {
	Color color = Color::Red;
	color = Color::Blue;
}

void ColorEnumTest::testValue() {
	QCOMPARE( Color::Red.value(), 0 );
	QCOMPARE( Color::Green.value(), 1 );
	QCOMPARE( Color::Blue.value(), 2 );
}

void ColorEnumTest::testName() {
	QVERIFY( Color::Red.name() == L"Red" );
	QVERIFY( Color::Green.name() == L"Green" );
	QVERIFY( Color::Blue.name() == L"Blue" );
}

void ColorEnumTest::testFindByValue() {
	auto colorIterator = Color::find( 2 );
	QVERIFY( colorIterator != Color::end() );
	QVERIFY( *colorIterator == Color::Blue );
}

void ColorEnumTest::testFindByName() {
	auto colorIterator = Color::find( L"Green" );
	QVERIFY( colorIterator != Color::end() );
	QVERIFY( *colorIterator == Color::Green );
}

void ColorEnumTest::testEquality() {
	QVERIFY( Color::Red == Color::Red );
	QVERIFY( Color::Green == Color::Green );
	QVERIFY( Color::Blue == Color::Blue );
}

void ColorEnumTest::testLessThan() {
	QVERIFY( Color::Red < Color::Green );
	QVERIFY( Color::Green < Color::Blue );
}

//##################################################################################################

// Enum for testing explicit value assignment:

class Number : public enum_class< Number > {
	public:
		static const Number One;
		static const Number Two;
		static const Number Three;

	private:
		Number( int value, const char *name )
			: enum_class( value, name ) {
		}
};

const Number Number::One( 1, "One" );
const Number Number::Two( 2, "Two" );
const Number Number::Three( 3, "Three" );

void NumberEnumTest::testValue() {
	QCOMPARE( Number::One.value(),   1 );
	QCOMPARE( Number::Two.value(),   2 );
	QCOMPARE( Number::Three.value(), 3 );
}

//#########################################################################################################

// Enum for testing explicit start value:

class Animal : public enum_class< Animal > {
	public:
		static const Animal Cat;
		static const Animal Dog;

	private:
		Animal()
			: enum_class() {
		}

		Animal( int value )
			: enum_class( value ) {
		}
};

const Animal Animal::Cat( 10 );
const Animal Animal::Dog;

void AnimalEnumTest::testValue() {
	QCOMPARE( Animal::Cat.value(), 10 );
	QCOMPARE( Animal::Dog.value(), 11 );
}

static ColorEnumTest colorEnumTest;
static NumberEnumTest numberEnumTest;
static AnimalEnumTest animalEnumTest;

} }
