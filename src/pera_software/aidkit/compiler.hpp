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

#if defined(AIDKIT_GCC)
	#define AIDKIT_WARNING_PUSH() _Pragma(AIDKIT_STRINGIZE(GCC diagnostic push))
	#define AIDKIT_WARNING_POP()  _Pragma(AIDKIT_STRINGIZE(GCC diagnostic pop))

	#define AIDKIT_WARNING_DISABLE_GCC(text) _Pragma(AIDKIT_STRINGIZE(GCC diagnostic ignored text))
	#define AIDKIT_WARNING_DISABLE_CLANG(text)
	#define AIDKIT_WARNING_DISABLE_MSVC(number)
#endif

#if defined(AIDKIT_CLANG)
	#define AIDKIT_WARNING_PUSH() _Pragma(AIDKIT_STRINGIZE(clang diagnostic push))
	#define AIDKIT_WARNING_POP()  _Pragma(AIDKIT_STRINGIZE(clang diagnostic pop))

	#define AIDKIT_WARNING_DISABLE_CLANG(text) _Pragma(AIDKIT_STRINGIZE(clang diagnostic ignored text))
	#define AIDKIT_WARNING_DISABLE_GCC(text)
	#define AIDKIT_WARNING_DISABLE_MSVC(number)
#endif

#if defined(AIDKIT_MSVC)
	#define AIDKIT_WARNING_PUSH() _Pragma(AIDKIT_STRINGIZE(warning(push)))
	#define AIDKIT_WARNING_POP()  _Pragma(AIDKIT_STRINGIZE(warning(pop)))

	#define AIDKIT_WARNING_DISABLE_MSVC(number) _Pragma(AIDKIT_STRINGIZE(warning(disable: number)))
	#define AIDKIT_WARNING_DISABLE_GCC(text)
	#define AIDKIT_WARNING_DISABLE_CLANG(text)
#endif
