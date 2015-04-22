#include "debug_test.hpp"
#include <pera_software/aidkit/debug.hpp>
#include <assert.h>

namespace pera_software { namespace aidkit {

// To solve the bootstrapping we use std::assert:

static void testFailingAssert() {
	try {
		AIDKIT_ASSERT( false );
		__assert( "AIDKIT_ASSERT( false ) didn't abort!", __FILE__, __LINE__ );
	} catch ( assertion_exception &assertionException ) {
		// We got the expected exception so everything is fine!
	}
}

static void testSucceedingAssert() {
	try {
		AIDKIT_ASSERT( true );
	} catch ( assertion_exception &assertionException ) {
		__assert( "AIDKIT_ASSERT( true ) did abort!", __FILE__, __LINE__ );
	}
}

void runDebugTests() {
	testFailingAssert();
	testSucceedingAssert();
}

} }

