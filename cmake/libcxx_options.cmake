# Enable libc++ debug mode:
# See https://libcxx.llvm.org/docs/DesignDocs/DebugMode.html for further details.

function(set_default_libcxx_target_options targetName)
	message("Setting default libc++ options for '${targetName}'")

	target_compile_definitions(${targetName}
		PUBLIC
			$<$<CONFIG:Debug>:_LIBCPP_DEBUG>
	)
endfunction()
