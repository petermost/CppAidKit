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

namespace pera_software::aidkit::concurrent {

using namespace std;

static DataMutexTest mutexTest;

//#########################################################################################################

// Explicit template instantiation to detect syntax errors:
template class data_mutex< vector< string >>;

void DataMutexTest::testLock() {

	// Must initially not be locked yet:

	data_mutex< vector< string >> names( 20u, "empty" );
	QVERIFY( !names.is_locked() );

	// Lock the data:

	{
		auto names_ptr = names.lock();
		QVERIFY( static_cast< bool >( names_ptr ));
		QVERIFY( names.is_locked() );

		// The names_ptr destructor will unlock the mutex.
	}
	// Must now be unlocked again:

	QVERIFY( !names.is_locked() );
}

void DataMutexTest::testReset() {
	data_mutex< vector< string >> names( 20u, "empty" );

	// Lock the data:

	auto p = names.lock();
	QVERIFY( names.is_locked() );

	// Unlock manually:

	p.reset();
	QVERIFY( !names.is_locked() );
}


void DataMutexTest::testResetWithUnknownPointer() {
	data_mutex< vector< string >> names;

	// Lock the data:

	auto p = names.lock();
	QVERIFY( names.is_locked() );

	// Unlock manually but with an unknown pointer:

	vector< string > someData;
	p.reset( &someData );
	QVERIFY( !names.is_locked() );

	p.reset();
	QCOMPARE( names.lock_count(), 0 );
}


}
