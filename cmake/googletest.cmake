function(add_googletest_subdirectory)
	if (NOT AIDKIT_VCPKG_BUILD)
		if (EXISTS /usr/src/googletest)
			add_subdirectory(/usr/src/googletest googletest)

			# Create the same targets/variables which FindGTest would have done:
			set(GTEST_FOUND TRUE PARENT_SCOPE)
			add_library(GTest::GTest ALIAS gtest)
			add_library(GTest::Main ALIAS gtest_main)

			# Create the targets in 'our' prefered directory:
			set_default_output_target_options(gtest)
			set_default_output_target_options(gtest_main)
		endif()
	endif()
endfunction()
