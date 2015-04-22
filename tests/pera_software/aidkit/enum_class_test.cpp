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

#include <pera_software/aidkit/debug.hpp>
#include <pera_software/aidkit/enum_class.hpp>

namespace pera_software { namespace aidkit {

using namespace std;

//#########################################################################################################

// Enum for testing values start with 0:

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

struct ColorEnumTest {
	// These are just a compile tests so we don't mark them with [Test]:

	static void ColorFunction( Color /* color */ ) { }

	void CompileTestCallByValue() {
		ColorFunction( Color::Blue );
	}

	void CompileTestAssignment() {
		Color color = Color::Red;
		color = Color::Blue;
	}

	void TestValue() {
		AIDKIT_ASSERT( Color::Red.value() == 0 );
		AIDKIT_ASSERT( Color::Green.value() == 1 );
		AIDKIT_ASSERT( Color::Blue.value() == 2 );
	}

	void TestName() {
		AIDKIT_ASSERT( Color::Red.name() == L"Red" );
		AIDKIT_ASSERT( Color::Green.name() == L"Green" );
		AIDKIT_ASSERT( Color::Blue.name() == L"Blue" );
	}

	void TestBeginEnd() {
		auto colors1 = make_enum_vector< Color >();
		vector< Color > colors2( Color::begin(), Color::end() );

		AIDKIT_ASSERT( colors1 == colors2 );
	}

	void TestFindWithValue() {
		auto colorIterator = Color::find( 2 );
		AIDKIT_ASSERT( colorIterator != Color::end() );
		AIDKIT_ASSERT( *colorIterator == Color::Blue );
	}

	void TestFindWithName() {
		auto colorIterator = Color::find( L"Green" );
		AIDKIT_ASSERT( colorIterator != Color::end() );
		AIDKIT_ASSERT( *colorIterator == Color::Green );
	}

	void TestEquality() {
		AIDKIT_ASSERT( Color::Red == Color::Red );
		AIDKIT_ASSERT( Color::Green == Color::Green );
		AIDKIT_ASSERT( Color::Blue == Color::Blue );
	}

	void TestLessThan() {
		AIDKIT_ASSERT( Color::Red < Color::Green );
		AIDKIT_ASSERT( Color::Green < Color::Blue );
	}
};

//#########################################################################################################

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

struct NumberEnumTest {
	void TestValue() {
		AIDKIT_ASSERT( Number::One.value() == 1 );
		AIDKIT_ASSERT( Number::Two.value() == 2 );
		AIDKIT_ASSERT( Number::Three.value() == 3);
	}
};

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

struct AnimalEnumTest {
	void TestValue() {
		AIDKIT_ASSERT( Animal::Cat.value() == 10 );
		AIDKIT_ASSERT( Animal::Dog.value() == 11 );
	}
};

void runEnumTests() {

	ColorEnumTest colorEnumTest;
	colorEnumTest.TestValue();
	colorEnumTest.TestName();
	colorEnumTest.TestBeginEnd();
	colorEnumTest.TestFindWithValue();
	colorEnumTest.TestFindWithName();
	colorEnumTest.TestEquality();
	colorEnumTest.TestLessThan();

	NumberEnumTest numberEnumTest;
	numberEnumTest.TestValue();

	AnimalEnumTest animalEnumTest;
	animalEnumTest.TestValue();
}

} }
