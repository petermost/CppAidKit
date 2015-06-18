#include <pera_software/aidkit/qt/test/Test.hpp>
#include <QApplication>
#include <QStringList>

namespace pera_software { namespace aidkit {

using namespace qt;

int executeTests( const QStringList &arguments ) {
	Test::executeTests( arguments );
	return 0;
}

} }

int main( int argc, char *argv[] ) {

	// Q_INIT_RESOURCE( AidKitResources );
	// Q_INIT_RESOURCE( CompanyResources );

	QApplication application( argc, argv );
	QStringList arguments = application.arguments();

	// if there aren't any parameters then we want the 'silent' mode:

	if ( arguments.length() == 1 )
		arguments.append( "-silent" );

	auto result = pera_software::aidkit::executeTests( arguments );

	// Q_CLEANUP_RESOURCE( CompanyResources );
	// Q_CLEANUP_RESOURCE( AidKitResources );

	return result;
}
