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

AIDKIT_PRAGMA_GCC_WARNING_PUSH()

AIDKIT_PRAGMA_GCC_WARNING_DISABLE(unused-parameter)
AIDKIT_PRAGMA_GCC_WARNING_DISABLE(unused-function)
AIDKIT_PRAGMA_GCC_WARNING_DISABLE(unused-variable)
AIDKIT_PRAGMA_GCC_WARNING_DISABLE(shadow-uncaptured-local)

static void unusedFunction(int unusedParameter)
{
}

TEST(CompilerTest, testPragmaMacros)
{
	int unusedVariable;
	auto lambda = [](int unusedVariable){};
}

AIDKIT_PRAGMA_GCC_WARNING_POP()
