// Copyright 2023 Peter Most, PERA Software Solutions GmbH
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

#include <pera_software/aidkit/stdlib/string_ref.hpp>

namespace pera_software::aidkit::stdlib {

using namespace std;

TEST(StringRefTest, ConstructorWithPointer)
{
	const char str[] = "1234";

	string_ref ref(str);

	ASSERT_EQ(ref.data(), str);
	ASSERT_EQ(ref.length(), 4);
	ASSERT_STREQ(ref.data(), str);
}

TEST(StringRefTest, ConstructorWithNullPointer)
{
	string_ref ref(nullptr);

	ASSERT_NE(ref.data(), nullptr);
	ASSERT_EQ(*ref.data(), 0);
	ASSERT_EQ(ref.length(), 0);
}

TEST(StringRefTest, ConstructorWithString)
{
	const string str("1234");

	string_ref ref(str);

	ASSERT_NE(ref.data(), nullptr);
	ASSERT_EQ(ref.length(), str.length());
	ASSERT_STREQ(ref.data(), str.c_str());
}

}
