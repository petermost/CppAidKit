# Contains general options for cmake

set( CMAKE_WARN_DEPRECATED ON )
set( CMAKE_VERBOSE_MAKEFILE TRUE )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

if ( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES )
	message( "Enabling debug build" )
	set( CMAKE_BUILD_TYPE Debug CACHE STRING "Select build type" FORCE)
	# Present a combobox in the cmake-gui (https://blog.kitware.com/cmake-and-the-default-build-type/):
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
