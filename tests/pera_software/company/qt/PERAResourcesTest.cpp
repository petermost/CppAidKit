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

#include "PERAResourcesTest.hpp"
#include <pera_software/aidkit/qt/gui/ResourcesTest.hpp>
#include <pera_software/company/qt/PERAResources.hpp>
#include <QTest>

namespace pera_software::company::qt {

using namespace std;

static PERAResourcesTest resourcesTest;

void PERAResourcesTest::testLoadIcons() {
	ASSERT_IMAGE(PERAResources::icon());
	ASSERT_IMAGE(PERAResources::logo());
}

}