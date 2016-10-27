# Enable glibc debug mode:

if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
	message( "Enabling glibc debug settings" )
	add_definitions( -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC )
endif()

