function(set_default_msvc_target_options targetName)
	report("Setting default msvc options for target '${targetName}")

	# CMake appends /W3 by default, and having /W3 followed by /W4 will result in
	# cl : Command line warning D9025 : overriding '/W3' with '/W4'.  Since this is
	# a command line warning and not a compiler warning, it cannot be suppressed except
	# by fixing the command line.

	string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

	target_compile_definitions(${targetName}
		PRIVATE
			_CRT_SECURE_NO_WARNINGS
			_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
	)

	target_compile_options(${targetName}
		PRIVATE
			/W4 /permissive-

			/wd4251 # '...' needs to have dll-interface to be used by clients of class '...''
			/wd4275 # non dll-interface-class '...' used as base for dll-interface class '...'
	)
endfunction()


