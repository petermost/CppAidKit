# Setup aidkit usage

add_subdirectory( ../CppAidKit ./CppAidKitBuildFiles )
include_directories( ../CppAidKit/src/ )
link_directories( ./CppAidKitBuildFiles )

