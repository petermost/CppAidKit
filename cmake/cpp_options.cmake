function(set_default_cpp_target_options targetName)
	message("Setting default C++ options for target '${targetName}")

	set_target_properties(${targetName}
		PROPERTIES
			# Define the C++ standard:
			CXX_STANDARD 20

			# Don't fall back to an earlier standard:
			CXX_STANDARD_REQUIRED YES

			# Don't allow C++ extension:
			CXX_EXTENSIONS OFF
	)
endfunction()
