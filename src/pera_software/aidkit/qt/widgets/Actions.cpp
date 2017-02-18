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

using namespace ::std;

const function< void() > Actions::DEFAULT_QUIT_SLOT = &QApplication::quit;
const function< void() > Actions::DEFAULT_ABOUT_QT_SLOT = &QApplication::aboutQt;

//==================================================================================================

QAction *Actions::quitAction(QObject *parent, function< void() > slot ) {
	QAction *action = new QAction( parent );
	action->setText( QObject::tr( "&Quit" ));
	action->setIcon( Resources::quitIcon() );
	action->setShortcut( QKeySequence::Quit );
	action->setMenuRole( QAction::MenuRole::QuitRole );

	if ( slot )
		QObject::connect( action, &QAction::triggered, slot );

	return action;
}

//==================================================================================================

QAction *Actions::aboutQtAction( QObject *parent, function< void()> slot ) {
	QAction *action = new QAction( parent );
	action->setText( QObject::tr( "About &Qt..." ));
	action->setMenuRole( QAction::MenuRole::AboutQtRole );

	if ( slot )
		QObject::connect( action, &QAction::triggered, slot );

	return action;
}

} } }
