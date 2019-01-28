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

// Include the cmake generated file. See generate_export_header() in the master CMakeLists.txt.
#include "cmake_aidkit_api.hpp"

#ifndef AIDKIT_API
    // Fail early if this symbol isn't defined.
    #error AIDKIT_API is not defined!
#endif

//#if defined( AIDKIT_GCC )
//	#define AIDKIT_DECLARE_EXPORT __attribute__(( visibility( "default" )))
//	#define AIDKIT_DECLARE_IMPORT __attribute__(( visibility( "default" )))
//#elif defined( AIDKIT_MSVC )
//	#define AIDKIT_DECLARE_EXPORT __declspec( dllexport )
//	#define AIDKIT_DECLARE_IMPORT __declspec( dllimport )
//#endif

//#if defined( AidKit_EXPORTS ) // Will be defined by cmake
//	#define AIDKIT_API AIDKIT_DECLARE_EXPORT
//#else
//	#define AIDKIT_API AIDKIT_DECLARE_IMPORT
//#endif

namespace pera_software::aidkit {

}
