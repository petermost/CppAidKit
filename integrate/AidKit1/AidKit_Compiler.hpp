#ifndef AIDKIT_COMPILER_HPP
#define AIDKIT_COMPILER_HPP

// To see the predefined symbols from GCC use cpp -dM or gcc <file> -dM -M

// Determine the compiler:

#if defined( _MSC_VER )
	#define AIDKIT_MSC
	#if _MSC_VER == 1100
		#define AIDKIT_MSC_5
	#elif _MSC_VER == 1200
		#define AIDKIT_MSC_6
	#else
		#error "Can't determine MSC compiler version!"
	#endif
#elif defined( __GNUC__ )
	#define AIDKIT_GCC
	#if __GNUC__ == 2
		#define AIDKIT_GCC_2
	#elif __GNUC__ == 3
		#define AIDKIT_GCC_3
	#else
		#error "Can't determine GCC compiler version!"
	#endif
#else
	#error "Can't determine compiler!"
#endif

// Determine the operating system:

#if defined( _WIN32 )
	#define AIDKIT_WINDOWS
#elif defined( __unix__ )
	#define AIDKIT_UNIX
	#if defined( __linux__ )
		#define AIDKIT_LINUX
	#elif defined( __FreeBSD__ )
		#define AIDKIT_BSD
	#endif
#else
	#error "Can't determine operating system!"
#endif


// Determine the processor type:

#if defined( _M_IX86 ) || defined( __i386__ )
	#define AIDKIT_I386
#endif

// Determine wether it is a debug build:

#if defined( _DEBUG ) || defined( DEBUG ) || !defined( NDEBUG )
	#define AIDKIT_DEBUG
#else
	#define AIDKIT_RELEASE
#endif

// Determine wether it is a unicode build:

#if defined( UNICODE ) || defined( _UNICODE )
	#define AIDKIT_UNICODE
#else
	#define AIDKIT_ANSICODE
#endif

// Determine wether it is a multithread build:

#if defined( _MT )
	#define AIDKIT_MULTITHREAD
#else
	#define AIDKIT_SINGLETHREAD
#endif

#endif
