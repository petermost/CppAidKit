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

namespace pera_software { namespace aidkit { namespace concurrent {

using namespace std;

static DataMutexTest mutexTest;

//#########################################################################################################

// Explicit template instantiation to detect syntax errors:
template class data_mutex< vector< string >>;

void DataMutexTest::testLock() {

	data_mutex< vector< string >> names( 20, "empty" );
	auto p1 = names.lock();
	auto p2 = names.try_lock();
	QVERIFY( static_cast< bool >( p1 ));
	QVERIFY( !static_cast< bool >( p2 ));
}

} } }
