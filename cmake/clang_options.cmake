# Show the compilers name and version:
# To see all warning switches: g++ --help=warnings

if( CMAKE_CXX_COMPILER_ID STREQUAL "Clang" )
	message( "Setting Clang options" )

	# Add Clang specific switches:

	add_compile_options(
		-W -Wall -Wextra -Wpedantic
		-Weverything

		-Wno-c++98-compat -Wno-c++98-compat-pedantic
		-Wno-format-nonliteral
		-Wno-exit-time-destructors -Wno-global-constructors
		-Wno-padded
		-Wno-redundant-parens
		-Wno-covered-switch-default
		-Wno-switch-enum
		-Wno-used-but-marked-unused
	)
endif()

