function(report text)
	if (CMAKE_VERBOSE_MAKEFILE)
		message("-- AidKit: ${text}")
	endif()
endfunction()

function(reportMissing text)
	report("Building without '${text}', because it was not found!")
endfunction()
