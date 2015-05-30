#include <pera_software/aidkit/qt/test/Test.hpp>
//#include "AidKit_Network_Test.hpp"
//#include "AidKit_Exception_Test.hpp"
//#include "AidKit_ResourceMutex_Test.hpp"
//#include "../AidKit/AidKit_Test.hpp"

namespace pera_software { namespace aidkit {

using namespace qt;

int executeTests() {
	Test::executeTests();
	return 0;
}

} }

int main() {
	return pera_software::aidkit::executeTests();
}

//	try {

////		runDebugTests();
////		runEnumTests();
////		runFileTests();
////		runExceptionTests();
////		runNetworkTests();
////		runResourceMutexTests();

//		return EXIT_SUCCESS;
//	} catch ( assertion_exception &assertionException ) {
//		cout << assertionException.file_name() << "(" << assertionException.line_number() << ") "
//				<< assertionException.function_name() << "(): Assertion '" << assertionException.expression() << "' failed!" << endl;

//		return EXIT_FAILURE;
//	}
