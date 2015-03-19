cmake_minimum_required( VERSION 3.0 )
set( CMAKE_WARN_DEPRECATED ON )
set( CMAKE_VERBOSE_MAKEFILE ON )

project( AidKit )
add_compile_options( -std=c++14 -w -Wall -Wextra -pedantic )

add_library( AidKit SHARED
	sources/pera_software/company/PERA.cpp
)
add_definitions( -DAIDKIT_LIBRARY_BUILD )
include_directories( headers/ )

############################# Setup Qt5 usage #################################
# See: http://doc.qt.io/qt-5/cmake-manual.html
set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
find_package( Qt5Widgets )
target_link_libraries( AidKit Qt5::Widgets )

