# Define the C++ standard:

set( CMAKE_CXX_STANDARD 17 )

# Don't fall back to an earlier standard:

set( CMAKE_CXX_STANDARD_REQUIRED ON )

# Warn about C++ constructs whose meaning differs between ISO versions:

add_compile_options(
	-Wc++11-compat
	-Wc++14-compat
	-Wc++17-compat
	-Wc++1z-compat
)
