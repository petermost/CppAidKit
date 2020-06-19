# Enable libstdc++ debug mode:
# See https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html for further details.
#
# These debug switches must be set globally because they influence the generated code size!

function(set_default_libstdcxx_target_options targetName)
	report("Setting default libstdc++ options for '${targetName}'")

	target_compile_definitions(${targetName}
		PUBLIC
			$<$<CONFIG:Debug>:_GLIBCXX_DEBUG$<SEMICOLON>_GLIBCXX_DEBUG_PEDANTIC>
	)
	target_compile_options(${targetName}
		PUBLIC
			$<$<CONFIG:Debug>:-U_GLIBCXX_USE_DEPRECATED>
	)
endfunction()
