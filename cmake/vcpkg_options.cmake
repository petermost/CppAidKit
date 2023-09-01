# AIDKIT_VCPKG_BUILD is set in platform.cmake

if (AIDKIT_VCPKG_BUILD)
	# A condition in the 'CMakePresets.json' would be prefered, but seems not possible
	if (UNIX)
		set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "Target triplet for Linux")
	elseif(WIN32)
		set(VCPKG_TARGET_TRIPLET "x64-windows-static-md" CACHE STRING "Target triplet for Windows")
	endif()
endif()
