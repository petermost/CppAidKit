set(CMAKE_TOOLCHAIN_FILE vcpkg/scripts/buildsystems/vcpkg.cmake CACHE FILEPATH "Path to vcpkg submodule" FORCE)
if (UNIX)
	set(VCPKG_HOST_TRIPLET "x64-linux" CACHE STRING "Host triplet for Linux" FORCE)
else()
	set(VCPKG_HOST_TRIPLET "x64-windows-static" CACHE STRING "Host triplet for Windows" FORCE)
endif()
