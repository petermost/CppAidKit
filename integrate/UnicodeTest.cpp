#include "StdAfx.h"
#include "../Testing/Assertions.hpp"
#include <UtilityCpp/Strings/Unicode.hpp>
#include <locale>
#include <codecvt>

#pragma managed

namespace RohdeSchwarz { namespace Strings {

using namespace std;
using namespace NUnit::Framework;
using namespace Testing;

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
const wstring UTF16_SS({ 0x00DF });

const u8string UTF8_LOWER_AE({ 0xC3, 0xA4 });
const u8string UTF8_LOWER_OE({ 0xC3, 0xB6 });
const u8string UTF8_LOWER_UE({ 0xC3, 0xBC });
const u8string UTF8_UPPER_AE({ 0xC3, 0x84 });
const u8string UTF8_UPPER_OE({ 0xC3, 0x96 });
const u8string UTF8_UPPER_UE({ 0xC3, 0x9C });
const u8string UTF8_SS({ 0xC3, 0x9F });

const wstring WIDE_LOWER_AE( L"ä" );
const wstring WIDE_LOWER_OE( L"ö" );
const wstring WIDE_LOWER_UE( L"ü" );
const wstring WIDE_UPPER_AE( L"Ä" );
const wstring WIDE_UPPER_OE( L"Ö" );
const wstring WIDE_UPPER_UE( L"Ü" );
const wstring WIDE_SS( L"ß" );

const string NARROW_LOWER_AE( "ä" );
const string NARROW_LOWER_OE( "ö" );
const string NARROW_LOWER_UE( "ü" );
const string NARROW_UPPER_AE( "Ä" );
const string NARROW_UPPER_OE( "Ö" );
const string NARROW_UPPER_UE( "Ü" );
const string NARROW_SS( "ß" );

const wstring UTF16_UMLAUTE = UTF16_LOWER_AE + UTF16_LOWER_OE + UTF16_LOWER_UE + 
	UTF16_UPPER_AE + UTF16_UPPER_OE + UTF16_UPPER_UE + UTF16_SS;

const u8string UTF8_UMLAUTE = UTF8_LOWER_AE + UTF8_LOWER_OE + UTF8_LOWER_UE + 
	UTF8_UPPER_AE + UTF8_UPPER_OE + UTF8_UPPER_UE + UTF8_SS;

const wstring WIDE_UMLAUTE = WIDE_LOWER_AE + WIDE_LOWER_OE + WIDE_LOWER_UE + 
	WIDE_UPPER_AE + WIDE_UPPER_OE + WIDE_UPPER_UE + WIDE_SS;

const string NARROW_UMLAUTE = NARROW_LOWER_AE + NARROW_LOWER_OE + NARROW_LOWER_UE + 
	NARROW_UPPER_AE + NARROW_UPPER_OE + NARROW_UPPER_UE + NARROW_SS;

[TestFixture]
public ref struct UnicodeTest
{
	[Test]
	void TestNarrowStringToWideString()
	{
		string narrowString( "abcdef" );
		wstring wideString = string_to_wstring( narrowString );

		AssertAreEqual( L"abcdef", wideString );
	}

	[Test]
	void TestWideStringToNarrowString()
	{
		wstring wideString( L"12345" );
		string narrowString = wstring_to_string( wideString );

		AssertAreEqual( "12345", narrowString );
	}

	[Test]
	void TestEmptyNarrowStringToWideString()
	{
		string narrowString( "" );
		wstring wideString = string_to_wstring( narrowString );

		AssertAreEqual( L"", wideString );
	}

	[Test]
	void TestEmptyWideStringToNarrowString()
	{
		wstring wideString( L"" );
		string narrowString = wstring_to_string( wideString );

		AssertAreEqual( "", narrowString );
	}
	
	[Test]
	void TestUmlauteWideStringToU8String()
	{
		u8string utf8Umlaute = wstring_to_u8string( UTF16_UMLAUTE );
		AssertAreEqual( utf8Umlaute, UTF8_UMLAUTE );
	}

	[Test]
	void TestUmlauteU8StringToWideString()
	{
		wstring utf16Umlaute = u8string_to_wstring( UTF8_UMLAUTE );
		AssertAreEqual( utf16Umlaute, UTF16_UMLAUTE );
	}

	[Test]
	void TestUmlauteNarrowStringToWideString()
	{
		wstring wideUmlaute = string_to_wstring( NARROW_UMLAUTE );
		AssertAreEqual( wideUmlaute, WIDE_UMLAUTE );
	}

	[Test]
	void TestUmlauteWideStringToNarrowString()
	{
		string narrowUmlaute = wstring_to_string( WIDE_UMLAUTE );
		AssertAreEqual( narrowUmlaute, NARROW_UMLAUTE );
	}
};

} }
