# Set the rpath so the resulting target is 'relocatable', meaning the shared libraries in the
# current directory are being loaded:

set( CMAKE_INSTALL_RPATH "$ORIGIN" )
set( CMAKE_BUILD_WITH_INSTALL_RPATH ON )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH ON )
