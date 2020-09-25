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

#if defined(AIDKIT_LINUX)
	#define AIDKIT_EXPORT __attribute__((visibility("default")))
	#define AIDKIT_IMPORT __attribute__((visibility("default")))

	#define AIDKIT_API_DEPRECATED __attribute__ ((__deprecated__))
#elif defined(AIDKIT_WINDOWS)
	#define AIDKIT_EXPORT __declspec(dllexport)
	#define AIDKIT_IMPORT __declspec(dllimport)

	#define AIDKIT_API_DEPRECATED __declspec(deprecated)
#endif

#if defined(AIDKIT_SHARED_LIBRARY)
	// Will be defined by cmake for shared libraries
	// (https://cmake.org/cmake/help/latest/prop_tgt/DEFINE_SYMBOL.html)
	#if defined(AidKit_EXPORTS)
		#define AIDKIT_API AIDKIT_EXPORT
	#else
		#define AIDKIT_API AIDKIT_IMPORT
	#endif
#elif defined(AIDKIT_STATIC_LIBRARY)
	#define AIDKIT_API
#endif

// Could have ben generated with cmake i.e.:
// include(GenerateExportHeader)
// generate_export_header(AidKit
//     EXPORT_FILE_NAME aidkit_api.hpp
//     INCLUDE_GUARD_NAME AIDKIT_API_HPP
//     EXPORT_MACRO_NAME AIDKIT_API
// )
// But I didn't want to rely too much on cmake ;-)

namespace pera_software::aidkit {

}
