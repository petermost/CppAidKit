function(set_default_qt_target_options targetName)
	message("Setting default Qt options for target '${targetName}")

	target_compile_definitions(${targetName}
		PRIVATE
			# If this macro is defined, the compiler will generate warnings if API declared as deprecated by Qt
			# is used.
			QT_DEPRECATED_WARNINGS

			# This macro can be defined in the project file to disable functions deprecated in a specified
			# version of Qt or any earlier version.
			QT_DISABLE_DEPRECATED_BEFORE=0x000000
	)
	# Get rid of compile warning: 'warning: empty expression statement has no effect; remove unnecessary ';' to silence this warning [-Wextra-semi-stmt]
	# https://bugreports.qt.io/browse/QTBUG-82978 "Allow "-Wextra-semi-stmt" on Q_UNUSED"
	# According to the comments in the bugreport, this will not be fixed before Qt6.
	if (Qt5Core_VERSION VERSION_LESS 6)
		set_source_files_properties("${targetName}_autogen/mocs_compilation.cpp"
			PROPERTIES
				COMPILE_OPTIONS "-Wno-extra-semi-stmt"
		)
	endif()
endfunction()

# Enable C++17 support:

#if ( ${CMAKE_VERSION} VERSION_LESS 3.8.0 )
#	# From https://gitlab.kitware.com/cmake/cmake/issues/16468
#	find_package( Qt5Core )
#	if ( Qt5Core_FOUND )
#		# get_property( propertyValue TARGET Qt5::Core PROPERTY INTERFACE_COMPILE_FEATURES )
#		# message( "Property: ${propertyValue}" )
#		set_property( TARGET Qt5::Core PROPERTY INTERFACE_COMPILE_FEATURES "" )
#		add_compile_options( -std=gnu++1z )
#	endif()
#else()
#	message( FATAL_ERROR "Remove missing cmake C++17 support workaround!" )
#endif()
