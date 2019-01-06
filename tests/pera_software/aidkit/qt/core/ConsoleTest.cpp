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

#include "ConsoleTest.hpp"
#include <pera_software/aidkit/qt/core/Console.hpp>
#include <QString>

namespace pera_software::aidkit::qt {

// This is more of a compile test then runtime test, so we don't instantiate ConsoleTest.

void ConsoleTest::testOutStream() {
	QString text( "" );

	cout << text;
}

void ConsoleTest::testErrStream() {
	QString text( "" );

	cerr << text;
}

void ConsoleTest::testInStream() {
	QString text;

	cin >> text;
}

}
