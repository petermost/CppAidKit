function(set_default_cpp_target_options targetName)
	report("Setting default C++ options for target '${targetName}")

	target_compile_features(${targetName}
		PRIVATE
			cxx_std_20
	)
	set_target_properties(${targetName}
		PROPERTIES
			# Don't allow C++ extension:
			CXX_EXTENSIONS OFF
	)
endfunction()
