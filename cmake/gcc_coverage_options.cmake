set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

function(set_default_gcc_code_coverage_options targetName)
	report("Setting default code coverage options for target '${targetName}'")

	target_compile_options(${targetName}
		PUBLIC
			--coverage # synonym for -fprofile-arcs -ftest-coverage
	)
	target_link_options(${targetName}
		PUBLIC
			--coverage # synonym for -lgcov
	)
endfunction()
