cmake_minimum_required(VERSION 2.8)

project(AidKit)

set( CMAKE_BUILD_TYPE Debug )

# Qt5:

set( Qt5CMakeDir /home/peter/Qt/5.1.1/gcc_64/lib/cmake )
set( Qt5Core_DIR ${Qt5CMakeDir}/Qt5Core/ )
set( Qt5Gui_DIR ${Qt5CMakeDir}/Qt5Gui/ )
set( Qt5Widgets_DIR ${Qt5CMakeDir}/Qt5Widgets/ )

find_package( Qt5Widgets QUIET )
if ( Qt5Widgets_FOUND )
	message( "Building with Qt." )
	set( CMAKE_AUTOMOC ON )
	set( CMAKE_INCLUDE_CURRENT_DIR ON )

	set( qtSources
		AidKit/Qt/AidKit_Qt_Action.cpp
		AidKit/Qt/AidKit_Qt_Network.cpp
		AidKit/Qt/AidKit_Qt_DirectoryGuide.cpp
		AidKit/Qt/AidKit_Qt_StandardActions.cpp
	)
else()
	message( "Building without Qt!" )
endif()

# Boost:

find_package( Boost COMPONENTS system filesystem QUIET )
if ( Boost_FOUND )
	message( "Building with Boost." )
	include_directories( ${Boost_INCLUDE_DIRS} )
	link_directories( ${Boost_LIBRARY_DIRS} )
	set( boostLibraries ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} )

	set( boostSources
		AidKit/Boost/AidKit_Boost_DirectoryGuide.cpp
		AidKit/Boost/AidKit_Boost_Network.cpp
	)
else()
	message( "Building without Boost!" )
endif()

# Linux Sources:

set( linuxSources
	AidKit/Linux/AidKit_Linux_FileType.cpp
	AidKit/Linux/AidKit_Linux_Network.cpp
)
set( linuxLibraries magic )

# Windows Sources:

set( windowsSources
	AidKit/Windows/AidKit_Windows_Network.cpp
)

# General Sources:

set( generalSources
	AidKit/AidKit_Test.cpp
	AidKit/AidKit_Debug.cpp
	AidKit/AidKit_Network.cpp
	AidKit/AidKit_Platform.cpp
	AidKit/AidKit_Exception.cpp
#	AidKit/Function.cpp
)

# Test sources:
set( testSources
	AidKitTests/AidKit_Tests.cpp
	AidKitTests/AidKit_Debug_Test.cpp
	AidKitTests/AidKit_Network_Test.cpp
	AidKitTests/AidKit_Exception_Test.cpp
	AidKitTests/AidKit_ResourceMutex_Test.cpp
)

# Setup library build:

add_definitions( -g -W -Wall -pedantic -std=c++11 )
add_library( AidKit SHARED ${qtSources} ${boostSources} ${linuxSources} ${generalSources} )
target_link_libraries( AidKit ${qtLibraries} ${boostLibraries} ${linuxLibraries} )
if ( Qt5Widgets_FOUND )
	qt5_use_modules( AidKit Widgets )
endif()

# Setup library test build:

add_executable( aidkittests ${testSources} ${qtSources} ${boostSources} ${linuxSources} ${generalSources} )
target_link_libraries( aidkittests ${qtLibraries} ${boostLibraries} ${linuxLibraries} )
if ( Qt5Widgets_FOUND )
	qt5_use_modules( aidkittests Widgets )
endif()
