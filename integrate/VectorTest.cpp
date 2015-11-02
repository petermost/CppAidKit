#include "StdAfx.h"
#include <UtilityCppUnitTest/Testing/Assertions.hpp>
#include <UtilityCpp/Std/Vector.hpp>
#include <boost/format.hpp>

using namespace std;
using namespace boost;
using namespace NUnit::Framework;
using namespace Testing;

static bool is_two( int i )
{
	return i == 2;
}

public ref struct VectorTest
{
	void TestStreamOperatorWithEmptyVector()
	{
		vector< int > ints;

		auto result = ( wformat( L"%1%" ) % ints ).str();
		AssertAreEqual( L"", result );
	}

	void TestStreamOperatorWithOneElement()
	{
		vector< int > ints = { 1 };

		auto result = ( wformat( L"%1%" ) % ints ).str();
		AssertAreEqual( L"1", result );
	}

	void TestStreamOperatorWithMultipleElements()
	{
		vector< int > ints = { 1, 2, 3 };

		auto result = ( wformat( L"%1%" ) % ints ).str();
		AssertAreEqual( L"1, 2, 3", result );
	}

	void TestRemoveIf()
	{
		vector< int > ints = { 1, 2, 2, 2, 3 };
		
		vector_remove_if( &ints, is_two );

		AssertAreEqual( 2u, ints.size() );
		AssertAreEqual( 1, ints[ 0 ]);
		AssertAreEqual( 3, ints[ 1 ]);
	}
};

