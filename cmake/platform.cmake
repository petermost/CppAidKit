# Detect which compiler is in use:

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(AIDKIT_CMAKE_GCC TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(AIDKIT_CMAKE_CLANG TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(AIDKIT_CMAKE_MSVC TRUE)
else()
	message(AUTHOR_WARNING "Unknown C++ compiler: CMAKE_CXX_COMPILER_ID: '${CMAKE_CXX_COMPILER_ID}', CMAKE_CXX_COMPILER_VERSION: '${CMAKE_CXX_COMPILER_VERSION}'")
endif()

# Detect which operating system is in use:

if (UNIX)
	set(AIDKIT_CMAKE_UNIX TRUE)
	set(AIDKIT_CMAKE_LINUX TRUE)
elseif(WIN32)
	set(AIDKIT_WINDOWS TRUE)
else()
	message(AUTHOR_WARNING "Unknown operating system: CMAKE_SYSTEM: '${CMAKE_SYSTEM}'")
endif()
