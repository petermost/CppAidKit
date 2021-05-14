include(FetchContent)

function(add_googletest_subdirectory)
	if (NOT TARGET gtest AND NOT TARGET gtest_main)
		if (EXISTS /usr/src/googletest)
			add_subdirectory(/usr/src/googletest googletest)
		else()
			message(CHECK_START "Downloading 'googletest'")
			FetchContent_Declare(googletest
				GIT_REPOSITORY https://github.com/google/googletest.git
				# GIT_TAG        release-1.10.0
				GIT_TAG        e7e591764baba0a0c3c9ad0014430e7a27331d16
			)
			FetchContent_MakeAvailable(googletest)
			message(CHECK_PASS "finished")
		endif()
		# Create the same targets/variables which FindGTest would have done:
		set(GTEST_FOUND TRUE PARENT_SCOPE)
		add_library(GTest::GTest ALIAS gtest)
		add_library(GTest::Main ALIAS gtest_main)

		# Create the targets in 'our' prefered directory:
		set_default_output_target_options(gtest)
		set_default_output_target_options(gtest_main)
	endif()
endfunction()
