if(AIDKIT_CMAKE_MSVC)
	# CMake appends /W3 by default, and having /W3 followed by /W4 will result in
	# cl : Command line warning D9025 : overriding '/W3' with '/W4'.  Since this is
	# a command line warning and not a compiler warning, it cannot be suppressed except
	# by fixing the command line.
	#
	# This replacement must be done for the global scope and not in a function scope!

	string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
	string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

function(set_default_msvc_target_options targetName)
	report("Setting default msvc options for target '${targetName}'")

	target_compile_definitions(${targetName}
		PRIVATE
			_CRT_SECURE_NO_WARNINGS
			_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
	)

	target_compile_options(${targetName}
		PRIVATE
			-EHsc				 # Make the exception support standard conform
			-permissive-         # Make the language support standard conform
			-Zc:__cplusplus      # Enable updated __cplusplus macro
			-Zc:externConstexpr  # Enable extern constexpr variables
			-Zc:inline           # Remove unreferenced COMDAT
			-Zc:preprocessor     # Enable preprocessor conformance mode
			-Zc:referenceBinding # Don't allow non-const lvalue reference to bind to a temporary
			-Zc:rvalueCast       # Enforce type conversion rules
			-Zc:strictStrings    # Disable string literal type conversion
			-Zc:ternary          # (Enforce conditional operator rules
			-Zc:throwingNew      # Assume operator new throws

			-W4
			-wd4251 # '...' needs to have dll-interface to be used by clients of class '...''
			-wd4275 # non dll-interface-class '...' used as base for dll-interface class '...'
	)
endfunction()
