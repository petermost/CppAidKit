#include "AidKit_Debug_Test.hpp"
#include "AidKit_Network_Test.hpp"
#include "AidKit_Exception_Test.hpp"
#include "AidKit_ResourceMutex_Test.hpp"
#include "../AidKit/AidKit_Test.hpp"
#include <iostream>

using namespace std;
using namespace PERA::AidKit;

int main()
{
	try {
		runDebugTests();
		runExceptionTests();
		runNetworkTests();
		runResourceMutexTests();

		return EXIT_SUCCESS;
	} catch ( AssertionException &assertionException ) {
		cout << assertionException.fileName() << "(" << assertionException.lineNumber() << ") "
				<< assertionException.functionName() << "(): Assertion '" << assertionException.expression() << "' failed!" << endl;

		return EXIT_FAILURE;
	}
}

