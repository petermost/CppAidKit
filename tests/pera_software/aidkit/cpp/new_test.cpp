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
#include <QTest>

namespace pera_software::aidkit::cpp {

using namespace std;

struct UserObject {
    static int constructorDesctructorCounter;

    char unusedData[10];

    UserObject() {
        ++constructorDesctructorCounter;
    }
    ~UserObject() {
        --constructorDesctructorCounter;
    }
};

int UserObject::constructorDesctructorCounter = 0;

static NewTest newTest;

static constexpr size_t MAX_MEMORY = 100;
static_assert(MAX_MEMORY >= sizeof(UserObject), "MAX_MEMORY isn't big enough!");

void NewTest::testPlacementDelete() {
    QCOMPARE(0, UserObject::constructorDesctructorCounter);
    {
        char memory[MAX_MEMORY];
        unique_ptr<UserObject, placement_delete> obj(new(memory)UserObject);
        QCOMPARE(1, UserObject::constructorDesctructorCounter);
    }
    QCOMPARE(0, UserObject::constructorDesctructorCounter);
}

void NewTest::testConstPlacementDelete() {
    QCOMPARE(0, UserObject::constructorDesctructorCounter);
    {
        char memory[MAX_MEMORY];
        const unique_ptr<UserObject, placement_delete> obj(new(memory)UserObject);
        QCOMPARE(1, UserObject::constructorDesctructorCounter);
    }
    QCOMPARE(0, UserObject::constructorDesctructorCounter);
}

}
