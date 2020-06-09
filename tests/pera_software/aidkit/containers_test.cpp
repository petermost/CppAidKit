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
#include <pera_software/aidkit/vectors.hpp>
#include <sstream>

namespace pera_software::aidkit {

using namespace std;


TEST(ContainersTest, testJoin)
{
	vector<int> ints = {1, 2, 3};

	string str = containers::join(ints, "[", ",", "]");

	ASSERT_EQ(str, "[1,2,3]");
}

TEST(ContainersTest, testStreamOperatorWithEmptyVector)
{
	vector<int> ints;
	ostringstream output;

	output << ints;

	ASSERT_EQ(output.str(), "");
}

TEST(ContainersTest, testStreamOperatorWithOneElement)
{
	vector<int> ints = {1};
	ostringstream output;

	output << ints;

	ASSERT_EQ(output.str(), "1");
}

TEST(ContainersTest, testStreamOperatorWithMultipleElements)
{
	vector<int> ints = {1, 2, 3};
	ostringstream output;

	output << ints;

	ASSERT_EQ(output.str(), "1, 2, 3");
}

}
