# To see all GCC warning switches: g++ --help=warnings
# To see all Clang switches: clang --help

function(set_default_gcc_target_options targetName)
	report("Setting default gcc options for target '${targetName}'")

	set_common_gcc_clang_target_options(${targetName})
	target_compile_options(${targetName}
		PRIVATE
			-Wcast-align=strict
			-Wcast-qual
			-Wduplicated-branches
			-Wduplicated-cond
			-Wmissing-include-dirs
			-Wnon-virtual-dtor
			-Wold-style-cast
			-Woverloaded-virtual
			-Wsuggest-override
			-Wundef
			-Wuseless-cast
	)

	if (MINGW)
		target_compile_definitions(${targetName}
			PUBLIC
				__USE_MINGW_ANSI_STDIO
		)
	endif()
endfunction()

function(set_default_clang_target_options targetName)
	report("Setting default clang options for target '${targetName}")

	set_common_gcc_clang_target_options(${targetName})
	target_compile_options(${targetName}
		PRIVATE
			-Weverything

			-Wno-c++98-compat -Wno-c++98-compat-pedantic #-Wno-c++98-extensions
			-Wno-c++14-compat #-Wno-c++14-compat-pedantic -Wno-c++14-extensions
			-Wno-c++17-compat #-Wno-c++17-compat-pedantic -Wno-c++17-extensions
			#-Wno-c++20-compat -Wno-c++20-compat-pedantic -Wno-c++20-extensions
			-Wno-covered-switch-default
			-Wno-exit-time-destructors -Wno-global-constructors
			-Wno-format-nonliteral
			-Wno-missing-prototypes
			-Wno-padded
			-Wno-redundant-parens
			-Wno-switch-enum
			-Wno-used-but-marked-unused
	)
endfunction()

function(set_common_gcc_clang_target_options targetName)
	target_compile_options(${targetName}
		PRIVATE
			-Wall -Wextra -Wpedantic

			-pipe
	)
endfunction()

# -fdiagnostics-show-option   # Show which compiler switch caused a warning
