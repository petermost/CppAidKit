#include "debug_test.hpp"
#include "enum_class_test.hpp"
#include "io/file_test.hpp"
#include <pera_software/aidkit/debug.hpp>
#include <pera_software/aidkit/qt/test/Test.hpp>
#include <QTest>
#include <QGlobalStatic>
//#include "AidKit_Network_Test.hpp"
//#include "AidKit_Exception_Test.hpp"
//#include "AidKit_ResourceMutex_Test.hpp"
//#include "../AidKit/AidKit_Test.hpp"
#include <iostream>

namespace pera_software { namespace aidkit {

using namespace std;
using namespace io;
using namespace qt;

int executeTests() {
	Test::executeTests();
	return 0;
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

}

} }


int main() {
	return pera_software::aidkit::executeTests();
}
