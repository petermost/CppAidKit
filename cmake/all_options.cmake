include(${CMAKE_CURRENT_LIST_DIR}/report.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cpp_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/library_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/output_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/qt_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/rpath_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/gcc_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/clang_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/msvc_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/libstdcxx_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/libcxx_options.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/googletest.cmake)

report("CMAKE_VERSION: '${CMAKE_VERSION}'")

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)

if (CMAKE_VERBOSE_MAKEFILE)
	# Make Ninja build verbose as well (https://github.com/ninja-build/ninja/issues/900):
	set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Verbose Makefile" FORCE)
endif()

# Set default build type:
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type" FORCE)
	# Present a combobox in the cmake-gui (https://blog.kitware.com/cmake-and-the-default-build-type/):
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_WARN_DEPRECATED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(set_default_target_options targetName)
	set_default_cpp_target_options(${targetName})
	set_default_rpath_target_options(${targetName})
	set_default_output_target_options(${targetName})
	set_default_library_target_options(${targetName})

	# See https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html for a list of # compiler ids.
	# report("CMAKE_CXX_COMPILER_ID: '${CMAKE_CXX_COMPILER_ID}', CMAKE_CXX_COMPILER_VERSION: '${CMAKE_CXX_COMPILER_VERSION}'")
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			set_default_gcc_target_options(${targetName})
		elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
			set_default_clang_target_options(${targetName})
		endif()
		# GCC and Clang link to the libstdc++, so we set the options for both:
		set_default_libstdcxx_target_options(${targetName})
		# But in case libc++ (clang) is being used, set those options:
		set_default_libcxx_target_options(${targetName})
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		set_default_msvc_target_options(${targetName})
	endif()

	if (Qt5Core_FOUND)
		set_default_qt_target_options(${targetName})
	endif()
endfunction()
