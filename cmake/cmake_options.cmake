# Contains general options for cmake

set( CMAKE_WARN_DEPRECATED ON )

if ( NOT CMAKE_BUILD_TYPE )
	message( "Enabling debug build" )
	set( CMAKE_BUILD_TYPE Debug CACHE STRING "Select build type")
	# Present a combobox in the cmake-gui (https://blog.kitware.com/cmake-and-the-default-build-type/):
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if ( NOT CMAKE_VERBOSE_MAKEFILE )
	message( "Enabling verbose makefile" )
	set( CMAKE_VERBOSE_MAKEFILE TRUE )
endif()

