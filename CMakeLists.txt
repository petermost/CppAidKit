# Copyright 2015 Peter Most, PERA Software Solutions GmbH
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

cmake_minimum_required( VERSION 3.5 )
project( AidKit )

include( cmake/all_options.cmake )

set( OTHER_FILES
	lgpl.txt
	src/pera_software/aidkit/qt/qt.cpp
)

# Library Sources:

set( HEADERS
	src/pera_software/aidkit/aidkit.hpp
	src/pera_software/aidkit/containers.hpp
	src/pera_software/aidkit/debug.hpp
	src/pera_software/aidkit/enum_class.hpp
	src/pera_software/aidkit/enum_flags.hpp
	src/pera_software/aidkit/exception.hpp
	src/pera_software/aidkit/unicode.hpp
	src/pera_software/aidkit/platform.hpp
	src/pera_software/aidkit/strings.hpp
	src/pera_software/aidkit/string_ref.hpp
	src/pera_software/aidkit/vectors.hpp
	src/pera_software/aidkit/io/errno.hpp
	src/pera_software/aidkit/io/file.hpp
	src/pera_software/aidkit/io/basic_file.hpp
	src/pera_software/aidkit/io/file_error.hpp
	src/pera_software/aidkit/io/system_error.hpp
	src/pera_software/aidkit/concurrent/data_mutex.hpp
	src/pera_software/company/PERA.hpp
)
set( SOURCES
	src/pera_software/pera_software.cpp
	src/pera_software/aidkit/aidkit.cpp
	src/pera_software/aidkit/containers.cpp
	src/pera_software/aidkit/debug.cpp
	src/pera_software/aidkit/enum_class.cpp
	src/pera_software/aidkit/enum_flags.cpp
	src/pera_software/aidkit/exception.cpp
	src/pera_software/aidkit/unicode.cpp
	src/pera_software/aidkit/platform.cpp
	src/pera_software/aidkit/strings.cpp
	src/pera_software/aidkit/string_ref.cpp
	src/pera_software/aidkit/vectors.cpp
	src/pera_software/aidkit/io/errno.cpp
	src/pera_software/aidkit/io/file.cpp
	src/pera_software/aidkit/io/basic_file.cpp
	src/pera_software/aidkit/io/file_error.cpp
	src/pera_software/aidkit/io/system_error.cpp
	src/pera_software/aidkit/concurrent/data_mutex.cpp
	src/pera_software/company/PERA.cpp
)

set( TEST_HEADERS
	tests/pera_software/aidkit/enum_class_test.hpp
	tests/pera_software/aidkit/enum_flags_test.hpp
	tests/pera_software/aidkit/strings_test.hpp
	tests/pera_software/aidkit/unicode_test.hpp
	tests/pera_software/aidkit/vectors_test.hpp
	tests/pera_software/aidkit/concurrent/data_mutex_test.hpp
	tests/pera_software/aidkit/io/file_test.hpp
)
set( TEST_SOURCES
	tests/pera_software/aidkit/test_main.cpp
	tests/pera_software/aidkit/enum_class_test.cpp
	tests/pera_software/aidkit/enum_flags_test.cpp
	tests/pera_software/aidkit/strings_test.cpp
	tests/pera_software/aidkit/unicode_test.cpp
	tests/pera_software/aidkit/vectors_test.cpp
	tests/pera_software/aidkit/concurrent/data_mutex_test.cpp
	tests/pera_software/aidkit/io/file_test.cpp
)

# Library QtCore Sources:

set( QT_CORE_HEADERS
	src/pera_software/aidkit/qt/io/Console.hpp
	src/pera_software/aidkit/qt/net/Endian.hpp
	src/pera_software/aidkit/qt/core/DirectoryGuide.hpp
	src/pera_software/aidkit/qt/core/Enums.hpp
	src/pera_software/aidkit/qt/core/IniSettings.hpp
)
set( QT_CORE_SOURCES
	src/pera_software/aidkit/qt/io/Console.cpp
	src/pera_software/aidkit/qt/net/Endian.cpp
	src/pera_software/aidkit/qt/core/DirectoryGuide.cpp
	src/pera_software/aidkit/qt/core/Enums.cpp
	src/pera_software/aidkit/qt/core/IniSettings.cpp
)
set( QT_CORE_RESOURCES
	resources/pera_software/aidkit/AidKitResources.qrc
	resources/pera_software/company/CompanyResources.qrc
)
set( QT_CORE_TEST_HEADERS
	tests/pera_software/aidkit/qt/net/EndianTest.hpp
)
set( QT_CORE_TEST_SOURCES
	tests/pera_software/aidkit/qt/net/EndianTest.cpp
)

# Library QtGui Sources:

set( QT_GUI_HEADERS
	src/pera_software/aidkit/qt/Resources.hpp
)
set( QT_GUI_SOURCES
	src/pera_software/aidkit/qt/Resources.cpp
)

# Library QtWidgets Sources:

set( QT_WIDGETS_HEADERS
	src/pera_software/aidkit/qt/widgets/MainWindow.hpp
	src/pera_software/aidkit/qt/widgets/MessagesWidget.hpp
	src/pera_software/aidkit/qt/widgets/QuitAction.hpp
	src/pera_software/company/qt/PERAAboutDialog.hpp
	src/pera_software/company/qt/PERAApplication.hpp
	src/pera_software/company/qt/PERAMainWindow.hpp
)
set( QT_WIDGETS_SOURCES
	src/pera_software/aidkit/qt/widgets/MainWindow.cpp
	src/pera_software/aidkit/qt/widgets/MessagesWidget.cpp
	src/pera_software/aidkit/qt/widgets/QuitAction.cpp
	src/pera_software/company/qt/PERAAboutDialog.cpp
	src/pera_software/company/qt/PERAApplication.cpp
	src/pera_software/company/qt/PERAMainWindow.cpp
)

# Library Boost Sources:

set( BOOST_HEADERS
	src/pera_software/aidkit/boost/formatter.hpp
)
set( BOOST_SOURCES
	src/pera_software/aidkit/boost/formatter.cpp
)
set( BOOST_TEST_HEADERS
	tests/pera_software/aidkit/boost/formatter_test.hpp
)
set( BOOST_TEST_SOURCES
	tests/pera_software/aidkit/boost/formatter_test.cpp
)

# Test Library Sources

set( TESTLIB_HEADERS
	tests/pera_software/aidkit/qt/test/Test.hpp
)
set( TESTLIB_SOURCES
	tests/pera_software/aidkit/qt/test/Test.cpp
)


macro( FindPackage packageName )
	find_package( ${packageName} QUIET )
	if ( ${packageName}_FOUND )
		message( "Building with ${packageName}." )
	else()
		message( "Building without ${packageName}!" )
	endif()
endmacro()



FindPackage( Qt5Core )
if ( Qt5Core_FOUND )

	# Disable the slot, signal, emit etc. keywords:
	add_definitions( -DQT_NO_KEYWORDS )

	qt5_add_resources( RESOURCES ${QT_CORE_RESOURCES} )

	qt5_wrap_cpp( QT_CORE_MOC_SOURCES ${QT_CORE_HEADERS} )
	list( APPEND SOURCES ${QT_CORE_SOURCES} ${QT_CORE_MOC_SOURCES} )

	qt5_wrap_cpp( QT_CORE_TEST_MOC_SOURCES ${QT_CORE_TEST_HEADERS} )
	list( APPEND TEST_SOURCES ${QT_CORE_TEST_SOURCES} ${QT_CORE_TEST_MOC_SOURCES} )
endif()

FindPackage( Qt5Gui )
if ( Qt5Gui_FOUND )
	qt5_wrap_cpp( QT_GUI_MOC_SOURCES ${QT_GUI_HEADERS})
	list( APPEND SOURCES ${QT_GUI_SOURCES} ${QT_GUI_MOC_SOURCES} )
endif()

FindPackage( Qt5Widgets )
if ( Qt5Widgets_FOUND )
	qt5_wrap_cpp( QT_WIDGETS_MOC_SOURCES ${QT_WIDGETS_HEADERS})
	list( APPEND SOURCES ${QT_WIDGETS_SOURCES} ${QT_WIDGETS_MOC_SOURCES} )
endif()

################################ Setup Boost ##################################

FindPackage( Boost )
if ( Boost_FOUND )
#	include_directories( ${Boost_INCLUDE_DIRS} )
#	link_directories( ${Boost_LIBRARY_DIRS} )

	list( APPEND SOURCES ${BOOST_SOURCES} )

	qt5_wrap_cpp( BOOST_MOC_SOURCES ${BOOST_TEST_HEADERS} )
	list( APPEND TEST_SOURCES ${BOOST_TEST_SOURCES} ${BOOST_MOC_SOURCES} )
endif()

############################## Setup AidKit ###################################

include_directories( src/ )
add_library( AidKit SHARED ${SOURCES} ${RESOURCES} )
if ( Qt5Core_FOUND )
	target_link_libraries( AidKit Qt5::Core )
endif()
if ( Qt5Gui_FOUND )
	target_link_libraries( AidKit Qt5::Gui )
endif()
if ( Qt5Widgets_FOUND )
	target_link_libraries( AidKit Qt5::Widgets )
endif()

############################## Setup AidKitTest ###############################

FindPackage( Qt5Test )

if ( Qt5Test_FOUND )
	qt5_wrap_cpp( TESTLIB_MOC_SOURCES ${TESTLIB_HEADERS} )

	add_library( AidKitTest SHARED ${TESTLIB_SOURCES} ${TESTLIB_MOC_SOURCES} )
	target_link_libraries( AidKitTest Qt5::Test Qt5::Core )
endif()

########################### Setup AidKit unit tests ###########################

if ( Qt5Test_FOUND )

	# Prepare the 'normal' test files:

	qt5_wrap_cpp( TEST_MOC_SOURCES ${TEST_HEADERS} )
	list( APPEND TEST_SOURCES ${TEST_MOC_SOURCES} )

	include_directories( tests/ )
	add_executable( testAidKit ${TEST_SOURCES} )
	target_link_libraries( testAidKit AidKitTest AidKit )
endif()
