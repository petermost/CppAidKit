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

#include "new_test.hpp"
#include <pera_software/aidkit/cpp/new.hpp>
#include <memory>
#include <QTest>

namespace pera_software::aidkit::cpp {

using namespace std;

class InstanceCounter {
	public:
		InstanceCounter(int *counter)
			: counter_(counter) {
			++(*counter_);
		}

		~InstanceCounter() {
			--(*counter_);
		}
	private:
		int *const counter_;
};

static NewTest newTest;

static constexpr size_t MEMORY_SIZE = 100;
static_assert(MEMORY_SIZE >= sizeof(InstanceCounter), "MEMORY_SIZE isn't big enough!");

void NewTest::testPlacementDelete() {
	int counter = 0;
	{
		char sharedMemory[MEMORY_SIZE];
		char uniqueMemory[MEMORY_SIZE];

		shared_ptr<InstanceCounter> sharedObj(new(sharedMemory)InstanceCounter(&counter), placement_new_deleter());
		unique_ptr<InstanceCounter, placement_new_deleter> uniqueObj(new(uniqueMemory)InstanceCounter(&counter));

		QCOMPARE(2, counter);
	}
	QCOMPARE(0, counter);
}

void NewTest::testConstPlacementDelete() {
	int counter = 0;
	{
		char sharedMemory[MEMORY_SIZE];
		char uniqueMemory[MEMORY_SIZE];

		const shared_ptr<InstanceCounter> sharedObj(new(sharedMemory)InstanceCounter(&counter), placement_new_deleter());
		const unique_ptr<InstanceCounter, placement_new_deleter> uniqueObj(new(uniqueMemory)InstanceCounter(&counter));

		QCOMPARE(2, counter);
	}
	QCOMPARE(0, counter);
}

}
