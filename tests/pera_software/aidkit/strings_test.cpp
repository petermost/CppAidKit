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

#include <gtest/gtest.h>
#include <pera_software/aidkit/strings.hpp>

namespace pera_software::aidkit {

using namespace std;

// Explicitly instantiate the templates to detect compiler errors:

template bool try_stoi(const string &, int *, error_code *);
template bool try_stoi(const string &, long *, error_code *);
template bool try_stoi(const string &, long long *, error_code *);
template bool try_stoi(const string &, unsigned long *, error_code *);
template bool try_stoi(const string &, unsigned long long *, error_code *);

TEST(StringsTest, testStringLiteral)
{
	const char stringLiteral[] = "unimportend";

	ASSERT_TRUE(is_string_literal(stringLiteral));
}

TEST(StringsTest, testNonStringLiteral)
{
	const char *nonStringLiteral = "unimportend";

	ASSERT_FALSE(is_string_literal(nonStringLiteral));
}

TEST(StringsTest, testTrimLeftSpace)
{
	string actual = trim_left(string("\t\r\n   123   "));
	string expected("123   ");

	ASSERT_EQ(actual, expected);
}

TEST(StringsTest, testTrimRightSpace)
{
	string actual = trim_right(string("   123\t\r\n  "));
	string expected("   123");

	ASSERT_EQ(actual, expected);
}

TEST(StringsTest, testTrimLeftChars)
{
	string actual = trim_left(string("...123   "), '.');
	string expected("123   ");

	ASSERT_EQ(actual, expected);
}

TEST(StringsTest, testTrimRightChars)
{
	string actual = trim_right(string("   123..."), '.');
	string expected("   123");

	ASSERT_EQ(actual, expected);
}

TEST(StringsTest, testTrySToI)
{
	string value("123");
	long integer;
	error_code errorCode;

	bool success = try_stoi(value, &integer, &errorCode);
	ASSERT_TRUE(success);
	ASSERT_EQ(integer, 123l);
}

}
