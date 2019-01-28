message( "Setting MSVC options" )

# CMake appends /W3 by default, and having /W3 followed by /W4 will result in
# cl : Command line warning D9025 : overriding '/W3' with '/W4'.  Since this is
# a command line warning and not a compiler warning, it cannot be suppressed except
# by fixing the command line.

string(REGEX REPLACE " /W[0-4]" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_compile_options( /W4 )

add_definitions( -D_CRT_SECURE_NO_WARNINGS )
