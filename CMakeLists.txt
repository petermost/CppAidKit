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

cmake_minimum_required(VERSION 3.13)
project(AidKit VERSION 1.0.0.0)

include(GenerateExportHeader)
include(cmake/all_options.cmake)

find_package(Boost QUIET
	COMPONENTS
		filesystem
)
find_package(Qt5 QUIET
	COMPONENTS
		Core
		Gui
		Widgets
)
add_subdirectory(/usr/src/googletest googletest)

###############################################################################
# Setup AidKit:
# If no type is specified (SHARED or STATIC) then the user can define the type with the
# BUILD_SHARED_LIBS variable!

add_library(AidKit
	src/pera_software/pera_software.cpp
	src/pera_software/aidkit/aidkit.hpp
	src/pera_software/aidkit/aidkit.cpp
	src/pera_software/aidkit/bit_cast.hpp
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
	src/pera_software/aidkit/vectors.hpp
	src/pera_software/aidkit/vectors.cpp
	src/pera_software/aidkit/unicode.hpp
	src/pera_software/aidkit/unicode.cpp

	src/pera_software/aidkit/io/basic_file.hpp
	src/pera_software/aidkit/io/basic_file.cpp
	src/pera_software/aidkit/io/errno.hpp
	src/pera_software/aidkit/io/errno.cpp
	src/pera_software/aidkit/io/file.hpp
	src/pera_software/aidkit/io/file.cpp
	src/pera_software/aidkit/io/file_error.hpp
	src/pera_software/aidkit/io/file_error.cpp
	src/pera_software/aidkit/io/file_ptr.hpp
	src/pera_software/aidkit/io/file_ptr.cpp
	src/pera_software/aidkit/io/system_error.hpp
	src/pera_software/aidkit/io/system_error.cpp

	src/pera_software/aidkit/cpp/new.hpp
	src/pera_software/aidkit/cpp/new.cpp
	src/pera_software/aidkit/cpp/memory.hpp
	src/pera_software/aidkit/cpp/memory.cpp
	src/pera_software/aidkit/cpp/stdlib.hpp
	src/pera_software/aidkit/cpp/stdlib.cpp

	src/pera_software/aidkit/concurrent/data_mutex.hpp
	src/pera_software/aidkit/concurrent/data_mutex.cpp

	src/pera_software/company/PERA.hpp
	src/pera_software/company/PERA.cpp
)
set_default_target_options(AidKit)

set_target_properties(AidKit
	PROPERTIES
		SOVERSION ${PROJECT_VERSION}
)

# Generate the 'export header' and add the generated file to the library as well:

generate_export_header(AidKit
	EXPORT_FILE_NAME aidkit_api.hpp
	INCLUDE_GUARD_NAME AIDKIT_API_HPP
	EXPORT_MACRO_NAME AIDKIT_API
)
target_sources(AidKit
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}/aidkit_api.hpp
)

target_include_directories(AidKit
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDE_DIR}>
)

###############################################################################
# Setup AidKit tests:

add_executable(testAidKit
	tests/pera_software/aidkit/test_main.hpp
	tests/pera_software/aidkit/test_main.cpp

	tests/pera_software/aidkit/containers_test.cpp
	tests/pera_software/aidkit/enum_class_test.cpp
	tests/pera_software/aidkit/enum_flags_test.cpp
	tests/pera_software/aidkit/strings_test.cpp
	tests/pera_software/aidkit/vectors_test.cpp
	tests/pera_software/aidkit/unicode_test.cpp

	tests/pera_software/aidkit/concurrent/data_mutex_test.cpp

	tests/pera_software/aidkit/io/file_test.cpp
	tests/pera_software/aidkit/io/file_ptr_test.cpp

	tests/pera_software/aidkit/cpp/new_test.cpp
	tests/pera_software/aidkit/cpp/memory_test.cpp
	tests/pera_software/aidkit/cpp/stdlib_test.cpp
)
set_default_target_options(testAidKit)

target_include_directories(testAidKit
	PUBLIC
		src/
		tests/
)

target_link_libraries(testAidKit
	PRIVATE
		AidKit
		gtest
		# gtest_main
)


###############################################################################

if (Boost_FOUND)
	target_sources(AidKit
		PRIVATE
			src/pera_software/aidkit/boost/formatter.hpp
			src/pera_software/aidkit/boost/formatter.cpp
			src/pera_software/aidkit/boost/directory_guide.hpp
			src/pera_software/aidkit/boost/directory_guide.cpp
	)
	target_sources(testAidKit
		PRIVATE
			tests/pera_software/aidkit/boost/formatter_test.cpp
	)
	target_compile_definitions(AidKit
		PRIVATE
			BOOST_ALL_DYN_LINK
			BOOST_ASIO_NO_DEPRECATED
			BOOST_FILESYSTEM_NO_DEPRECATED
	)
	target_link_libraries(AidKit
		PUBLIC
			Boost::dynamic_linking
			Boost::disable_autolinking
			Boost::boost
			Boost::filesystem
	)
else()
	message(WARNING "Boost not found, building without it!")
endif()


if (Qt5Core_FOUND)
	# Setting the Qt 'AUTO'-properties *after* the targets are already defined seems not to work i.e.:
	# set(CMAKE_AUTOMOC ON)
	# set(CMAKE_AUTORCC ON)
	# set(CMAKE_AUTOUIC ON)
	# According	to https://cmake.org/cmake/help/latest/prop_tgt/AUTOMOC.html:
	# "This property is initialized by the value of the CMAKE_AUTOMOC variable *if it is set* when
	# a target is created."

	set_target_properties(AidKit testAidKit
		PROPERTIES
			AUTOMOC ON
			AUTORCC ON
	)
	target_sources(AidKit
		PRIVATE
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
	target_sources(testAidKit
		PRIVATE
			tests/pera_software/aidkit/qt/TestFixture.hpp
			tests/pera_software/aidkit/qt/TestFixture.cpp
			tests/pera_software/aidkit/qt/core/ConsoleTest.cpp
			tests/pera_software/aidkit/qt/core/EndianTest.cpp
	)
	# Disable the slot, signal, emit etc. keywords:
	target_compile_definitions(AidKit
		PRIVATE
			QT_NO_KEYWORDS
	)
	target_link_libraries(AidKit
		PUBLIC
			Qt5::Core
	)
else()
	message(WARNING "Qt5 Core not found, building without it!")
endif()

if (Qt5Gui_FOUND)
	target_sources(AidKit
		PRIVATE
			src/pera_software/aidkit/qt/gui/ForwardDeclarations.hpp
			src/pera_software/aidkit/qt/gui/MessagesModel.cpp
			src/pera_software/aidkit/qt/gui/MessagesModel.hpp
			src/pera_software/aidkit/qt/gui/Resources.hpp
			src/pera_software/aidkit/qt/gui/Resources.cpp
	)
	target_sources(testAidKit
		PRIVATE
			tests/pera_software/aidkit/qt/gui/ResourcesTest.hpp
			tests/pera_software/aidkit/qt/gui/ResourcesTest.cpp

			tests/pera_software/company/qt/PERAResourcesTest.cpp
	)
	target_link_libraries(AidKit
		PUBLIC
			Qt5::Gui
	)
else()
	message(WARNING "Qt5 Gui not found, building without it!")
endif()

if (Qt5Widgets_FOUND)
	target_sources(AidKit
		PRIVATE
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
			src/pera_software/company/qt/PERAResources.hpp
			src/pera_software/company/qt/PERAResources.cpp
	)
	target_link_libraries(AidKit
		PUBLIC
			Qt5::Widgets
	)
else()
	message(WARNING "Qt5 Widgets not found, building without it!")
endif()


###############################################################################
# Installing
# For testing: make DESTDIR=<directory> install

include(GNUInstallDirs)
install(TARGETS AidKit EXPORT exportName
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(EXPORT exportName
	DESTINATION cmake
	FILE AidKitConfig.cmake
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/aidkit_api.hpp
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pera_software/aidkit/
)
install(DIRECTORY src/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	FILES_MATCHING PATTERN "*.hpp"
)

###############################################################################
# Packaging

set(CPACK_GENERATOR DEB)
#set(CPACK_DEBIAN_PACKAGE_DEPENDS "")

set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "P. Most")

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "PERA Software Solutions GmbH")
set(CPACK_PACKAGE_CONTACT "pmost@pera-software.com")

set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local/")

include(CPack)
