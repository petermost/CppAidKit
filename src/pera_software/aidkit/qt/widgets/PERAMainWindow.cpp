// Copyright 2014 Peter Most, PERA Software Solutions GmbH
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

#include "PERAMainWindow.hpp"
#include "PERAAboutDialog.hpp"
#include "PERAActions.hpp"

#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QString>

#include <pera_software/aidkit/qt/widgets/Actions.hpp>
#include <pera_software/aidkit/qt/gui/PERAResources.hpp>

namespace pera_software::aidkit::qt {

template <typename A>
	static A *createActionLazily(QAction **action, const std::function<void()> &slot, QObject *parent = nullptr)
	{
		if (*action == nullptr) {
			*action = new A(parent);
			QObject::connect(*action, &QAction::triggered, slot);
		}
		return static_cast<A *>(*action);
	}

static QMenu *createMenuLazily(QMenu **menu, const QString &title, QWidget *parent)
{
	if (*menu == nullptr) {
		*menu = new QMenu(title, parent);
	}
	return *menu;
}

//==================================================================================================

PERAMainWindow::PERAMainWindow(QSharedPointer<PERASettingsStorage> settingsStorage, QWidget *parent)
	: MainWindow(parent), settingsStorage_(settingsStorage)
{
	setWindowTitle(tr("%1 - (c) by %2 - %3")
	   .arg(QApplication::applicationName())
	   .arg(QApplication::organizationName())
	   .arg(QApplication::organizationDomain()));

	// I couldn't quite figure out the difference between QApplication::setWindowIcon(), QWidget::setWindowIcon()
	// and QWindow::setIcon(), so for now we set the icon here, were it is probably most expected:

	setWindowIcon(PERAResources::instance().icon());

	settingsStorage_->readGeometry(this);
}

PERAMainWindow::~PERAMainWindow()
{
	settingsStorage_->writeGeometry(this);
}

//==================================================================================================

QMenu *PERAMainWindow::addFileMenu()
{
	fileMenu()->addAction(quitAction());

	menuBar()->addMenu(fileMenu());

	return fileMenu();
}

//==================================================================================================

QMenu *PERAMainWindow::addHelpMenu()
{
	helpMenu()->addAction(aboutPERAAction());
	helpMenu()->addAction(aboutQtAction());

	menuBar()->addMenu(helpMenu());

	return helpMenu();
}

//==================================================================================================

QMenu *PERAMainWindow::fileMenu()
{
	return createMenuLazily(&fileMenu_, tr("&File"), this);
}

//==================================================================================================

QMenu *PERAMainWindow::helpMenu()
{
	return createMenuLazily(&helpMenu_, tr("&Help"), this);
}

//==================================================================================================

QAction *PERAMainWindow::quitAction()
{
	return createActionLazily<QuitAction>(&quitAction_, QuitAction::DEFAULT_SLOT, this);
}

//==================================================================================================

QAction *PERAMainWindow::aboutPERAAction()
{
	return createActionLazily<AboutPERAAction>(&aboutPERAAction_, AboutPERAAction::DEFAULT_SLOT, this);
}

//==================================================================================================

QAction *PERAMainWindow::aboutQtAction()
{
	return createActionLazily<AboutQtAction>(&aboutQtAction_, AboutQtAction::DEFAULT_SLOT, this);
}

//==================================================================================================

void PERAMainWindow::aboutPERA()
{
	aboutPERA(this);
}

//==================================================================================================

void PERAMainWindow::aboutPERA(QWidget *parent)
{
	PERAAboutDialog aboutPERADialog(parent);

	aboutPERADialog.exec();
}

}
