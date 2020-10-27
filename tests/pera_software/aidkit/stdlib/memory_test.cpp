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
#include <pera_software/aidkit/stdlib/memory.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <string>

namespace pera_software::aidkit::stdlib {

using namespace std;

static constexpr size_t MAX_SIZE(static_cast<size_t>(-1));

TEST(MemoryTest, testMakeUniqueMemoryPtr)
{
	ASSERT_THROW(make_unique_memory_ptr(MAX_SIZE), bad_alloc);
}

TEST(MemoryTest, testMakeSharedMemoryPtr)
{
	ASSERT_THROW(make_shared_memory_ptr(MAX_SIZE), bad_alloc);
}

TEST(MemoryTest, testSharedPtrNullDeleter)
{
	int instances = 0;
	InstanceCounter counter(&instances);
	ASSERT_EQ(instances, 1);
	{
		shared_ptr<InstanceCounter> sharedPtr(&counter, null_deleter());
	}
	ASSERT_EQ(instances, 1);
}

TEST(MemoryTest, testUniquePtrNullDeleter)
{
	int instances = 0;
	InstanceCounter counter(&instances);
	ASSERT_EQ(instances, 1);
	{
		unique_ptr<InstanceCounter, null_deleter> uniquePtr(&counter);
	}
	ASSERT_EQ(instances, 1);
}

}
