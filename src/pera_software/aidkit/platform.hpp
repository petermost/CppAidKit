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

// To see the predefined symbols from GCC use cpp -dM or gcc <file> -dM -M

// Determine what kind (DEBUG|RELEASE) build it is:

#if defined( _DEBUG ) || defined( DEBUG ) || !defined( NDEBUG )
	#define AIDKIT_DEBUG
#else
	#define AIDKIT_RELEASE
#endif

// Determine the operating system:

#if defined( _WIN32 ) || defined( WIN32 )
	#define AIDKIT_WINDOWS
#elif defined( __linux__ )
	#define AIDKIT_LINUX
#else
	#error Can't determine operating system!
#endif

// Determine the compiler:

#if defined( _MSC_VER )
	#define AIDKIT_MSVC
#elif defined( __GNUC__ )
	#define AIDKIT_GCC
	#if defined( __MINGW32__ ) || defined( __MINGW64__ )
		#define AIDKIT_MINGW
	#endif
#else
	#error "Can't determine compiler!"
#endif
