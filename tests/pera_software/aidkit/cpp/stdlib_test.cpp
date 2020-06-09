// Copyright 2016 Peter Most, PERA Software Solutions GmbH
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
#include <iterator>
#include <pera_software/aidkit/cpp/stdlib.hpp>
#include <vector>

namespace pera_software::aidkit::cpp {

using namespace std;

TEST(StdLibTest, testCountOf)
{
	int ints[] = {1, 2, 2, 2, 3};

	ASSERT_EQ(countof(ints), size_t(5));
}

TEST(StdLibTest, testSize)
{
	vector<int> ints = {1, 2, 3};

	ASSERT_EQ(std::size(ints), size_t(3));
}

TEST(StdLibTest, testIntCastTooLarge)
{
	const long l = std::numeric_limits<int>::max() + 1l;
	ASSERT_THROW(int_cast<int>(l), out_of_range);
}

TEST(StdLibTest, testIntCastTooSmall)
{
	const long l = std::numeric_limits<int>::min() - 1l;
	ASSERT_THROW(int_cast<int>(l), out_of_range);
}

}
