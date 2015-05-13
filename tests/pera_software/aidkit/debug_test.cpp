#include "debug_test.hpp"
#include <pera_software/aidkit/debug.hpp>
#include <assert.h>

// TODO Move to debug.hpp?

#if defined( AIDKIT_MINGW )
	#define FAIL( message ) _assert( message, __FILE__, __LINE__ )
#elif defined( AIDKIT_GCC )
	#define FAIL( message ) __assert( message, __FILE__, __LINE__ )
#endif

namespace pera_software { namespace aidkit {

// To solve the bootstrapping we use std::assert:
static void testFailingAssert() {
	try {
		AIDKIT_ASSERT( false );
		FAIL( "AIDKIT_ASSERT( false ) didn't abort!" );
	} catch ( assertion_exception &assertionException ) {
		// We got the expected exception so everything is fine!
	}
}

static void testSucceedingAssert() {
	try {
		AIDKIT_ASSERT( true );
	} catch ( assertion_exception &assertionException ) {
		FAIL( "AIDKIT_ASSERT( true ) did abort!" );
	}
}

void runDebugTests() {
	testFailingAssert();
	testSucceedingAssert();
}

} }

