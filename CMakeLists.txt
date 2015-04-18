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
project( AidKit )

set( CMAKE_WARN_DEPRECATED ON )

if ( NOT CMAKE_BUILD_TYPE )
	message( "Enabling debug build" )
	set( CMAKE_BUILD_TYPE debug )
endif()

if ( NOT CMAKE_VERBOSE_MAKEFILE )
	message( "Enabling verbose makefile" )
	set( CMAKE_VERBOSE_MAKEFILE TRUE )
endif()

if ( UNIX )
	set( CMAKE_PREFIX_PATH "/home/peter/Qt5.4.1/5.4/gcc_64/lib/cmake" )
elseif( WIN32 )
	message( "Set path to windows qt directory!" )
	set( CMAKE_PREFIX_PATH "c:/Qt5.4.1/5.4/" )
endif()

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

set( OTHER_FILES
	lgpl.txt
)

set( HEADERS
	src/pera_software/aidkit/AidKit.hpp
	src/pera_software/company/PERA.hpp
	src/pera_software/aidkit/Exception.hpp
	src/pera_software/aidkit/io/ErrNoException.hpp
)
set( SOURCES
	src/pera_software/aidkit/AidKit.cpp
	src/pera_software/company/PERA.cpp
	src/pera_software/aidkit/Exception.cpp
	src/pera_software/aidkit/io/ErrNoException.cpp
)

set( QT_HEADERS
	src/pera_software/aidkit/qt/core/DirectoryGuide.hpp
	src/pera_software/aidkit/qt/widgets/QuitAction.hpp
	src/pera_software/company/qt/MainWindow.hpp
	src/pera_software/company/qt/AboutDialog.hpp
	src/pera_software/company/qt/Application.hpp
)
set( QT_SOURCES
	src/pera_software/aidkit/qt/core/DirectoryGuide.cpp
	src/pera_software/aidkit/qt/widgets/QuitAction.cpp
	src/pera_software/company/qt/MainWindow.cpp
	src/pera_software/company/qt/AboutDialog.cpp
	src/pera_software/company/qt/Application.cpp
)
qt5_wrap_cpp( MOC_SOURCES ${QT_HEADERS})

qt5_add_resources( QT_RESOURCES
	resources/pera_software/aidkit/AidKitResources.qrc
	resources/pera_software/company/CompanyResources.qrc
)
add_library( AidKit SHARED ${SOURCES} ${QT_SOURCES} ${MOC_SOURCES} ${QT_RESOURCES})
include_directories( src/ )

target_link_libraries( AidKit Qt5::Widgets )

