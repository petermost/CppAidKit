
# Ensure that all outputs (shared libraries, static libraries, executables, etc.) end up in the same
# directory as the executable:
# See also:
# https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#runtime-output-artifacts
# https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#library-output-artifacts
# https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#archive-output-artifacts
#
# Attention!
# If the binary directory already contains a directory with the same name as the resulting build
# target (executable) then the linker will complain: 'ld: cannot open output file .: Is a directory'
# This will most likely only happen under Linux, because executables don't get an .exe extension.
# https://stackoverflow.com/questions/38168725/cmake-trying-to-link-directory-as-an-executable-if-their-names-match

function(set_default_output_target_options targetName)
	report("Setting default output options for target '${targetName}")

	set(outputDirectory ${CMAKE_BINARY_DIR}/bin)

	set_target_properties(${targetName}
		PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${outputDirectory}
			LIBRARY_OUTPUT_DIRECTORY ${outputDirectory}
			ARCHIVE_OUTPUT_DIRECTORY ${outputDirectory}
	)

endfunction()
