# Enable glibc debug mode:
# See https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html for further details.
#
# These debug switches must be set globally because they influence the generated code size!

# message( "Enabling glibc debug settings" )
add_compile_definitions($<$<CONFIG:Debug>:_GLIBCXX_DEBUG$<SEMICOLON>_GLIBCXX_DEBUG_PEDANTIC>)
add_compile_options($<$<CONFIG:Debug>:-U_GLIBCXX_USE_DEPRECATED>)
