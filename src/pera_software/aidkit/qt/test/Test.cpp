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

namespace pera_software { namespace aidkit { namespace qt {

QList< QObject * > Test::s_tests;

Test::Test() {
	s_tests.append( this );
}

Test::~Test() {
	s_tests.removeOne( this );
}

void Test::executeTests( const QStringList &arguments ) {
	for ( QObject *object : s_tests )
		QTest::qExec( object, arguments );
}

} } }
