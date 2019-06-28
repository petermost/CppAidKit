# Enable glibc debug mode:
# See https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html for further details.
#
# These debug switches must be set globally because they influence the generated code size!

function(set_default_libstdcxx_options)
	message("Setting default libstdc++ options for all targets")

	add_compile_definitions($<$<CONFIG:Debug>:_GLIBCXX_DEBUG$<SEMICOLON>_GLIBCXX_DEBUG_PEDANTIC>)
	add_compile_options($<$<CONFIG:Debug>:-U_GLIBCXX_USE_DEPRECATED>)
endfunction()
