#include "AidKit_Debug_Test.hpp"
#include "../AidKit/AidKit_Debug.hpp"
#include <assert.h>

using namespace PERA::AidKit;

// To solve the bootstrapping we use std::assert:

static void testFailingAssert()
{
	try {
		AIDKIT_ASSERT( false );
		__assert( "AIDKIT_ASSERT( false ) didn't abort!", __FILE__, __LINE__ );
	} catch ( AssertionException &assertionException ) {
		// We got the expected exception so everything is fine!
	}
}

static void testSucceedingAssert()
{
	try {
		AIDKIT_ASSERT( true );
	} catch ( AssertionException &assertionException ) {
		__assert( "AIDKIT_ASSERT( true ) did abort!", __FILE__, __LINE__ );
	}
}

void runDebugTests()
{
	testFailingAssert();
	testSucceedingAssert();
}

