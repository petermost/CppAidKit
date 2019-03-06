message( "Setting GCC options" )

if ( MINGW )
	add_definitions( -D__USE_MINGW_ANSI_STDIO )
endif()

# Add GCC specific switches:
# To see all warning switches: g++ --help=warnings

add_compile_options(
	-Wall -Wextra -Wpedantic    # Enable all warnings
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

# Enable glibc debug mode:
# See https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html for further details.

if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
	message( "Enabling glibc debug settings" )
	add_definitions( -D_GLIBCXX_DEBUG )
	add_definitions( -D_GLIBCXX_DEBUG_PEDANTIC )
#	add_definitions( -D_GLIBCXX_CONCEPT_CHECKS )
	add_definitions( -D_GLIBCXX_ASSERTIONS )
	remove_definitions( -D_GLIBCXX_USE_DEPRECATED )
endif()


#if ( CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5 )
#endif()

