#include "test_main.hpp"
#include <exception>
#include <gtest/gtest.h>
#include <pera_software/aidkit/platform.hpp>

using namespace std;
using namespace testing;

#if defined(AIDKIT_MINGW)
static void nullHandler(const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t)
{
}
#endif

int g_argc;
char **g_argv;

int main(int argc, char *argv[])
{
	printf("Running main() from %s\n", __FILE__);

	g_argc = argc;
	g_argv = argv;

#if defined(AIDKIT_GCC_STDLIB)
	set_terminate(__gnu_cxx::__verbose_terminate_handler);
#endif

#if defined(AIDKIT_MINGW)
	// Disable the invalid error handler from the msvcrt:

	_set_invalid_parameter_handler(nullHandler);
#endif

	InitGoogleTest(&g_argc, g_argv);

	return RUN_ALL_TESTS();
}
