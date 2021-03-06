// Copyright 2019 Peter Most, PERA Software Solutions GmbH
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

#include "InstanceCounter.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <pera_software/aidkit/stdlib/new.hpp>

namespace pera_software::aidkit::stdlib {

using namespace std;

static constexpr size_t MEMORY_SIZE = 100;
static_assert(MEMORY_SIZE >= sizeof(InstanceCounter), "MEMORY_SIZE isn't big enough!");

TEST(NewTest, testPlacementDelete)
{
	int counter = 0;
	{
		char sharedMemory[MEMORY_SIZE];
		char uniqueMemory[MEMORY_SIZE];

		shared_ptr<InstanceCounter> sharedObj(new (sharedMemory) InstanceCounter(&counter), placement_new_deleter());
		unique_ptr<InstanceCounter, placement_new_deleter> uniqueObj(new (uniqueMemory) InstanceCounter(&counter));

		ASSERT_EQ(2, counter);
	}
	ASSERT_EQ(0, counter);
}

TEST(NewTest, testConstPlacementDelete)
{
	int counter = 0;
	{
		char sharedMemory[MEMORY_SIZE];
		char uniqueMemory[MEMORY_SIZE];

		const shared_ptr<InstanceCounter> sharedObj(new (sharedMemory) InstanceCounter(&counter), placement_new_deleter());
		const unique_ptr<InstanceCounter, placement_new_deleter> uniqueObj(new (uniqueMemory) InstanceCounter(&counter));

		ASSERT_EQ(2, counter);
	}
	ASSERT_EQ(0, counter);
}

}
