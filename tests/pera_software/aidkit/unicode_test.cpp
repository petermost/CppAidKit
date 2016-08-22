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

#include "unicode_test.hpp"
#include <pera_software/aidkit/unicode.hpp>
#include <QTest>

namespace pera_software { namespace aidkit {

using namespace std;

// ä = UTF-16(0x00E4) = UTF-8(0xC3 0xA4)
// ö = UTF-16(0x00F6) = UTF-8(0xC3 0xB6)
// ü = UTF-16(0x00FC) = UTF-8(0xC3 0xBC)
// Ä = UTF-16(0x00C4) = UTF-8(0xC3 0xC4)
// Ö = UTF-16(0x00D6) = UTF-8(0xC3 0x96)
// Ü = UTF-16(0x00DC) = UTF-8(0xC3 0x9C)
// ß = UTF-16(0x00DF) = UTF-8(0xC3 0x9F)

const wstring UTF16_LOWER_AE({ 0x00E4 });
const wstring UTF16_LOWER_OE({ 0x00F6 });
const wstring UTF16_LOWER_UE({ 0x00FC });
const wstring UTF16_UPPER_AE({ 0x00C4 });
const wstring UTF16_UPPER_OE({ 0x00D6 });
const wstring UTF16_UPPER_UE({ 0x00DC });
const wstring UTF16_SHARP_SS({ 0x00DF });

const u8string UTF8_LOWER_AE({ 0xC3, 0xA4 });
const u8string UTF8_LOWER_OE({ 0xC3, 0xB6 });
const u8string UTF8_LOWER_UE({ 0xC3, 0xBC });
const u8string UTF8_UPPER_AE({ 0xC3, 0x84 });
const u8string UTF8_UPPER_OE({ 0xC3, 0x96 });
const u8string UTF8_UPPER_UE({ 0xC3, 0x9C });
const u8string UTF8_SHARP_SS({ 0xC3, 0x9F });

const wstring WIDE_LOWER_AE({ 228 });
const wstring WIDE_LOWER_OE({ 246 });
const wstring WIDE_LOWER_UE({ 252 });
const wstring WIDE_UPPER_AE({ 196 });
const wstring WIDE_UPPER_OE({ 214 });
const wstring WIDE_UPPER_UE({ 220 });
const wstring WIDE_SHARP_SS({ 223 });

const string NARROW_LOWER_AE({ static_cast< char >( 228 )});
const string NARROW_LOWER_OE({ static_cast< char >( 246 )});
const string NARROW_LOWER_UE({ static_cast< char >( 252 )});
const string NARROW_UPPER_AE({ static_cast< char >( 196 )});
const string NARROW_UPPER_OE({ static_cast< char >( 214 )});
const string NARROW_UPPER_UE({ static_cast< char >( 220 )});
const string NARROW_SHARP_SS({ static_cast< char >( 223 )});

const wstring UTF16_UMLAUTE = UTF16_LOWER_AE + UTF16_LOWER_OE + UTF16_LOWER_UE +
	UTF16_UPPER_AE + UTF16_UPPER_OE + UTF16_UPPER_UE + UTF16_SHARP_SS;

const u8string UTF8_UMLAUTE = UTF8_LOWER_AE + UTF8_LOWER_OE + UTF8_LOWER_UE +
	UTF8_UPPER_AE + UTF8_UPPER_OE + UTF8_UPPER_UE + UTF8_SHARP_SS;

const wstring WIDE_UMLAUTE = WIDE_LOWER_AE + WIDE_LOWER_OE + WIDE_LOWER_UE +
	WIDE_UPPER_AE + WIDE_UPPER_OE + WIDE_UPPER_UE + WIDE_SHARP_SS;

const string NARROW_UMLAUTE = NARROW_LOWER_AE + NARROW_LOWER_OE + NARROW_LOWER_UE +
	NARROW_UPPER_AE + NARROW_UPPER_OE + NARROW_UPPER_UE + NARROW_SHARP_SS;


static UnicodeTest unicodeTest;

//=================================================================================================

void UnicodeTest::testNarrowStringToWideString() {
	string narrowString( "abcdef" );
	wstring wideString = string_to_wstring( narrowString );

	QCOMPARE( wideString, wstring( L"abcdef" ));
}

void UnicodeTest::testWideStringToNarrowString() {
	wstring wideString( L"12345" );
	string narrowString = wstring_to_string( wideString );

	QCOMPARE( narrowString, string( "12345" ));
}

//=================================================================================================

void UnicodeTest::testEmptyNarrowStringToWideString() {
	string narrowString( "" );
	wstring wideString = string_to_wstring( narrowString );

	QCOMPARE( wideString, wstring( L"" ));
}

void UnicodeTest::testEmptyWideStringToNarrowString() {
	wstring wideString( L"" );
	string narrowString = wstring_to_string( wideString );

	QCOMPARE( narrowString, string( "" ));
}

//=================================================================================================

void UnicodeTest::testUmlauteWideStringToU8String() {
	u8string utf8Umlaute = wstring_to_u8string( UTF16_UMLAUTE );

	QCOMPARE( UTF8_UMLAUTE, utf8Umlaute );
}

#ifdef U8STRING_TO_WSTRING_NOT_WORKING
void UnicodeTest::testUmlauteU8StringToWideString() {
	QSKIP( "u8string_to_wstring is not working with this glibc version!" );
}

#else

void UnicodeTest::testUmlauteU8StringToWideString() {
	wstring utf16Umlaute = u8string_to_wstring( UTF8_UMLAUTE );

	QCOMPARE( UTF16_UMLAUTE, utf16Umlaute );
}

#endif

//=================================================================================================

void UnicodeTest::testUmlauteNarrowStringToWideString() {
	wstring wideUmlaute = string_to_wstring( NARROW_UMLAUTE );

	QCOMPARE( WIDE_UMLAUTE, wideUmlaute );
}

void UnicodeTest::testUmlauteWideStringToNarrowString() {
	string narrowUmlaute = wstring_to_string( WIDE_UMLAUTE );

	QCOMPARE( NARROW_UMLAUTE, narrowUmlaute );
}

} }
