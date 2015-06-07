#include <pera_software/aidkit/qt/test/Test.hpp>
#include <QApplication>
#include <QStringList>

//#include "AidKit_Network_Test.hpp"
//#include "AidKit_Exception_Test.hpp"
//#include "AidKit_ResourceMutex_Test.hpp"
//#include "../AidKit/AidKit_Test.hpp"

namespace pera_software { namespace aidkit {

using namespace qt;

int executeTests( const QStringList &arguments ) {
	Test::executeTests( arguments );
	return 0;
}

} }

int main( int argc, char *argv[] ) {

	QApplication application( argc, argv );
	QStringList arguments = application.arguments();

	// if there aren't any parameters then we want the 'silent' mode:

	if ( arguments.length() == 1 )
		arguments.append( "-silent" );

	return pera_software::aidkit::executeTests( arguments );
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
