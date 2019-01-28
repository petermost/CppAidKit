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

#include "Test.hpp"
#include <QTest>
#include <exception>
#include <QCoreApplication>
#include <pera_software/aidkit/qt/core/Console.hpp>

namespace pera_software::aidkit::qt {

using namespace std;

//==================================================================================================

Test::Test() noexcept {

	// Append this test to the list of tests:

	tests().append( this );
}

//==================================================================================================

Test::~Test() {

	// Remove this test from the list of tests:

	tests().removeOne( this );
}

//==================================================================================================

int Test::main( int argc, char *argv[] ) noexcept {

#ifdef AIDKIT_GCC
	set_terminate( __gnu_cxx::__verbose_terminate_handler );
#endif
	QCoreApplication application( argc, argv );
	QStringList arguments = application.arguments();

	// if there aren't any parameters then we want the 'silent' mode:
	// http://doc.qt.io/qt-5/qtest-overview.html#qt-test-command-line-arguments

	if ( arguments.length() == 1 ) {
		arguments.append( "-silent" );
	}

	// Execute the tests and print which have failed:

	QVector< Test * > failedTests = executeTests( arguments );
	for ( Test *test : failedTests ) {
		cerr << "Test failed: '" << test->name() << "'!" << endl;
	}
	return failedTests.size();
}

//==================================================================================================

QString Test::name() const noexcept {
	const QMetaObject *meta = metaObject();
	return meta->className();
}

//==================================================================================================

QVector< Test * > Test::executeTests( const QStringList &arguments ) noexcept {
	QVector< Test * > failedTests;

	for ( Test *test : tests() ) {
		int hasFailed = QTest::qExec( test, arguments );
		if ( hasFailed )
			failedTests.append( test );
	}
	return failedTests;
}

//==================================================================================================

QVector< Test * > &Test::tests() noexcept {
	// Use a function level static container so we don't get a problem with the undefined
	// initialization order of file level statics:

	static QVector< Test * > s_tests;

	return s_tests;
}


}
