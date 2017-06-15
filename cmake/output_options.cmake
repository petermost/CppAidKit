# Ensure that all outputs (shared libraries, static libraries, executables, etc.) end up in the same
# directory as the executable:
# See also:
# https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#runtime-output-artifacts
# https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#library-output-artifacts
# https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#archive-output-artifacts

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
