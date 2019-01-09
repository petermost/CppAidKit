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

#include "formatter_test.hpp"
#include <pera_software/aidkit/boost/formatter.hpp>
#include <QTest>

namespace pera_software { namespace aidkit { namespace boost {

using namespace std;

static FormatterTest formatterTest;

void FormatterTest::testBadFormatString() {
	formatter( "%q" ) % "1.";
}

void FormatterTest::testTooFewArguments() {
	formatter( "%s %s %s" ) % "1." % "2." % "3.";
}

void FormatterTest::testTooManyArguments() {
	formatter( "%s" ) % "1." % "2." % "3.";
}

} } }
