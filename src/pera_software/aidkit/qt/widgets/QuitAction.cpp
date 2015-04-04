#include "QuitAction.hpp"

namespace pera_software { namespace aidkit { namespace qt {

QuitAction::QuitAction( QObject *parent )
	: QAction( parent )
{
	setText( tr( "&Quit" ));
	setShortcut( QKeySequence::Quit );

//#if defined( Q_OS_WIN )
	setIcon( QIcon( AidKit::QUIT_ICON_NAME ));
//#elif defined( Q_OS_LINUX )
//	setIcon( QIcon::fromTheme( "application-exit" ));
//#endif
}

} } }
