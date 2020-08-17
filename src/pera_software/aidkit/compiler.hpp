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

#include "platform.hpp"
#include "strings.hpp"

// Macros to handle warnings (push,pop,disable) in a more or less crossplatform way.
// Adapted from https://www.boost.org/doc/libs/release/boost/compute/detail/diagnostic.hpp

#define AIDKIT_PRAGMA(text) _Pragma(#text)

#if defined(AIDKIT_GCC)
	#define AIDKIT_GCC_DIAGNOSTIC(text)      AIDKIT_PRAGMA(GCC diagnostic text)
	#define AIDKIT_GCC_PUSH_WARNINGS()       AIDKIT_GCC_DIAGNOSTIC(push)
	#define AIDKIT_GCC_POP_WARNINGS()        AIDKIT_GCC_DIAGNOSTIC(pop)
	#define AIDKIT_GCC_DISABLE_WARNING(text) AIDKIT_GCC_DIAGNOSTIC(ignored AIDKIT_JOIN_STRINGIFY(-W, text))
	#define AIDKIT_GCC_ENABLE_WARNING(text)  AIDKIT_GCC_DIAGNOSTIC(warning AIDKIT_JOIN_STRINGIFY(-W, text))

	#define AIDKIT_MSVC_DISABLE_WARNING(number)
	#define AIDKIT_MSVC_ENABLE_WARNING(number)
#endif

// Clang is suppose to be compatible with GCC, but in case there are specific Clang warnings we
// define also a set of macros for Clang.
#if defined(AIDKIT_CLANG)
	#define AIDKIT_CLANG_DIAGNOSTIC(text)      AIDKIT_PRAGMA(clang diagnostic text)
	#define AIDKIT_CLANG_PUSH_WARNINGS()       AIDKIT_CLANG_DIAGNOSTIC(push)
	#define AIDKIT_CLANG_POP_WARNINGS()        AIDKIT_CLANG_DIAGNOSTIC(pop)
	#define AIDKIT_CLANG_DISABLE_WARNING(text) AIDKIT_CLANG_DIAGNOSTIC(ignored AIDKIT_JOIN_STRINGIFY(-W, text))
	#define AIDKIT_CLANG_ENABLE_WARNING(text)  AIDKIT_CLANG_DIAGNOSTIC(warning AIDKIT_JOIN_STRINGIFY(-W, text))
#endif

#if defined(AIDKIT_MSVC)
	#define AIDKIT_MSVC_DIAGNOSTIC(text)        AIDKIT_PRAGMA(warning(text))
	#define AIDKIT_MSVC_PUSH_WARNINGS()         AIDKIT_MSVC_DIAGNOSTIC(push)
	#define AIDKIT_MSVC_POP_WARNINGS()          AIDKIT_MSVC_DIAGNOSTIC(pop)
	#define AIDKIT_MSVC_DISABLE_WARNING(number) AIDKIT_MSVC_DIAGNOSTIC(disable: number)
	#define AIDKIT_MSVC_ENABLE_WARNING(number)  AIDKIT_MSVC_DIAGNOSTIC(default: number)

	#define AIDKIT_GCC_DISABLE_WARNING(text)
	#define AIDKIT_GCC_DISABLE_WARNING(text)
	#define AIDKIT_CLANG_DISABLE_WARNING(text)
	#define AIDKIT_CLANG_DISABLE_WARNING(text)
#endif
