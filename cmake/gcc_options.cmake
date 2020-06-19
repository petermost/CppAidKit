function(set_default_gcc_target_options targetName)
	report("Setting default gcc options for target '${targetName}'")

	if (MINGW)
		target_compile_definitions(${targetName}
			PUBLIC
				__USE_MINGW_ANSI_STDIO
		)
	endif()

	# To see all warning switches: g++ --help=warnings

	target_compile_options(${targetName}
		PRIVATE
			-Wall -Wextra -Wpedantic -pedantic-errors    # Enable all warnings
			-Wimplicit-fallthrough
			-Wmissing-include-dirs      # Warn if a user-supplied include directory does not exist.
			-Wswitch-default
			# -Wswitch-enum
			-Wunused-parameter
			-Wunused-const-variable
			-Wuninitialized
			-Wunknown-pragmas
			-Wsuggest-final-types
			-Wsuggest-final-methods
			-Wsuggest-override          # Warn about overriding virtual functions that are not marked with the override keyword.
			-Walloc-zero
			-Walloca
			-Wduplicated-branches
			-Wduplicated-cond
			# -Wsystem-headers
			-Wtrampolines
			-Wfloat-equal
			# -Wundef                     # Warn if an undefined identifier is evaluated in an #if directive.
			-Wunused-macros
			-Wcast-qual
			-Wcast-align                # Warn whenever a pointer is cast such that the required alignment of the target is increased.
			-Wconditionally-supported
			-Wzero-as-null-pointer-constant
			-Wdangling-else
			-Wdate-time
			-Wuseless-cast
			-Wsign-conversion
			-Wfloat-conversion
			-Wlogical-op
			-Wmissing-field-initializers
			-Wpacked
			# -Wpadded
			-Winvalid-pch
			# -Wabi
			-Wctor-dtor-privacy
			-Wnoexcept
			-Wnoexcept-type
			-Wnon-virtual-dtor
			-Wold-style-cast            # Warn if an old-style (C-style) cast to a non-void type is used within a C++ program.
			-Woverloaded-virtual

			-pipe                       # Avoid temporary files, speeding up builds.
			-fdiagnostics-show-option   # Show which compiler switch caused a warning
			-pthread                    # Adds support for multithreading with the pthreads library. This option sets flags for both the preprocessor and linker
	)
endfunction()
