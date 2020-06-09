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
#include <pera_software/aidkit/enum_flags.hpp>

namespace pera_software::aidkit {

using namespace std;

enum class open_mode : unsigned {
	read,
	write,
	append,
	extended,
	binary
};

// Explicit template instantion to detect compile errors early:

template class enum_flags<open_mode>;

using open_modes = enum_flags<open_mode>;

static void open_file(const open_modes modes)
{
	if ((modes & open_mode::append) == open_mode::append) {
	}
	if (modes & open_mode::binary) {
	}
}

//#########################################################################################################

TEST(EnumFlagsTest, testFunctionCall)
{
	open_file(open_modes(open_mode::append) | open_mode::extended);
}

TEST(EnumFlagsTest, testConstructor)
{
	open_modes modes(open_mode::append);

	ASSERT_EQ(modes.to_int(), 4u);
}

TEST(EnumFlagsTest, testDefaultConstructor)
{
	open_modes modes;

	ASSERT_EQ(modes.to_int(), 0u);
}

TEST(EnumFlagsTest, testOr1)
{
	open_modes modes = open_modes(open_mode::read) | open_mode::extended;

	ASSERT_EQ(modes.to_int(), 9u);
}

TEST(EnumFlagsTest, testOr2)
{
	open_modes modes = open_modes(open_mode::read) | open_mode::write | open_mode::extended;
	open_modes mask = open_modes(open_mode::read) | open_mode::write;

	open_modes result = modes & mask;

	ASSERT_EQ(result, mask);
}

TEST(EnumFlagsTest, testAnd)
{
	open_modes modes = open_modes(open_mode::read) | open_mode::extended | open_mode::binary;
	open_modes result = modes & open_mode::binary;

	ASSERT_EQ(result, open_mode::binary);
}

}
