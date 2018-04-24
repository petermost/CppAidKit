# Show the compilers name and version:
# To see all warning switches: g++ --help=warnings

message( "C++ compiler: " ${CMAKE_CXX_COMPILER_ID} ", version: " ${CMAKE_CXX_COMPILER_VERSION})

if ( MINGW )
	add_definitions( -D__USE_MINGW_ANSI_STDIO )
endif()

# Add GCC specific switches:

add_compile_options(
	-pipe                       # Avoid temporary files, speeding up builds.
	-Wall -Wextra -Wpedantic    # Enable all warnings
	-Wmissing-include-dirs      # Warn if a user-supplied include directory does not exist.
	-Wundef                     # Warn if an undefined identifier is evaluated in an #if directive.
	-Wcast-align                # Warn whenever a pointer is cast such that the required alignment of the target is increased.
	-Wold-style-cast            # Warn if an old-style (C-style) cast to a non-void type is used within a C++ program.
	-Wsuggest-override          # Warn about overriding virtual functions that are not marked with the override keyword.

	-fvisibility=hidden         # Make symbols hidden by default i.e. must be explicitly exported
	-fdiagnostics-show-option   # Show which compiler switch caused a warning

	-pthread                    # Adds support for multithreading with the pthreads library. This option sets flags for both the preprocessor and linker
)

#if ( CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5 )
#endif()

