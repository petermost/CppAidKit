include( ${CMAKE_CURRENT_LIST_DIR}/cmake_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/cpp_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/gcc_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/glibc_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/qt_options.cmake )
include( ${CMAKE_CURRENT_LIST_DIR}/rpath_options.cmake )

# We don't include the aidkit_options.cmake because the add_subdirectory call
# in it leads to an endless recursion!
#include( ${CMAKE_CURRENT_LIST_DIR}/aidkit_options.cmake )

