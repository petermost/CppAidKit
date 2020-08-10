function(set_default_clang_target_options targetName)
	report("Setting default clang options for target '${targetName}")

	target_compile_options(${targetName}
		PRIVATE
			-Wall -Wextra -Wpedantic
			-Weverything

			-Wno-c++98-compat -Wno-c++98-compat-pedantic #-Wno-c++98-extensions
			-Wno-c++14-compat -Wno-c++14-compat-pedantic -Wno-c++14-extensions
			-Wno-c++17-compat -Wno-c++17-compat-pedantic -Wno-c++17-extensions
			-Wno-c++20-compat -Wno-c++20-compat-pedantic -Wno-c++20-extensions
			-Wno-format-nonliteral
			-Wno-exit-time-destructors -Wno-global-constructors
			-Wno-padded
			-Wno-redundant-parens
			-Wno-covered-switch-default
			-Wno-switch-enum
			-Wno-used-but-marked-unused
			-Wno-missing-prototypes

			-pipe
	)
endfunction()
