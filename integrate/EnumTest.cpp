#include "stdafx.h"
#include "Testing/Assertions.hpp"
#include <UtilityCpp/Enum.hpp>

#pragma managed

using namespace std;
using namespace NUnit::Framework;

namespace RohdeSchwarz {

using namespace Testing;

//#########################################################################################################

// Enum for testing values start with 0:

class Color : public Enum< Color, int, wchar_t > {
	public:
		static const Color Red;
		static const Color Green;
		static const Color Blue;

	private:
		Color( const wchar_t *name )
			: Enum( name )
		{ }
};

const Color Color::Red( L"Red" );
const Color Color::Green( L"Green" );
const Color Color::Blue( L"Blue" );

[ TestFixture ]
public ref struct ColorEnumTest
{
	// These are just a compile tests so we don't mark them with [Test]:

	static void ColorFunction( Color /* color */ ) { }

	void CompileTestCallByValue()
	{
		ColorFunction( Color::Blue );
	}

	void CompileTestAssignment()
	{
		Color color = Color::Red;
		color = Color::Blue;
	}

	[ Test ]
	void TestValue()
	{
		Assert::AreEqual( 0, Color::Red.value() );
		Assert::AreEqual( 1, Color::Green.value() );
		Assert::AreEqual( 2, Color::Blue.value() );
	}

	[ Test ]
	void TestName()
	{
		AssertAreEqual( wstring( L"Red" ),   Color::Red.name() );
		AssertAreEqual( wstring( L"Green" ), Color::Green.name() );
		AssertAreEqual( wstring( L"Blue" ),  Color::Blue.name() );
	}

	[ Test ]
	void TestBeginEnd()
	{
		auto colors1 = make_enum_vector< Color >();
		vector< Color > colors2( Color::begin(), Color::end() );

		Assert::IsTrue( colors1 == colors2 );
	}

	[ Test ]
	void TestFindWithValue()
	{
		auto colorIterator = Color::find( 2 );
		Assert::IsTrue( colorIterator != Color::end() );
		Assert::IsTrue( *colorIterator == Color::Blue );
	}

	[ Test ]
	void TestFindWithName()
	{
		auto colorIterator = Color::find( L"Green" );
		Assert::IsTrue( colorIterator != Color::end() );
		Assert::IsTrue( *colorIterator == Color::Green );
	}

	[ Test ]
	void TestEquality()
	{
		Assert::IsTrue( Color::Red == Color::Red );
		Assert::IsTrue( Color::Green == Color::Green );
		Assert::IsTrue( Color::Blue == Color::Blue );
	}

	[ Test ]
	void TestLessThan()
	{
		Assert::IsTrue( Color::Red < Color::Green );
		Assert::IsTrue( Color::Green < Color::Blue );
	}
};

//#########################################################################################################

// Enum for testing explicit value assignment:

class Number : public Enum< Number > {
	public:
		static const Number One;
		static const Number Two;
		static const Number Three;

	private:
		Number( int value, const char *name )
			: Enum( value, name )
		{ }
};

const Number Number::One( 1, "One" );
const Number Number::Two( 2, "Two" );
const Number Number::Three( 3, "Three" );

[ TestFixture ]
public ref struct NumberEnumTest
{
	[ Test ]
	void TestValue()
	{
		Assert::AreEqual( 1, Number::One.value() );
		Assert::AreEqual( 2, Number::Two.value() );
		Assert::AreEqual( 3, Number::Three.value() );
	}
};

//#########################################################################################################

// Enum for testing explicit start value:

class Animal : public Enum< Animal > {
	public:
		static const Animal Cat;
		static const Animal Dog;

	private:
		Animal()
			: Enum()
		{ }

		Animal( int value )
			: Enum( value )
		{ }
};

const Animal Animal::Cat( 10 );
const Animal Animal::Dog;

[ TestFixture ]
public ref struct AnimalEnumTest
{
	[ Test ]
	void TestValue()
	{
		Assert::AreEqual( 10, Animal::Cat.value() );
		Assert::AreEqual( 11, Animal::Dog.value() );
	}
};

}
