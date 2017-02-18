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

#include "PERAActions.hpp"
#include "PERAApplication.hpp"
#include <QAction>

namespace pera_software { namespace company { namespace qt {

using namespace ::std;

const function< void() > PERAActions::DEFAULT_ABOUT_PERA_SLOT = &PERAApplication::aboutPERA;

QAction *PERAActions::aboutPERAAction( QObject *parent, function< void() > slot ) {
	QAction *action = new QAction( parent );
	action->setText( QObject::tr( "&About &PERA..." ));
	action->setMenuRole( QAction::MenuRole::AboutRole );

	if ( slot )
		QObject::connect( action, &QAction::triggered, slot );

	return action;
}

} } }
