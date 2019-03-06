# Make the 'generate_export_header' function available:

include(GenerateExportHeader)

# Hide things by default:

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# Note: It is still necessary to use call 'generate_export_header' for each target!
