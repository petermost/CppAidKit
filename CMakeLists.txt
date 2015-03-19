cmake_minimum_required( VERSION 3.0 )
set( CMAKE_WARN_DEPRECATED ON )
set( CMAKE_VERBOSE_MAKEFILE ON )

if ( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE debug )
endif()

project( AidKit )

############################# Setup Qt5 usage #################################
# See: http://doc.qt.io/qt-5/cmake-manual.html

set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
find_package( Qt5Widgets )

############################# Setup AidKit ####################################

add_compile_options( -std=c++14 -w -Wall -Wextra -pedantic )

set( HEADERS
	headers/pera_software/company/PERA.hpp
	headers/pera_software/company/AboutDialog.hpp
)
set( SOURCES
	sources/pera_software/company/PERA.cpp
	sources/pera_software/company/AboutDialog.cpp
)

add_library( AidKit SHARED ${HEADERS} ${SOURCES} )
add_definitions( -DAIDKIT_LIBRARY_BUILD )
include_directories( headers/ )
target_link_libraries( AidKit Qt5::Widgets )
