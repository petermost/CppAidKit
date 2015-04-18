#include "AidKit_Exception_Test.hpp"
#include "../AidKit/AidKit_Exception.hpp"
#include "../AidKit/AidKit_Test.hpp"
#include <string>
#include <string.h>

using namespace std;
using namespace PERA::AidKit;

static void testEmptyExceptionMessage()
{
	Exception exception;

	AIDKIT_ASSERT( strcmp( exception.what(), "" ) == 0 );
}

static void testExceptionMessage()
{
	Exception exception( "exception message" );

	AIDKIT_ASSERT( strcmp( exception.what(), "exception message" ) == 0 );
}


void runExceptionTests()
{
	testEmptyExceptionMessage();
	testExceptionMessage();
}
