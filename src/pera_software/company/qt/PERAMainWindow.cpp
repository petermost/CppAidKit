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

#include <pera_software/company/PERA.hpp>
#include <pera_software/aidkit/qt/widgets/Actions.hpp>
#include <pera_software/aidkit/qt/widgets/Widgets.hpp>

namespace pera_software { namespace company { namespace qt {

using namespace aidkit::qt;

//==================================================================================================

PERAMainWindow::PERAMainWindow( QWidget *parent )
	: MainWindow( parent ) {

	setWindowTitle( tr( "%1 - (c) by %2 - %3" )
		.arg( QApplication::applicationName() )
		.arg( QApplication::organizationName() )
		.arg( QApplication::organizationDomain() ));

	// I couldn't quite figure out the difference between QApplication::setWindowIcon(), QWidget::setWindowIcon()
	// and QWindow::setIcon(), so for now we set the icon here, were it is probably most expected:

	setWindowIcon( QIcon( PERA::ICON_NAME ));
}

//==================================================================================================

QMenu *PERAMainWindow::addFileMenu() {
	fileMenu()->addAction( quitAction() );

	menuBar()->addMenu( fileMenu() );

	return fileMenu();
}

//==================================================================================================

QMenu *PERAMainWindow::addHelpMenu() {
	helpMenu()->addAction( aboutPERAAction() );
	helpMenu()->addAction( aboutQtAction() );

	menuBar()->addMenu( helpMenu() );

	return helpMenu();
}

//==================================================================================================

QMenu *PERAMainWindow::fileMenu() {
	if ( fileMenu_ == nullptr ) {
		fileMenu_ = new QMenu( tr( "&File" ), this );
	}
	return fileMenu_;
}

//==================================================================================================

QMenu *PERAMainWindow::helpMenu() {
	if ( helpMenu_ == nullptr ) {
		helpMenu_ = new QMenu( tr( "&Help" ));
	}
	return helpMenu_;
}

//==================================================================================================

QAction *PERAMainWindow::quitAction() {
	if ( quitAction_ == nullptr ) {
		quitAction_ = Actions::create< QuitAction >( this, QuitAction::DEFAULT_SLOT );
	}
	return quitAction_;
}

//==================================================================================================

QAction *PERAMainWindow::aboutPERAAction() {
	if ( aboutPERAAction_ == nullptr ) {
		aboutPERAAction_ = Actions::create< AboutPERAAction >( this, AboutPERAAction::DEFAULT_SLOT );
	}
	return aboutPERAAction_;
}

//==================================================================================================

QAction *PERAMainWindow::aboutQtAction() {
	if ( aboutQtAction_ == nullptr ) {
		aboutQtAction_ = Actions::create< AboutQtAction >( this, AboutQtAction::DEFAULT_SLOT );
	}
	return aboutQtAction_;
}

//==================================================================================================

void PERAMainWindow::readSettings( QSettings *settings ) noexcept {
	Widgets::readGeometry(this, settings);
}

//==================================================================================================

void PERAMainWindow::writeSettings( QSettings *settings ) const noexcept {
	Widgets::writeGeometry(this, settings);
}

//==================================================================================================

void PERAMainWindow::aboutPERA() {
	aboutPERA( this );
}

//==================================================================================================

void PERAMainWindow::aboutPERA( QWidget *parent ) {
	PERAAboutDialog aboutPERADialog( parent );

	aboutPERADialog.exec();
}


} } }
