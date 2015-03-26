# Copyright 2014 Peter Most, PERA Software Solutions GmbH
#
# This file is part of the CppAidKit library.
#
# CppAidKit is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# CppAidKit is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required( VERSION 3.0 )
set( CMAKE_WARN_DEPRECATED ON )
set( CMAKE_VERBOSE_MAKEFILE ON )
if ( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE debug )
endif()

project( AidKit )

############################# Setup Qt5 usage #################################
# See: http://doc.qt.io/qt-5/cmake-manual.html
#
# For AUTOMOC to work we also have to include the headers in the add_library() call!
# set( CMAKE_AUTOMOC ON )
#
# This is needed when a cpp-file includes the generated moc file.
# set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package( Qt5Widgets )

############################# Setup AidKit ####################################

add_compile_options( -std=c++14 -w -Wall -Wextra -pedantic )

set( HEADERS
	headers/pera_software/aidkit/AidKit.hpp
	headers/pera_software/aidkit/qt/MainWindow.hpp
	headers/pera_software/company/PERA.hpp
	headers/pera_software/company/AboutDialog.hpp
	headers/pera_software/company/Application.hpp
)
set( SOURCES
	sources/pera_software/aidkit/AidKit.cpp
	sources/pera_software/aidkit/qt/MainWindow.cpp
	sources/pera_software/company/PERA.cpp
	sources/pera_software/company/AboutDialog.cpp
	sources/pera_software/company/Application.cpp
)
qt5_wrap_cpp( MOC_SOURCES ${HEADERS})

qt5_add_resources( RESOURCES
	resources/pera_software/Resources.qrc
)
add_library( AidKit SHARED ${SOURCES} ${MOC_SOURCES} ${RESOURCES})
add_definitions( -DAIDKIT_LIBRARY_BUILD )
include_directories( headers/ )

target_link_libraries( AidKit Qt5::Widgets )

