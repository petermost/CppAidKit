#include "stdafx.h"
#include "../Testing/Assertions.hpp"
#include <UtilityCpp/IO/Endian.hpp>


#pragma managed


using namespace Testing;
using namespace NUnit::Framework;

template < typename T >
	void Assert_hton_ntoh( T expectedHostValue, T expectedNetValue )
	{
		T actualNetValue = hton( expectedHostValue );
		AssertAreEqual( expectedNetValue, actualNetValue, L"hton() doesn't work correctly!" );

		T actualHostValue = ntoh( expectedNetValue );
		AssertAreEqual( expectedHostValue, actualHostValue, L"ntoh() doesn't work correctly!" );
	}

[TestFixture]
public ref struct EndianTest
{
	[Test]
	void Test_hton_ntoh_8()
	{
		Assert_hton_ntoh< uint8_t >( 0x01, 0x01 );
	}

	[Test]
	void Test_hton_ntoh_16()
	{
		Assert_hton_ntoh< uint16_t >( 0x0123, 0x2301 );
	}

	[Test]
	void Test_hton_ntoh_32()
	{
		Assert_hton_ntoh< uint32_t >( 0x01234567, 0x67452301 );
	}

	[Test]
	void Test_hton_ntoh_64()
	{
		Assert_hton_ntoh< uint64_t >( 0x0123456789ABCDEF, 0xEFCDAB8967452301 );
	}

	[Test]
	void Test_hton_ntoh_compilation()
	{
		// These should trigger (if enabled) an error because the parameter is not an integer.
		// hton( 1.0 );
		// ntoh( 1.0 );

		// short / unsigned short
		
		hton(( short )1 );
		ntoh(( short )1 );
		hton(( unsigned short )1 );
		ntoh(( unsigned short )1 );

		// int / unsigned int

		hton( 1 );
		ntoh( 1 );
		hton( 1u );
		ntoh( 1u );

		// long / unsigned long

		hton( 1l );
		ntoh( 1l );
		hton( 1ul );
		ntoh( 1ul );

		// long long / unsigned long long

		hton( 1ll );
		ntoh( 1ll );
		hton( 1ull );
		ntoh( 1ull );
	}
};

