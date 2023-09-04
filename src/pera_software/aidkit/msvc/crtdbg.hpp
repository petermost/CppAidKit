#pragma once

#include <crtdbg.h>

#if defined(_DEBUG) && defined(_CRTDBG_MAP_ALLOC)
	#define NEW_DBG new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new NEW_DBG

	#ifndef malloc
		#error malloc macro not defined!
	#endif

	#ifndef calloc
		#error calloc macro not defined!
	#endif

	#ifndef realloc
		#error realloc macro not defined!
	#endif

	#ifndef free
		#error free macro not defined!
	#endif

#endif

