# Contains general options for cmake

set( CMAKE_WARN_DEPRECATED ON )

if ( NOT CMAKE_BUILD_TYPE )
	message( "Enabling debug build" )
	set( CMAKE_BUILD_TYPE Debug )
endif()

if ( NOT CMAKE_VERBOSE_MAKEFILE )
	message( "Enabling verbose makefile" )
	set( CMAKE_VERBOSE_MAKEFILE TRUE )
endif()

