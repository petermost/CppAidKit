#include "AidKit_Qt_Action.hpp"

namespace PERA { namespace AidKit { namespace Qt {

Action::Action(QObject *parent)
	: QAction( parent )
{
}


Action::Action( const QString &text, QObject *parent )
	: QAction( text, parent )
{
}

Action::Action( const QIcon &icon, const QString &text, QObject *parent )
	: QAction( icon, text, parent )
{
}

} } }
