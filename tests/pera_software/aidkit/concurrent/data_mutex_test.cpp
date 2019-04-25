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

#include "data_mutex_test.hpp"
#include <pera_software/aidkit/concurrent/data_mutex.hpp>
#include <QTest>
#include <vector>
#include <string>
#include <map>
#include <memory>

namespace pera_software::aidkit::concurrent {

using namespace std;

static DataMutexTest mutexTest;

//#########################################################################################################

// Explicit template instantiation to detect syntax errors:
using StringVectorDataMutex = class data_mutex< vector< string >>;

void DataMutexTest::testRegularLocking()
{
    StringVectorDataMutex names( 20u, "empty" );

    data_mutex_ptr names_ptr(&names);
    names_ptr->at(0) = "";
    (*names_ptr)[0] = "";
}

void DataMutexTest::testConstLocking()
{
    const StringVectorDataMutex names( 20u, "empty" );

    const_data_mutex_ptr names_ptr(&names);
    string first = names_ptr->at(0);
    first = (*names_ptr)[0];
}

}
