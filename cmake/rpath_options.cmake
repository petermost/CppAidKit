# For inspecting RPATH, RUNPATH etc.:
# - readelf -d <elffile>
# - chrpath <program>

# Enable RPATH handling:
set( CMAKE_SKIP_BUILD_RPATH  FALSE )

# If the internal 're-writing' of the rpath fails, then setting CMAKE_NO_BUILTIN_CHRPATH might help.
# See: https://cmake.org/cmake/help/latest/variable/CMAKE_NO_BUILTIN_CHRPATH.html

# 1) Add the current working directory so shared libraries in the current working directory are used.
# 2) Add the lib directory from the current working directory because the Qt plugins contain an RUNPATH of
#    '$ORIGIN/../../lib' where they expect to find the Qt libraries.
set( CMAKE_INSTALL_RPATH "$ORIGIN;$ORIGIN/lib" )

# "If this variable is set to true then the software is always built with the install path for the
# RPATH and does not need to be relinked when installed."
set( CMAKE_BUILD_WITH_INSTALL_RPATH TRUE )

# Append directories in the linker search path and outside the project to the INSTALL_RPATH.
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE )

# Sets RUNPATH to the same value as RPATH:
# Note (man ld):
# "if the linker is being invoked indirectly, via a compiler driver (e.g. gcc) then all the linker
#  command line options should be prefixed by -Wl"
set( LINKER_RUNPATH_FLAGS "-Wl,--enable-new-dtags" )
set( CMAKE_EXE_LINKER_FLAGS    "${LINKER_RUNPATH_FLAGS}" )
set( CMAKE_SHARED_LINKER_FLAGS "${LINKER_RUNPATH_FLAGS}" )

