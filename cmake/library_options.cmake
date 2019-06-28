function(set_default_library_target_options targetName)
	message("Setting default library options for target '${targetName}'")

	# Hide symbols by default:
	set_target_properties(${targetName}
		PROPERTIES
			CXX_VISIBILITY_PRESET hidden
			VISIBILITY_INLINES_HIDDEN YES
	)
endfunction()
