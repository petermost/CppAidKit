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
#include <pera_software/aidkit/qt/gui/Resources.hpp>
#include <QAction>
#include <QApplication>

namespace pera_software::aidkit::qt {

using namespace std;

//==================================================================================================

const function<void()> QuitAction::DEFAULT_SLOT = &QApplication::quit;

QuitAction::QuitAction(QObject *parent)
	: QAction(parent)
{
	setText(tr("&Quit"));
	setIcon(Resources::instance().quitIcon());
	setShortcut(QKeySequence::Quit);
	setMenuRole(QAction::MenuRole::QuitRole);
}

//==================================================================================================

const function<void()> AboutQtAction::DEFAULT_SLOT = &QApplication::aboutQt;

AboutQtAction::AboutQtAction(QObject *parent)
	: QAction(parent)
{
	setText(tr("About &Qt..."));
	setMenuRole(QAction::MenuRole::AboutQtRole);
}

}
