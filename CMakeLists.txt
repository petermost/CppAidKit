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
project(AidKit VERSION 1.2.0.0)

include(cmake/AidKit.cmake)

find_package(Boost QUIET
	COMPONENTS
		filesystem
)
find_package(Qt5 QUIET
	COMPONENTS
		Core
		Gui
		Widgets
		Test
		LinguistTools
)

add_googletest_subdirectory()

###############################################################################
# Setup 'AidKit':
# If no type is specified (SHARED or STATIC) then the user can define the type with the
# BUILD_SHARED_LIBS variable!

add_library(AidKit
	src/pera_software/PERA.hpp
	src/pera_software/PERA.cpp

	src/pera_software/aidkit/aidkit.hpp
	src/pera_software/aidkit/aidkit.cpp
	src/pera_software/aidkit/bit_cast.hpp
	src/pera_software/aidkit/compiler.hpp
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

	src/pera_software/aidkit/stdlib/new.hpp
	src/pera_software/aidkit/stdlib/new.cpp
	src/pera_software/aidkit/stdlib/memory.hpp
	src/pera_software/aidkit/stdlib/memory.cpp
	src/pera_software/aidkit/stdlib/stdlib.hpp
	src/pera_software/aidkit/stdlib/stdlib.cpp

	src/pera_software/aidkit/concurrent/data_mutex.hpp
	src/pera_software/aidkit/concurrent/data_mutex.cpp
)
set_default_target_options(AidKit)

target_compile_definitions(AidKit
	PUBLIC
		$<IF:$<BOOL:${BUILD_SHARED_LIBS}>,AIDKIT_SHARED_LIBRARY,AIDKIT_STATIC_LIBRARY>
)
set_target_properties(AidKit
	PROPERTIES
		SOVERSION ${AidKit_VERSION}
)

target_include_directories(AidKit
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src/>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDE_DIR}>
)

###############################################################################
# Setup 'AidKitTest' a helper library to support tests:

if (TARGET GTest::GTest)
	add_library(AidKitTest
		tests/pera_software/aidkit/test_main.hpp
		tests/pera_software/aidkit/test_main.cpp
	)
	set_default_target_options(AidKitTest)

	target_include_directories(AidKitTest
		PUBLIC
			tests/
	)

	target_link_libraries(AidKitTest
		PUBLIC
			AidKit
			GTest::GTest
			# GTest::Main
	)
else()
	message(AUTHOR_WARNING "GoogleTest not found, building without it!")
endif()

###############################################################################
# Setup 'testAidKit', the tests for the AidKit library:

if (TARGET AidKitTest)
	add_executable(testAidKit
		tests/pera_software/aidkit/compiler_test.cpp
		tests/pera_software/aidkit/containers_test.cpp
		tests/pera_software/aidkit/enum_class_test.cpp
		tests/pera_software/aidkit/enum_flags_test.cpp
		tests/pera_software/aidkit/strings_test.cpp
		tests/pera_software/aidkit/vectors_test.cpp
		tests/pera_software/aidkit/unicode_test.cpp
		tests/pera_software/aidkit/concurrent/data_mutex_test.cpp

		tests/pera_software/aidkit/io/file_test.cpp
		tests/pera_software/aidkit/io/file_ptr_test.cpp

		tests/pera_software/aidkit/stdlib/InstanceCounter.hpp
		tests/pera_software/aidkit/stdlib/InstanceCounter.cpp
		tests/pera_software/aidkit/stdlib/new_test.cpp
		tests/pera_software/aidkit/stdlib/memory_test.cpp
		tests/pera_software/aidkit/stdlib/stdlib_test.cpp
	)

	set_default_target_options(testAidKit)

	target_link_libraries(testAidKit
		PRIVATE
			AidKitTest
	)
endif()

if (TARGET Qt5::Widgets)
	target_sources(AidKit
		PRIVATE
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
			src/pera_software/aidkit/qt/core/Pointer.hpp
			src/pera_software/aidkit/qt/core/Pointer.cpp
			src/pera_software/aidkit/qt/core/Socket.hpp
			src/pera_software/aidkit/qt/core/Socket.cpp
			src/pera_software/aidkit/qt/core/Strings.hpp
			src/pera_software/aidkit/qt/core/Strings.cpp

			src/pera_software/aidkit/qt/PERAForwardDeclarations.hpp
			src/pera_software/aidkit/qt/core/PERASettings.cpp
			src/pera_software/aidkit/qt/core/PERASettings.hpp

			src/pera_software/aidkit/qt/gui/ForwardDeclarations.hpp
			src/pera_software/aidkit/qt/gui/MessagesModel.cpp
			src/pera_software/aidkit/qt/gui/MessagesModel.hpp
			src/pera_software/aidkit/qt/gui/Resources.hpp
			src/pera_software/aidkit/qt/gui/Resources.cpp
			src/pera_software/aidkit/qt/gui/PERAResources.hpp
			src/pera_software/aidkit/qt/gui/PERAResources.cpp

			src/pera_software/aidkit/qt/widgets/Application.hpp
			src/pera_software/aidkit/qt/widgets/Application.cpp
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

			src/pera_software/aidkit/qt/widgets/PERAAboutDialog.hpp
			src/pera_software/aidkit/qt/widgets/PERAAboutDialog.cpp
			src/pera_software/aidkit/qt/widgets/PERAActions.hpp
			src/pera_software/aidkit/qt/widgets/PERAActions.cpp
			src/pera_software/aidkit/qt/widgets/PERAApplication.hpp
			src/pera_software/aidkit/qt/widgets/PERAApplication.cpp
			src/pera_software/aidkit/qt/widgets/PERAMainWindow.hpp
			src/pera_software/aidkit/qt/widgets/PERAMainWindow.cpp

			src/pera_software/aidkit/qt/properties/Bindings.hpp
			src/pera_software/aidkit/qt/properties/Bindings.cpp
			src/pera_software/aidkit/qt/properties/Property.hpp
			src/pera_software/aidkit/qt/properties/Property.cpp
			src/pera_software/aidkit/qt/properties/BooleanProperty.hpp
			src/pera_software/aidkit/qt/properties/BooleanProperty.cpp
			src/pera_software/aidkit/qt/properties/IntegerProperty.hpp
			src/pera_software/aidkit/qt/properties/IntegerProperty.cpp
			src/pera_software/aidkit/qt/properties/StringProperty.hpp
			src/pera_software/aidkit/qt/properties/StringProperty.cpp

			# Resources:

			resources/pera_software/aidkit/AidKitResources.qrc
			resources/pera_software/PERAResources.qrc

	)
	if (TARGET AidKitTest AND TARGET Qt5::Test)
		target_sources(AidKitTest
			PRIVATE
				tests/pera_software/aidkit/qt/core/StringPrinter.hpp
				tests/pera_software/aidkit/qt/core/StringPrinter.cpp

				tests/pera_software/aidkit/qt/TestFixture.hpp
				tests/pera_software/aidkit/qt/TestFixture.cpp
		)
		target_link_libraries(AidKitTest
			PUBLIC
				Qt5::Test
		)
	endif()

	if (TARGET testAidKit)
		target_sources(testAidKit
			PRIVATE
				tests/pera_software/aidkit/qt/core/ConsoleTest.cpp
				tests/pera_software/aidkit/qt/core/EndianTest.cpp
				tests/pera_software/aidkit/qt/core/StringsTest.cpp

				tests/pera_software/aidkit/qt/gui/ResourcesTest.hpp
				tests/pera_software/aidkit/qt/gui/ResourcesTest.cpp
				tests/pera_software/aidkit/qt/gui/PERAResourcesTest.cpp

				tests/pera_software/aidkit/qt/properties/PropertiesTest.cpp
		)
	endif()

	target_link_libraries(AidKit
		PUBLIC
			Qt5::Core
			Qt5::Gui
			Qt5::Widgets
	)
else()
	message(AUTHOR_WARNING "Qt5 Widgets not found, building without it!")
endif()

if (Qt5LinguistTools_FOUND)
	# Embed translation files as a resource:
	# From "The missing example to use cmake qt5_create_translation"
	# (https://gist.github.com/giraldeau/546ba5512a74dfe9d8ea0862d66db412)

	configure_file(translations/AidKitTranslations.qrc ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
	qt5_create_translation(AIDKIT_TRANSLATION_FILES ${CMAKE_CURRENT_SOURCE_DIR} translations/AidKitTranslations_de.ts)

	target_sources(AidKit
		PRIVATE
			src/pera_software/aidkit/qt/core/Translator.hpp
			src/pera_software/aidkit/qt/core/Translator.cpp
			# translations/AidKitTranslations.qrc
			translations/AidKitTranslations_de.ts
			${AIDKIT_TRANSLATION_FILES}
			${CMAKE_CURRENT_BINARY_DIR}/AidKitTranslations.qrc
	)

	if (TARGET testAidKit)
		target_sources(testAidKit
			PRIVATE
				tests/pera_software/aidkit/qt/core/TranslatorTest.cpp
		)
	endif()
else()
	message(AUTHOR_WARNING "Qt5 LinguistTools not found, building without it!")
endif()

###############################################################################

if (TARGET Boost::filesystem)
	target_sources(AidKit
		PRIVATE
			src/pera_software/aidkit/boost/formatter.hpp
			src/pera_software/aidkit/boost/formatter.cpp
			src/pera_software/aidkit/boost/directory_guide.hpp
			src/pera_software/aidkit/boost/directory_guide.cpp
	)
	if (TARGET testAidKit)
		target_sources(testAidKit
			PRIVATE
				tests/pera_software/aidkit/boost/formatter_test.cpp
				tests/pera_software/aidkit/boost/directory_guide_test.cpp
		)
	endif()
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
			Boost::headers
			Boost::filesystem
	)
else()
	message(AUTHOR_WARNING "Boost filesysstem not found, building without it!")
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
