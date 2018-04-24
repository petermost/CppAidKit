# Enable glibc debug mode:
# See https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html for further details.

if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
	message( "Enabling glibc debug settings" )
	add_definitions( -D_GLIBCXX_DEBUG )
	add_definitions( -D_GLIBCXX_DEBUG_PEDANTIC )
#	add_definitions( -D_GLIBCXX_CONCEPT_CHECKS )
	add_definitions( -D_GLIBCXX_ASSERTIONS )
	remove_definitions( -D_GLIBCXX_USE_DEPRECATED )
endif()

