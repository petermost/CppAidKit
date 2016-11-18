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

#pragma once

#include <pera_software/aidkit/qt/test/Test.hpp>

namespace pera_software { namespace aidkit {

	class ColorEnumTest : public qt::Test {
			Q_OBJECT

		private Q_SLOTS:
			void testCallByValue();
			void testValue();
			void testValues();
			void testName();
			void testFindByValue();
			void testFindByName();
			void testEquality();
			void testLessThan();
			void testAssignment();
	};

	class NumberEnumTest : public qt::Test {
			Q_OBJECT

		private Q_SLOTS:
			void testValue();
			void testFindDuplicates();
	};

	class AnimalEnumTest : public qt::Test {
			Q_OBJECT

		private Q_SLOTS:
			void testValue();
			void testName();
	};

	class FruitEnumTest : public qt::Test {
			Q_OBJECT

		private Q_SLOTS:
			void testName();
	};

} }
