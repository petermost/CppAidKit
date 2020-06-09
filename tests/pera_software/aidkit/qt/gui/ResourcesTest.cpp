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
#include <gtest/gtest.h>
#include <pera_software/aidkit/qt/gui/Resources.hpp>
#include <QIcon>

namespace pera_software::aidkit::qt {

using namespace std;

TEST(ResourcesTest, testMissingIcon)
{
	QIcon missingIcon = loadIcon(QStringLiteral(":/missing.png"));
	ASSERT_TRUE(missingIcon.isNull());
}

TEST(ResourcesTest, testLoadIcons)
{
	ASSERT_IMAGE(Resources::quitIcon());
	ASSERT_IMAGE(Resources::debugIcon());
	ASSERT_IMAGE(Resources::warningIcon());
	ASSERT_IMAGE(Resources::informationIcon());
	ASSERT_IMAGE(Resources::errorIcon());
	ASSERT_IMAGE(Resources::clockIcon());
	ASSERT_IMAGE(Resources::settingsIcon());
}

}
