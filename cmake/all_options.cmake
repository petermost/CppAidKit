message( "CMake version: ${CMAKE_VERSION}")
# See https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html for a list of
# compiler ids.
message( "C++ compiler: " ${CMAKE_CXX_COMPILER_ID} ", version: " ${CMAKE_CXX_COMPILER_VERSION})

include( ${CMAKE_CURRENT_LIST_DIR}/cmake_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/cpp_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/gcc_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/clang_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/glibc_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/qt_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/rpath_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/output_options.cmake )

# We don't include the aidkit_options.cmake because the add_subdirectory call
# in it leads to an endless recursion!
#include( ${CMAKE_CURRENT_LIST_DIR}/aidkit_options.cmake )

