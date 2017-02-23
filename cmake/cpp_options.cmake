# Define the C++ standard:

if ( ${CMAKE_VERSION} VERSION_EQUAL 3.8.0 OR ${CMAKE_VERSION} VERSION_GREATER 3.8.0 )
	message( FATAL_ERROR "Remove missing cmake C++17 support workaround!")
	# https://cmake.org/cmake/help/v3.8/prop_tgt/CXX_STANDARD.html
	set( CMAKE_CXX_STANDARD 17 )

	# Don't fall back to an earlier standard:

	set( CMAKE_CXX_STANDARD_REQUIRED ON )
endif()
