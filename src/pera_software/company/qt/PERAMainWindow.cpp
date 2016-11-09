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
#include "Settings.hpp"

#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QApplication>

#include <pera_software/company/PERA.hpp>
#include <pera_software/aidkit/qt/widgets/QuitAction.hpp>

namespace pera_software { namespace company { namespace qt {

using namespace aidkit::qt;

const QString GROUP_NAME( QStringLiteral( "pera_software.company.qt.PERAMainWindow" )); // Colons (':') will be replaced with %3A!
const QString SIZE_KEY( QStringLiteral( "size" ));
const QString POSITION_KEY( QStringLiteral( "position" ));

//==================================================================================================

PERAMainWindow::PERAMainWindow( QWidget *parent )
	: MainWindow( parent ) {

	setWindowTitle( tr( "%1 - (c) by %2 - %3" )
		.arg( QApplication::applicationName() )
		.arg( QApplication::organizationName() )
		.arg( QApplication::organizationDomain() ));

	connect( this, &MainWindow::showed, this, &PERAMainWindow::onShowed );
	connect( this, &MainWindow::closed, this, &PERAMainWindow::onClosed );

	// Default window icon is set in Application::Application().
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

	menuBar()->addMenu( helpMenu_ );

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
		quitAction_ = new QuitAction( this );
		connect( quitAction_, &QAction::triggered, this, &PERAMainWindow::close );
	}
	return quitAction_;
}

//==================================================================================================

QAction *PERAMainWindow::aboutPERAAction() {
	if ( aboutPERAAction_ == nullptr ) {
		aboutPERAAction_ = new QAction( tr( "&About &PERA..." ), this );
		connect( aboutPERAAction_, &QAction::triggered, this, &PERAMainWindow::aboutPERA );
	}
	return aboutPERAAction_;
}

//==================================================================================================

QAction *PERAMainWindow::aboutQtAction() {
	if ( aboutQtAction_ == nullptr ) {
		aboutQtAction_ = new QAction( tr( "About &Qt..." ), this );
		connect( aboutQtAction_, &QAction::triggered, &QApplication::aboutQt );
	}
	return aboutQtAction_;
}


//==================================================================================================

void PERAMainWindow::onShowed() {
	Settings settings;
	readSettings( &settings );
}

//==================================================================================================

void PERAMainWindow::onClosed() {
	Settings settings;
	writeSettings( &settings );
}

//==================================================================================================

void PERAMainWindow::readSettings( Settings *settings ) {
	settings->beginGroup( GROUP_NAME );
		resize( settings->value( SIZE_KEY, size() ).toSize() );
		move( settings->value( POSITION_KEY, pos() ).toPoint() );
	settings->endGroup();
}

//==================================================================================================

void PERAMainWindow::writeSettings( Settings *settings ) const {
	settings->beginGroup( GROUP_NAME );
		settings->setValue( SIZE_KEY, size() );
		settings->setValue( POSITION_KEY, pos() );
	settings->endGroup();
}
//==================================================================================================

void PERAMainWindow::aboutPERA() {
	PERAAboutDialog aboutPERADialog;

	aboutPERADialog.exec();
}


} } }
