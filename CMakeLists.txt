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

cmake_minimum_required( VERSION 3.0 )
project( AidKit )

set( CMAKE_WARN_DEPRECATED ON )

if ( UNIX )
	set( CMAKE_PREFIX_PATH "/home/peter/Qt5.5.0/5.5/gcc_64/lib/cmake" )
elseif( WIN32 )
	set( CMAKE_PREFIX_PATH "C:/Qt/Qt5.5.0/5.5/mingw492_32/lib/cmake" )
endif()

if ( NOT CMAKE_BUILD_TYPE )
	message( "Enabling debug build" )
	set( CMAKE_BUILD_TYPE Debug )
endif()

if ( NOT CMAKE_VERBOSE_MAKEFILE )
	message( "Enabling verbose makefile" )
	set( CMAKE_VERBOSE_MAKEFILE TRUE )
endif()

# message( "C++ compiler version is: " ${CMAKE_CXX_COMPILER_VERSION})

############################# Setup Qt5 usage #################################
# See: http://doc.qt.io/qt-5/cmake-manual.html
#
# For AUTOMOC to work we also have to include the headers in the add_library() call!
# set( CMAKE_AUTOMOC ON )

# Allow including moc files:
# set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package( Qt5Widgets )
find_package( Qt5Test )

############################# Setup AidKit ####################################


add_compile_options(
	-std=c++14                  # Compile in C++14 mode

	-Wall -Wextra -Wpedantic    # Enable all warnings
	-Wmissing-include-dirs      # Warn if a user-supplied include directory does not exist.
	-Wundef                     # Warn if an undefined identifier is evaluated in an #if directive.
	-Wcast-align                # Warn whenever a pointer is cast such that the required alignment of the target is increased.
	-Wold-style-cast            # Warn if an old-style (C-style) cast to a non-void type is used within a C++ program.

	-fvisibility=hidden         # Make symbols hidden by default i.e. must be explicitly exported
	-fdiagnostics-show-option   # Show which switch caused a warning

	-pthread                    # Adds support for multithreading with the pthreads library. This option sets flags for both the preprocessor and linker
)

if ( CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5 )
	add_compile_options(
		-Wsuggest-override          # Warn about overriding virtual functions that are not marked with the override keyword.
	)
endif()

if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
	message( "Enabling debug settings" )
	add_definitions( -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC )
#	add_compile_options(
#		-fsanitize=address      # Enable AddressSanitizer, a fast memory error detector.
#		-fsanitize=thread       # Enable ThreadSanitizer, a fast data race detector.
#		-fsanitize=undefined    # Enable UndefinedBehaviorSanitizer, a fast undefined behavior detector.
#	)
endif()

if ( MINGW )
	add_definitions( -D__USE_MINGW_ANSI_STDIO )
endif()


set( OTHER_FILES
	lgpl.txt
)

# Library sources:

set( HEADERS
	src/pera_software/aidkit/aidkit.hpp
	src/pera_software/aidkit/debug.hpp
	src/pera_software/aidkit/unicode.hpp
	src/pera_software/aidkit/strings.hpp
	src/pera_software/aidkit/platform.hpp
	src/pera_software/aidkit/exception.hpp
	src/pera_software/aidkit/enum_class.hpp
	src/pera_software/aidkit/io/errno.hpp
	src/pera_software/aidkit/io/file.hpp
	src/pera_software/aidkit/io/basic_file.hpp
	src/pera_software/aidkit/io/file_error.hpp
	src/pera_software/aidkit/io/system_error.hpp
	src/pera_software/company/PERA.hpp
)
set( SOURCES
	src/pera_software/pera_software.cpp
	src/pera_software/aidkit/aidkit.cpp
	src/pera_software/aidkit/debug.cpp
	src/pera_software/aidkit/unicode.cpp
	src/pera_software/aidkit/strings.cpp
	src/pera_software/aidkit/platform.cpp
	src/pera_software/aidkit/exception.cpp
	src/pera_software/aidkit/enum_class.cpp
	src/pera_software/aidkit/io/errno.cpp
	src/pera_software/aidkit/io/file.cpp
	src/pera_software/aidkit/io/basic_file.cpp
	src/pera_software/aidkit/io/file_error.cpp
	src/pera_software/aidkit/io/system_error.cpp
	src/pera_software/company/PERA.cpp
)

set( QT_HEADERS
	src/pera_software/aidkit/qt/test/Test.hpp
	src/pera_software/aidkit/qt/net/Endian.hpp
	src/pera_software/aidkit/qt/core/DirectoryGuide.hpp
	src/pera_software/aidkit/qt/io/Console.hpp
	src/pera_software/aidkit/qt/widgets/QuitAction.hpp
	src/pera_software/company/qt/MainWindow.hpp
	src/pera_software/company/qt/AboutDialog.hpp
	src/pera_software/company/qt/Application.hpp
)
set( QT_SOURCES
	src/pera_software/aidkit/qt/qt.cpp
	src/pera_software/aidkit/qt/test/Test.cpp
	src/pera_software/aidkit/qt/net/Endian.cpp
	src/pera_software/aidkit/qt/core/DirectoryGuide.cpp
	src/pera_software/aidkit/qt/io/Console.cpp
	src/pera_software/aidkit/qt/widgets/QuitAction.cpp
	src/pera_software/company/qt/MainWindow.cpp
	src/pera_software/company/qt/AboutDialog.cpp
	src/pera_software/company/qt/Application.cpp
)

qt5_wrap_cpp( MOC_SOURCES ${QT_HEADERS})

qt5_add_resources( QRC_RESOURCES
	resources/pera_software/aidkit/AidKitResources.qrc
	resources/pera_software/company/CompanyResources.qrc
)

# Setup library build:

add_library( AidKit SHARED ${SOURCES} ${QT_SOURCES} ${MOC_SOURCES} ${QRC_RESOURCES})
include_directories( src/ )
target_link_libraries( AidKit Qt5::Test Qt5::Widgets )

if ( MINGW )
	# Linking to this library would solve linking errors to some *_nolock functions, but it results
	# in a startup crash most likely because of msvcrt.dll (libstdc++-6.dll) *and* msvr110.dll being used

	# target_link_libraries( AidKit msvcr110 )
endif()

########################### Setup testAidKit ##################################

set( TEST_HEADERS
#	tests/pera_software/aidkit/debug_test.hpp
	tests/pera_software/aidkit/strings_test.hpp
	tests/pera_software/aidkit/unicode_test.hpp
	tests/pera_software/aidkit/enum_class_test.hpp
	tests/pera_software/aidkit/io/file_test.hpp
	tests/pera_software/aidkit/qt/net/EndianTest.hpp
)

set( TEST_SOURCES
	tests/pera_software/aidkit/test_main.cpp
#	tests/pera_software/aidkit/debug_test.cpp
	tests/pera_software/aidkit/strings_test.cpp
	tests/pera_software/aidkit/unicode_test.cpp
	tests/pera_software/aidkit/enum_class_test.cpp
	tests/pera_software/aidkit/io/file_test.cpp
	tests/pera_software/aidkit/qt/net/EndianTest.cpp
)

qt5_wrap_cpp( MOC_TEST_SOURCES ${TEST_HEADERS})

# Setup library test build:

add_executable( testAidKit ${TEST_SOURCES} ${MOC_TEST_SOURCES})
target_link_libraries( testAidKit AidKit Qt5::Test )
