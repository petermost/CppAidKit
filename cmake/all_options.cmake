message( "CMake version: ${CMAKE_VERSION}")
# See https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html for a list of
# compiler ids.
message( "C++ compiler: " ${CMAKE_CXX_COMPILER_ID} ", version: " ${CMAKE_CXX_COMPILER_VERSION})
if ( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
	if ( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
		include( ${CMAKE_CURRENT_LIST_DIR}/gcc_options.cmake )
	elseif( CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		include( ${CMAKE_CURRENT_LIST_DIR}/clang_options.cmake )
	endif()
	# Both compiler link to the libstdc++, so we set the options for both:
	include( ${CMAKE_CURRENT_LIST_DIR}/libstdc++_options.cmake )
elseif( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	include( ${CMAKE_CURRENT_LIST_DIR}/msvc_options.cmake )
endif()

include( ${CMAKE_CURRENT_LIST_DIR}/cmake_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/cpp_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/library_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/output_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/qt_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/rpath_options.cmake )
