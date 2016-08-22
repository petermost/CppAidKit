#include <pera_software/aidkit/qt/test/Test.hpp>
#include <QApplication>
#include <QStringList>
#include <exception>

namespace pera_software { namespace aidkit {

using namespace qt;

int executeTests( const QStringList &arguments ) {
	return Test::executeTests( arguments );
}

} }

using namespace std;

int main( int argc, char *argv[] ) {

	set_terminate( __gnu_cxx::__verbose_terminate_handler );

	QApplication application( argc, argv );
	QStringList arguments = application.arguments();

	// if there aren't any parameters then we want the 'silent' mode:
	// http://doc.qt.io/qt-5/qtest-overview.html#qt-test-command-line-arguments

	if ( arguments.length() == 1 ) {
		arguments.append( "-silent" );
	}

	auto result = pera_software::aidkit::executeTests( arguments );

	return result;
}
