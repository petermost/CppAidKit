#include <exception>
#include <gtest/gtest.h>
#include <pera_software/aidkit/aidkit.hpp>
#include <pera_software/aidkit/main.hpp>
#include <pera_software/aidkit/platform.hpp>
#if defined(AIDKIT_MSVC)
	#include <io.h>
	#include <windows.h>
#endif

using namespace std;
using namespace filesystem;
using namespace testing;
using namespace pera_software::aidkit;

static void enableVerboseTerminateHandler()
{
#if defined(AIDKIT_GCC_LIB)
	set_terminate(__gnu_cxx::__verbose_terminate_handler);
#endif
}

#if defined(AIDKIT_MSVC_LIB)
static void nullInvalidParameterHandler(const wchar_t * /* expression */, const wchar_t * /* function */,
	const wchar_t * /* file */, unsigned int /* line */, uintptr_t /* pReserved */)
{
}
#endif


static void disableInvalidParameterHandler()
{
#if defined(AIDKIT_MSVC_LIB)
	_set_invalid_parameter_handler(nullInvalidParameterHandler);
#endif
}

// The 'FileTest.testOpenReadWrite' leads to the assertion:
// "minkernel\crts\ucrt\inc\corecrt_internal_stdio.h(690) : Assertion failed: ("Invalid file open mode", 0)"
// Trying to get rid of this message with:
// _CrtSetReportMode(_CRT_WARN, 0);
// _CrtSetReportMode(_CRT_ERROR, 0);
// _CrtSetReportMode(_CRT_ASSERT, 0);

// _CrtSetReportFile(_CRT_WARN, nullFile);
// _CrtSetReportFile(_CRT_ERROR, nullFile);
// _CrtSetReportFile(_CRT_ASSERT, nullFile);
// didn't help.

extern "C" exit_result aidkit_main(path name, vector<string> arguments /*, vector<pair<string, string>> environment */)
{
	printf("Running main() from %s\n", __FILE__);

	InitGoogleTest(&g_argc, g_argv);

	enableVerboseTerminateHandler();
	disableInvalidParameterHandler();

	return static_cast<exit_result>(RUN_ALL_TESTS());
}
