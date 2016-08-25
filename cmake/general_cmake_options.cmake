# Contains general options for cmake

set( CMAKE_WARN_DEPRECATED ON )

# Show the compilers name and version:

message( "C++ compiler is: " ${CMAKE_CXX_COMPILER_ID} ", version: " ${CMAKE_CXX_COMPILER_VERSION})

if ( NOT CMAKE_BUILD_TYPE )
	message( "Enabling debug build" )
	set( CMAKE_BUILD_TYPE Debug )
endif()

if ( NOT CMAKE_VERBOSE_MAKEFILE )
	message( "Enabling verbose makefile" )
	set( CMAKE_VERBOSE_MAKEFILE TRUE )
endif()

