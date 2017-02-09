// Copyright 2017 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#include "Actions.hpp"
#include <pera_software/aidkit/qt/Resources.hpp>
#include <QAction>
#include <QApplication>

namespace pera_software { namespace aidkit { namespace qt {

QAction *Actions::quitAction( QObject *parent, SlotConnection connection ) {
	QAction *action = new QAction( parent );
	action->setText( QObject::tr( "&Quit" ));
	action->setIcon( Resources::quitIcon() );
	action->setShortcut( QKeySequence::Quit );
	action->setMenuRole( QAction::MenuRole::QuitRole );

	if ( connection == SlotConnection::Default )
		QObject::connect( action, &QAction::triggered, &QApplication::quit );

	return action;
}


QAction *Actions::aboutQtAction(QObject *parent, SlotConnection connection ) {
	QAction *action = new QAction( parent );
	action->setText( QObject::tr( "About &Qt..." ));
	action->setMenuRole( QAction::MenuRole::AboutQtRole );

	if ( connection == SlotConnection::Default )
		QObject::connect( action, &QAction::triggered, &QApplication::aboutQt );

	return action;
}

} } }
