function(report text)
	if (CMAKE_VERBOSE_MAKEFILE)
		message("${text}")
	endif()
endfunction()
