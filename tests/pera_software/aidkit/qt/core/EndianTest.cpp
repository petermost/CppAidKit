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

#include "EndianTest.hpp"
#include <pera_software/aidkit/qt/core/Endian.hpp>
#include <QTest>

namespace pera_software { namespace aidkit { namespace qt {

static EndianTest endianTest;

template < typename T >
	void assert_hton_ntoh( T expectedHostValue, T expectedNetValue ) {
		T actualNetValue = hton( expectedHostValue );
		QCOMPARE( actualNetValue, expectedNetValue );

		T actualHostValue = ntoh( expectedNetValue );
		QCOMPARE( actualHostValue, expectedHostValue );
	}

void EndianTest::test_hton_ntoh_8() {
	assert_hton_ntoh< uint8_t >( 0x01, 0x01 );
}

void EndianTest::test_hton_ntoh_16() {
	assert_hton_ntoh< uint16_t >( 0x0123, 0x2301 );
}

void EndianTest::test_hton_ntoh_32() {
	assert_hton_ntoh< uint32_t >( 0x01234567, 0x67452301 );
}

void EndianTest::test_hton_ntoh_64() {
	assert_hton_ntoh< uint64_t >( 0x0123456789ABCDEF, 0xEFCDAB8967452301 );
}

void EndianTest::testCompilation() {
	// These should trigger (if enabled) an error because the parameter is not an integer.
	// hton( 1.0 );
	// ntoh( 1.0 );

	// short / unsigned short

	hton( short( 1 ));
	ntoh( short( 1 ));
	hton( ushort( 1 ));
	ntoh( ushort( 1 ));

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

} } }
