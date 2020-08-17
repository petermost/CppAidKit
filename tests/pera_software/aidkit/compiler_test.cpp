// Copyright 2020 Peter Most, PERA Software Solutions GmbH
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

#include <gtest/gtest.h>
#include <pera_software/aidkit/compiler.hpp>

AIDKIT_GCC_PUSH_WARNINGS()

AIDKIT_GCC_DISABLE_WARNING(unused-parameter)
AIDKIT_GCC_DISABLE_WARNING(unused-function)
AIDKIT_GCC_DISABLE_WARNING(unused-variable)
AIDKIT_GCC_DISABLE_WARNING(shadow-uncaptured-local)

static void unusedFunction(int unusedParameter)
{
}

TEST(CompilerTest, testPragmaMacros)
{
	int unusedVariable;
	auto lambda = [](int unusedVariable){};
}

AIDKIT_GCC_POP_WARNINGS()
