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

#include "ResourcesTest.hpp"
#include <pera_software/aidkit/qt/Resources.hpp>
#include <QTest>

namespace pera_software::aidkit::qt {

using namespace std;

static ResourceTest resourceTest;

#define ASSERT_ICON(icon) \
	QVERIFY(!icon.isNull())

void ResourceTest::testMissingIcon() {
	QIcon missingIcon("");
	QVERIFY(missingIcon.isNull());
}

void ResourceTest::testLoadIcons() {
	ASSERT_ICON(Resources::quitIcon());
	ASSERT_ICON(Resources::debugIcon());
	ASSERT_ICON(Resources::warningIcon());
	ASSERT_ICON(Resources::informationIcon());
	ASSERT_ICON(Resources::errorIcon());
	ASSERT_ICON(Resources::clockIcon());
}

}
