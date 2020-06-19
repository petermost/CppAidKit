function(set_default_cmake_options)
	report("Setting default cmake options")

	set(CMAKE_WARN_DEPRECATED ON)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

	if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
		report("Enabling debug build" )
		set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type" FORCE)
		# Present a combobox in the cmake-gui (https://blog.kitware.com/cmake-and-the-default-build-type/):
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
	endif()
endfunction()
