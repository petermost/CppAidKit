# Make the 'generate_export_header' function available:

include(GenerateExportHeader)

# Hide things by default:
# An alternative would be: set_target_properties(<target> PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN YES)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

# Note: It is still necessary to use call 'generate_export_header' for each target!
