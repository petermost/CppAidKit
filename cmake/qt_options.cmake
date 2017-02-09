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
	message( WARNING "Environment variable 'Qt5_DIR' not found!" )
elseif( NOT EXISTS "$ENV{Qt5_DIR}")
	message( FATAL_ERROR "Path '$ENV{Qt5_DIR}' from environment variable 'Qt5_DIR' doesn't exist!" )
endif()
