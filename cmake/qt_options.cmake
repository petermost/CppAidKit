# Instead of hard coding the Qt path like this:
#
#if ( UNIX )
#	set( CMAKE_PREFIX_PATH "/home/peter/Qt/5.6/gcc_64/lib/cmake" )
#elseif( WIN32 )
#	# set( CMAKE_PREFIX_PATH "C:/Qt/Qt5.5.1/5.5/mingw492_32/lib/cmake" )
#endif()
#
# we rely on the existence of the Qt5_DIR environment variable. For easier debugging we do some
# preliminary checks here:

if ( NOT DEFINED ENV{Qt5_DIR})
	message( WARNING "The environment variable 'Qt5_DIR' was not found!" )
elseif( NOT EXISTS "$ENV{Qt5_DIR}")
	message( FATAL_ERROR "The stored path '$ENV{Qt5_DIR}' in the environment variable 'Qt5_DIR' doesn't exist!" )
else()
	message( "Appending '$ENV{Qt5_DIR}' to CMAKE_PREFIX_PATH." )
	list( APPEND CMAKE_PREFIX_PATH $ENV{Qt5_DIR} )
endif()

# If this macro is defined, the compiler will generate warnings if API declared as deprecated by Qt
# is used.
add_definitions(-DQT_DEPRECATED_WARNINGS)

# This macro can be defined in the project file to disable functions deprecated in a specified
# version of Qt or any earlier version.
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x000000)

# Enable C++17 support:

#if ( ${CMAKE_VERSION} VERSION_LESS 3.8.0 )
#	# From https://gitlab.kitware.com/cmake/cmake/issues/16468
#	find_package( Qt5Core )
#	if ( Qt5Core_FOUND )
#		# get_property( propertyValue TARGET Qt5::Core PROPERTY INTERFACE_COMPILE_FEATURES )
#		# message( "Property: ${propertyValue}" )
#		set_property( TARGET Qt5::Core PROPERTY INTERFACE_COMPILE_FEATURES "" )
#		add_compile_options( -std=gnu++1z )
#	endif()
#else()
#	message( FATAL_ERROR "Remove missing cmake C++17 support workaround!" )
#endif()
