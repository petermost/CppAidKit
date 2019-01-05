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

# Library Sources:

set( sources
	src/pera_software/pera_software.cpp
	src/pera_software/aidkit/aidkit.hpp
	src/pera_software/aidkit/aidkit.cpp
	src/pera_software/aidkit/containers.hpp
	src/pera_software/aidkit/containers.cpp
	src/pera_software/aidkit/debug.hpp
	src/pera_software/aidkit/debug.cpp
	src/pera_software/aidkit/enum_class.hpp
	src/pera_software/aidkit/enum_class.cpp
	src/pera_software/aidkit/enum_flags.hpp
	src/pera_software/aidkit/enum_flags.cpp
	src/pera_software/aidkit/exception.hpp
	src/pera_software/aidkit/exception.cpp
	src/pera_software/aidkit/platform.hpp
	src/pera_software/aidkit/platform.cpp
	src/pera_software/aidkit/strings.hpp
	src/pera_software/aidkit/strings.cpp
	src/pera_software/aidkit/unicode.hpp
	src/pera_software/aidkit/unicode.cpp
	src/pera_software/aidkit/vectors.hpp
	src/pera_software/aidkit/vectors.cpp

	src/pera_software/aidkit/io/basic_file.hpp
	src/pera_software/aidkit/io/basic_file.cpp
	src/pera_software/aidkit/io/errno.hpp
	src/pera_software/aidkit/io/errno.cpp
	src/pera_software/aidkit/io/file.hpp
	src/pera_software/aidkit/io/file.cpp
	src/pera_software/aidkit/io/file_error.hpp
	src/pera_software/aidkit/io/file_error.cpp
	src/pera_software/aidkit/io/system_error.hpp
	src/pera_software/aidkit/io/system_error.cpp

	src/pera_software/aidkit/cpp/optional.cpp
	src/pera_software/aidkit/cpp/optional.hpp
	src/pera_software/aidkit/cpp/stdlib.hpp
	src/pera_software/aidkit/cpp/stdlib.cpp
	src/pera_software/aidkit/cpp/string_ref.hpp
	src/pera_software/aidkit/cpp/string_ref.cpp

	src/pera_software/aidkit/concurrent/data_mutex.hpp
	src/pera_software/aidkit/concurrent/data_mutex.cpp

	src/pera_software/company/PERA.hpp
	src/pera_software/company/PERA.cpp
)

set( testSources
	tests/pera_software/aidkit/enum_class_test.hpp
	tests/pera_software/aidkit/enum_class_test.cpp
	tests/pera_software/aidkit/enum_flags_test.hpp
	tests/pera_software/aidkit/enum_flags_test.cpp
	tests/pera_software/aidkit/strings_test.hpp
	tests/pera_software/aidkit/strings_test.cpp
	tests/pera_software/aidkit/test_main.cpp
	tests/pera_software/aidkit/unicode_test.hpp
	tests/pera_software/aidkit/unicode_test.cpp
	tests/pera_software/aidkit/vectors_test.hpp
	tests/pera_software/aidkit/vectors_test.cpp

	tests/pera_software/aidkit/concurrent/data_mutex_test.hpp
	tests/pera_software/aidkit/concurrent/data_mutex_test.cpp

	tests/pera_software/aidkit/io/file_test.hpp
	tests/pera_software/aidkit/io/file_test.cpp

	tests/pera_software/aidkit/cpp/stdlib_test.hpp
	tests/pera_software/aidkit/cpp/stdlib_test.cpp
)

# Library QtCore Sources:

set( qtCoreSources
	src/pera_software/aidkit/qt/qt.cpp

	src/pera_software/aidkit/qt/core/Chrono.hpp
	src/pera_software/aidkit/qt/core/Chrono.cpp
	src/pera_software/aidkit/qt/core/Console.hpp
	src/pera_software/aidkit/qt/core/Console.cpp
	src/pera_software/aidkit/qt/core/DirectoryGuide.hpp
	src/pera_software/aidkit/qt/core/DirectoryGuide.cpp
	src/pera_software/aidkit/qt/core/Endian.hpp
	src/pera_software/aidkit/qt/core/Endian.cpp
	src/pera_software/aidkit/qt/core/Enums.hpp
	src/pera_software/aidkit/qt/core/Enums.cpp
	src/pera_software/aidkit/qt/core/IniSettings.hpp
	src/pera_software/aidkit/qt/core/IniSettings.cpp
	src/pera_software/aidkit/qt/core/Persistable.hpp
	src/pera_software/aidkit/qt/core/Persistable.cpp
	src/pera_software/aidkit/qt/core/Socket.hpp
	src/pera_software/aidkit/qt/core/Socket.cpp

	src/pera_software/company/qt/ForwardDeclarations.hpp
	src/pera_software/company/qt/PERAIniSettings.cpp
	src/pera_software/company/qt/PERAIniSettings.hpp

	# Resources:

	resources/pera_software/aidkit/AidKitResources.qrc
	resources/pera_software/company/CompanyResources.qrc
)

set( qtCoreTestSources
	tests/pera_software/aidkit/qt/core/ConsoleTest.hpp
	tests/pera_software/aidkit/qt/core/ConsoleTest.cpp
	tests/pera_software/aidkit/qt/core/EndianTest.hpp
	tests/pera_software/aidkit/qt/core/EndianTest.cpp
)

# Library QtGui Sources:

set( qtGuiSources
	src/pera_software/aidkit/qt/Resources.hpp
	src/pera_software/aidkit/qt/Resources.cpp
	src/pera_software/aidkit/qt/gui/ForwardDeclarations.hpp
	src/pera_software/aidkit/qt/gui/MessagesModel.cpp
	src/pera_software/aidkit/qt/gui/MessagesModel.hpp
)

# Library QtWidgets Sources:

set( qtWidgetsSources
	src/pera_software/aidkit/qt/widgets/Actions.hpp
	src/pera_software/aidkit/qt/widgets/Actions.cpp
	src/pera_software/aidkit/qt/widgets/ForwardDeclarations.hpp
	src/pera_software/aidkit/qt/widgets/IntegerSpinBox.hpp
	src/pera_software/aidkit/qt/widgets/IntegerSpinBox.cpp
	src/pera_software/aidkit/qt/widgets/MainWindow.hpp
	src/pera_software/aidkit/qt/widgets/MainWindow.cpp
	src/pera_software/aidkit/qt/widgets/MessagesView.cpp
	src/pera_software/aidkit/qt/widgets/MessagesView.hpp
	src/pera_software/aidkit/qt/widgets/MessagesWidget.cpp
	src/pera_software/aidkit/qt/widgets/MessagesWidget.hpp
	src/pera_software/aidkit/qt/widgets/Widgets.hpp
	src/pera_software/aidkit/qt/widgets/Widgets.cpp

	src/pera_software/company/qt/PERAAboutDialog.hpp
	src/pera_software/company/qt/PERAAboutDialog.cpp
	src/pera_software/company/qt/PERAActions.hpp
	src/pera_software/company/qt/PERAActions.cpp
	src/pera_software/company/qt/PERAApplication.hpp
	src/pera_software/company/qt/PERAApplication.cpp
	src/pera_software/company/qt/PERAMainWindow.hpp
	src/pera_software/company/qt/PERAMainWindow.cpp
)

# Library Boost Sources:

set( boostSources
	src/pera_software/aidkit/boost/formatter.hpp
	src/pera_software/aidkit/boost/formatter.cpp
)
set( boostTestSources
	tests/pera_software/aidkit/boost/formatter_test.hpp
	tests/pera_software/aidkit/boost/formatter_test.cpp
)

# Test Library Sources

set( testLibSources
	src/pera_software/aidkit/qt/test/Test.hpp
	src/pera_software/aidkit/qt/test/Test.cpp
)

# Find the different packages but evaluate the results later:

find_package( Qt5 COMPONENTS Core Gui Widgets Test )

if ( Qt5Core_FOUND )
	set( CMAKE_AUTOMOC ON )
	set( CMAKE_AUTORCC ON )
	# set( CMAKE_AUTOUIC ON )
	# set( CMAKE_INCLUDE_CURRENT_DIR ON )

	# Disable the slot, signal, emit etc. keywords:
	add_definitions( -DQT_NO_KEYWORDS )

	list( APPEND sources ${qtCoreSources})
	list( APPEND testSources ${qtCoreTestSources})
endif()

if ( Qt5Gui_FOUND )
	list( APPEND sources ${qtGuiSources})
endif()

if ( Qt5Widgets_FOUND )
	list( APPEND sources ${qtWidgetsSources})
endif()

###############################################################################
# Setup Boost

find_package( Boost 1.69.0 QUIET )
if ( Boost_FOUND )
#	include_directories( ${Boost_INCLUDE_DIRS} )
#	link_directories( ${Boost_LIBRARY_DIRS} )

	list( APPEND sources ${boostSources} )
	list( APPEND testSources ${boostTestSources})
endif()

###############################################################################
# Setup AidKit

add_library( AidKit SHARED ${sources} ${RESOURCES} )
target_include_directories( AidKit PUBLIC src/ )
if ( Qt5Widgets_FOUND )
	target_link_libraries( AidKit Qt5::Widgets )
elseif ( Qt5Gui_FOUND )
	target_link_libraries( AidKit Qt5::Gui )
elseif ( Qt5Core_FOUND )
	target_link_libraries( AidKit Qt5::Core )
endif()

if ( Boost_FOUND )
	#target_link_libraries( AidKit Boost::format )
endif()

###############################################################################
# Setup AidKitTest

if ( Qt5Test_FOUND )
	add_library( AidKitTest SHARED ${testLibSources})
	target_include_directories( AidKitTest PUBLIC src/ )
	target_link_libraries( AidKitTest AidKit Qt5::Test Qt5::Core )
endif()

###############################################################################
# Setup AidKit unit tests

if ( Qt5Test_FOUND )
	add_executable( testAidKit ${testSources} )
	target_link_libraries( testAidKit AidKitTest AidKit )
endif()
