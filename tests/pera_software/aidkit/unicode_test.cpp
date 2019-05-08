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
#include <pera_software/aidkit/io/errno.hpp>
#include <system_error>
#include <sstream>
#include <QTest>

// TODO: Find better unicode examples.

namespace pera_software::aidkit {

using namespace io;
using namespace std;

//     UTF-16 | UTF-8     | ISO-8859-1 (Latin-1)
// ---------------------------------------------
// ä | 0x00E4 | 0xC3 0xA4 | 0xE4
// ö | 0x00F6 | 0xC3 0xB6 | 0xF6
// ü | 0x00FC | 0xC3 0xBC | 0xFC
// Ä | 0x00C4 | 0xC3 0xC4 | 0xC4
// Ö | 0x00D6 | 0xC3 0x96 | 0xD6
// Ü | 0x00DC | 0xC3 0x9C | 0xDC
// ß | 0x00DF | 0xC3 0x9F | 0xDF
// € | 0x0080 | 0xC2 0x80 | <not available>
// =============================================

const wstring UTF16_LOWER_AE( L"\x00E4" );
const wstring UTF16_LOWER_OE( L"\x00F6" );
const wstring UTF16_LOWER_UE( L"\x00FC" );
const wstring UTF16_UPPER_AE( L"\x00C4" );
const wstring UTF16_UPPER_OE( L"\x00D6" );
const wstring UTF16_UPPER_UE( L"\x00DC" );
const wstring UTF16_SHARP_SS( L"\x00DF" );
const wstring UTF16_EURO(     L"\x0080" );

const wstring UTF16_CHARACTERS =
    UTF16_LOWER_AE + UTF16_LOWER_OE + UTF16_LOWER_UE +
    UTF16_UPPER_AE + UTF16_UPPER_OE + UTF16_UPPER_UE +
    UTF16_SHARP_SS + UTF16_EURO;

const string UTF8_LOWER_AE( "\xC3\xA4" );
const string UTF8_LOWER_OE( "\xC3\xB6" );
const string UTF8_LOWER_UE( "\xC3\xBC" );
const string UTF8_UPPER_AE( "\xC3\x84" );
const string UTF8_UPPER_OE( "\xC3\x96" );
const string UTF8_UPPER_UE( "\xC3\x9C" );
const string UTF8_SHARP_SS( "\xC3\x9F" );
const string UTF8_EURO(     "\xC2\x80" );

const string UTF8_CHARACTERS =
    UTF8_LOWER_AE + UTF8_LOWER_OE + UTF8_LOWER_UE +
    UTF8_UPPER_AE + UTF8_UPPER_OE + UTF8_UPPER_UE +
    UTF8_SHARP_SS + UTF8_EURO;

const wstring ISO_8859_1_WIDE_LOWER_AE( L"\x00E4" );
const wstring ISO_8859_1_WIDE_LOWER_OE( L"\x00F6" );
const wstring ISO_8859_1_WIDE_LOWER_UE( L"\x00FC" );
const wstring ISO_8859_1_WIDE_UPPER_AE( L"\x00C4" );
const wstring ISO_8859_1_WIDE_UPPER_OE( L"\x00D6" );
const wstring ISO_8859_1_WIDE_UPPER_UE( L"\x00DC" );
const wstring ISO_8859_1_WIDE_SHARP_SS( L"\x00DF" );

const wstring ISO_8859_1_WIDE_CHARACTERS =
    ISO_8859_1_WIDE_LOWER_AE + ISO_8859_1_WIDE_LOWER_OE + ISO_8859_1_WIDE_LOWER_UE +
    ISO_8859_1_WIDE_UPPER_AE + ISO_8859_1_WIDE_UPPER_OE + ISO_8859_1_WIDE_UPPER_UE +
    ISO_8859_1_WIDE_SHARP_SS;

const string ISO_8859_1_NARROW_LOWER_AE( "\xE4" );
const string ISO_8859_1_NARROW_LOWER_OE( "\xF6" );
const string ISO_8859_1_NARROW_LOWER_UE( "\xFC" );
const string ISO_8859_1_NARROW_UPPER_AE( "\xC4" );
const string ISO_8859_1_NARROW_UPPER_OE( "\xD6" );
const string ISO_8859_1_NARROW_UPPER_UE( "\xDC" );
const string ISO_8859_1_NARROW_SHARP_SS( "\xDF" );

const string ISO_8859_1_NARROW_CHARACTERS =
    ISO_8859_1_NARROW_LOWER_AE + ISO_8859_1_NARROW_LOWER_OE + ISO_8859_1_NARROW_LOWER_UE +
    ISO_8859_1_NARROW_UPPER_AE + ISO_8859_1_NARROW_UPPER_OE + ISO_8859_1_NARROW_UPPER_UE +
    ISO_8859_1_NARROW_SHARP_SS;

static UnicodeTest unicodeTest;

//=================================================================================================

void UnicodeTest::testFromMbs() {
    string narrowString( "abcdef" );
    wstring wideString = from_mbs( narrowString );

    QCOMPARE( wideString, wstring( L"abcdef" ));
}

void UnicodeTest::testToMbs() {
    wstring wideString( L"12345" );
    string narrowString = to_mbs( wideString );

    QCOMPARE( narrowString, string( "12345" ));
}

//=================================================================================================

void UnicodeTest::testEmptyFromMbs() {
    string narrowString( "" );
    wstring wideString = from_mbs( narrowString );

    QCOMPARE( wideString, wstring( L"" ));
}

void UnicodeTest::testEmptyToMbs() {
    wstring wideString( L"" );
    string narrowString = to_mbs( wideString );

    QCOMPARE( narrowString, string( "" ));
}

//=================================================================================================

void UnicodeTest::testToUtf8() {
    string utf8Umlaute = to_utf8( UTF16_CHARACTERS );

    QCOMPARE( UTF8_CHARACTERS, utf8Umlaute );
}

void UnicodeTest::testFromUtf8() {
    wstring utf16Umlaute = from_utf8( UTF8_CHARACTERS );

    QCOMPARE( UTF16_CHARACTERS, utf16Umlaute );
}

//=================================================================================================

// Q: Why do these tests throw std::range_error under Linux?
// A: The encoding of the umlaute is in ISO-8859-1 (Latin-1)!


void UnicodeTest::testIso_8859_1_FromMbs() {
    try {
        wstring wideUmlaute = from_mbs( ISO_8859_1_NARROW_CHARACTERS );
        QFAIL( "Must throw errc::illegal_byte_sequence!");
    } catch ( const system_error &systemError ) {
        QCOMPARE( systemError.code(), make_error_code( errc::illegal_byte_sequence ));
    }
}

void UnicodeTest::testIso_8859_1_ToMbs() {
    try {
        string narrowUmlaute = to_mbs( ISO_8859_1_WIDE_CHARACTERS );
        QFAIL( "Must throw errc::illegal_byte_sequence!");
    } catch ( const system_error &systemError ) {
        QCOMPARE( systemError.code(), make_error_code( errc::illegal_byte_sequence ));
	}
}

//=================================================================================================

void UnicodeTest::testStdStreamOperator()
{
	ostringstream output;

	output << UTF16_CHARACTERS;

	QVERIFY( output.str() == UTF8_CHARACTERS );
}

}
