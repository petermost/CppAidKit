function(add_googletest_subdirectory)
	if (EXISTS /usr/src/googletest)
		if (NOT TARGET gtest AND NOT TARGET gtest_main)
			add_subdirectory(/usr/src/googletest googletest)
		endif()
		# Create the same targets/variables which FindGTest would have done:
		set(GTEST_FOUND TRUE PARENT_SCOPE)
		add_library(GTest::GTest ALIAS gtest)
		add_library(GTest::Main ALIAS gtest_main)
	else()
		include(FetchContent)
		FetchContent_Declare(googletest
			GIT_REPOSITORY https://github.com/google/googletest.git
			GIT_TAG        release-1.10.0
		)
		FetchContent_MakeAvailable(googletest)
		if (NOT TARGET gtest AND NOT TARGET gtest_main)
			add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
		endif()
		# Create the same targets/variables which FindGTest would have done:
		set(GTEST_FOUND TRUE PARENT_SCOPE)
		add_library(GTest::GTest ALIAS gtest)
		add_library(GTest::Main ALIAS gtest_main)
	endif()
endfunction()
