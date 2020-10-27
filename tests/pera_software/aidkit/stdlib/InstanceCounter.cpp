// Copyright 2020 Peter Most, PERA Software Solutions GmbH
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

namespace pera_software::aidkit::stdlib {

void InstanceCounter::operator delete(void *pointer, std::size_t size)
{
	ASSERT_EQ(size, sizeof(InstanceCounter));
	InstanceCounter *instanceCounter = static_cast<InstanceCounter *>(pointer);
	--(*instanceCounter->counter_);
}

InstanceCounter::InstanceCounter(int *counter)
	: counter_(counter)
{
	++(*counter_);
}

InstanceCounter::~InstanceCounter()
{
	--(*counter_);
}

}
