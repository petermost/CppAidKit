#pragma once

// To see the predefined symbols from GCC use cpp -dM or gcc <file> -dM -M

// Determine the GCC version:

#define AIDKIT_GCC_VERSION ( __GNUC__ * 100 + __GNUC_MINOR__ * 10 + __GNUC_PATCHLEVEL__ )

// Determine what kind (DEBUG|RELEASE) build it is:

#if defined( _DEBUG ) || defined( DEBUG ) || !defined( NDEBUG )
	#define AIDKIT_DEBUG
#else
	#define AIDKIT_RELEASE
#endif

// Determine the operating system:

#if defined( _WIN32 ) || defined( WIN32 )
	#define AIDKIT_WINDOWS
#elif defined( __linux__ )
	#define AIDKIT_LINUX
#else
	#error "Can't determine operating system!"
#endif
