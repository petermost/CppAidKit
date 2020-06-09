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

TEST(VectorsTest, testRemove)
{
	vector<int> ints = {1, 2, 2, 2, 3};

	// It is enough to test remove() because it calls remove_if():

	vectors::remove(&ints, 2);

	ASSERT_EQ(ints.size(), 2);
	ASSERT_EQ(ints.at(0), 1);
	ASSERT_EQ(ints.at(1), 3);
}

TEST(VectorsTest, testPopFront)
{
	vector<int> ints = {1, 2, 3};

	vectors::pop_front(&ints);

	ASSERT_EQ(ints.size(), 2);
	ASSERT_EQ(ints.at(0), 2);
	ASSERT_EQ(ints.at(1), 3);
}

}
