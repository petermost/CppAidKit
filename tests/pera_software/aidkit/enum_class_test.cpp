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

using namespace std;

static ColorEnumTest colorEnumTest;
static NumberEnumTest numberEnumTest;
static AnimalEnumTest animalEnumTest;
static FruitEnumTest fruitEnumTest;

//#########################################################################################################

// Enum for testing default value assignment:

class Color : public enum_class< Color, 4, int, wstring > {
	public:
		static const Color Red;
		static const Color Green;
		static const Color Blue;

	private:
		Color( const wstring &name )
			: enum_class( name ) {
		}
};

const Color Color::Red( L"Red" );
const Color Color::Green( L"Green" );
const Color Color::Blue( L"Blue" );

static void colorFunction( Color ) {
}

void ColorEnumTest::testCallByValue() {
	colorFunction( Color::Blue );
}

void ColorEnumTest::testValue() {
	QCOMPARE( Color::Red.value(), 0 );
	QCOMPARE( Color::Green.value(), 1 );
	QCOMPARE( Color::Blue.value(), 2 );
}

void ColorEnumTest::testValues() {
	vector< Color > colors = Color::values();
	QCOMPARE( colors.size(), static_cast< size_t >( 3 ));
}

void ColorEnumTest::testName() {
	QVERIFY( Color::Red.name() == L"Red" );
	QVERIFY( Color::Green.name() == L"Green" );
	QVERIFY( Color::Blue.name() == L"Blue" );
}

void ColorEnumTest::testFindByValue() {
	vector< Color > result = Color::find( 2 );
	QCOMPARE( result.size(), static_cast< size_t >( 1 ));
	QVERIFY( result[ 0 ] == Color::Blue );
}

void ColorEnumTest::testFindByName() {
	vector< Color > result = Color::find( L"Green" );
	QCOMPARE( result.size(), static_cast< size_t >( 1 ));
	QVERIFY( result[ 0 ] == Color::Green );
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

void ColorEnumTest::testAssignment() {
	Color color = Color::Red;
	QVERIFY( color == Color::Red );

	color = Color::Blue;
	QVERIFY( color == Color::Blue );
}

//##################################################################################################

// Enum for testing explicit value assignment and duplicated enums:

class Number : public enum_class< Number, 4 > {
	public:
		static const Number Ten;
		static const Number Twenty;
		static const Number Thirty;
		static const Number TwentyToo;
	private:
		Number( int value, const string &name )
			: enum_class( value, name ) {
		}
};

const Number Number::Ten(       10, "Ten" );
const Number Number::Twenty(    20, "Twenty" );
const Number Number::Thirty(    30, "Thirty" );
const Number Number::TwentyToo( 20, "TwentyToo" );

void NumberEnumTest::testValue() {
	QCOMPARE( Number::Ten.value(),    10 );
	QCOMPARE( Number::Twenty.value(), 20 );
	QCOMPARE( Number::Thirty.value(), 30 );
	QCOMPARE( Number::TwentyToo.value(), 20 );
}

void NumberEnumTest::testFindDuplicates() {
	vector< Number > numbers = Number::find( 20 );
	QCOMPARE( numbers.size(), static_cast< size_t >( 2 ));
	QVERIFY( numbers[ 0 ] == Number::Twenty );
	QVERIFY( numbers[ 1 ] == Number::TwentyToo );
}

//#########################################################################################################

// Enum for testing explicit start value:

class Animal : public enum_class< Animal, 2 > {
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

void AnimalEnumTest::testName() {
	QVERIFY( Animal::Cat.name() == "" );
	QVERIFY( Animal::Dog.name() == "" );
}

//#########################################################################################################

// Enum for testing with QString:

class Fruit : public enum_class< Fruit, 3, int, QString > {
	public:
		static const Fruit Apple;
		static const Fruit Orange;
		static const Fruit Lemon;

	private:
		Fruit( const QString &name )
			: enum_class( name ) {
		}
};

const Fruit Fruit::Apple( "Apple");
const Fruit Fruit::Orange( "Orange");
const Fruit Fruit::Lemon( "Lemon" );

void FruitEnumTest::testName() {
	QString expectedName = "Orange";

	QCOMPARE( Fruit::Orange.name(), expectedName );
}

} }
