if ( NOT DEFINED QT_CMAKE_DIR )
	set( QT_CMAKE_DIR "" CACHE PATH "Select Qt5 cmake directory (e.g.: ~/Qt/5.11.1/gcc_64/lib/cmake)" )
endif()
if( NOT EXISTS ${QT_CMAKE_DIR} )
	message( FATAL_ERROR "The path '${QT_CMAKE_DIR}' in 'QT_CMAKE_DIR' doesn't exist!" )
endif()

message( "Appending '${QT_CMAKE_DIR}' to CMAKE_PREFIX_PATH." )
list( APPEND CMAKE_PREFIX_PATH ${QT_CMAKE_DIR} )

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
