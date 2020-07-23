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
	// Clang is suppose to be compatible with GCC so we don't define extra macros for it!
	#define AIDKIT_PRAGMA_GCC_DIAGNOSTIC(text)      AIDKIT_PRAGMA(GCC diagnostic text)
	#define AIDKIT_PRAGMA_WARNING_PUSH()            AIDKIT_PRAGMA_GCC_DIAGNOSTIC(push)
	#define AIDKIT_PRAGMA_WARNING_POP()             AIDKIT_PRAGMA_GCC_DIAGNOSTIC(pop)
	#define AIDKIT_PRAGMA_GCC_WARNING_DISABLE(text) AIDKIT_PRAGMA_GCC_DIAGNOSTIC(ignored AIDKIT_JOIN_STRINGIFY(-W, text))
	#define AIDKIT_PRAGMA_GCC_WARNING_ENABLE(text)  AIDKIT_PRAGMA_GCC_DIAGNOSTIC(warning AIDKIT_JOIN_STRINGIFY(-W, text))

	#define AIDKIT_PRAGMA_MSVC_WARNING_DISABLE(number)
	#define AIDKIT_PRAGMA_MSVC_WARNING_ENABLE(number)
#endif

#if defined(AIDKIT_MSVC)
	#define AIDKIT_PRAGMA_MSVC_DIAGNOSTIC(text)        AIDKIT_PRAGMA(warning(text))
	#define AIDKIT_PRAGMA_WARNING_PUSH()               AIDKIT_PRAGMA_MSVC_DIAGNOSTIC(push)
	#define AIDKIT_PRAGMA_WARNING_POP()                AIDKIT_PRAGMA_MSVC_DIAGNOSTIC(pop)
	#define AIDKIT_PRAGMA_MSVC_WARNING_DISABLE(number) AIDKIT_PRAGMA_MSVC_DIAGNOSTIC(disable: number)
	#define AIDKIT_PRAGMA_MSVC_WARNING_ENABLE(number)  AIDKIT_PRAGMA_MSVC_DIAGNOSTIC(default: number)

	#define AIDKIT_PRAGMA_GCC_WARNING_DISABLE(text)
	#define AIDKIT_PRAGMA_GCC_WARNING_DISABLE(text)
#endif
