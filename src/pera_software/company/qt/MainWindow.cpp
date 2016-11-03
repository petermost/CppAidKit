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

#include "MainWindow.hpp"
#include "AboutDialog.hpp"
#include "Settings.hpp"
#include <pera_software/company/PERA.hpp>
#include <QString>
#include <QApplication>

namespace pera_software { namespace company { namespace qt {

using namespace pera_software::company;

const QString GROUP_NAME( QStringLiteral( "pera_software.company.qt.MainWindow" )); // Colons (':') will be replaced with %3A!
const QString SIZE_KEY( QStringLiteral( "size" ));
const QString POSITION_KEY( QStringLiteral( "position" ));

MainWindow::MainWindow( QWidget *parent )
	: QMainWindow( parent ) {

	setWindowTitle( QStringLiteral( "%1 - (c) by %2 - %3" ).arg( QApplication::applicationName() )
		.arg( QApplication::organizationName() ).arg( QApplication::organizationDomain() ));

	setWindowIcon( QIcon( PERA::ICON_NAME ));
}



void MainWindow::showEvent( QShowEvent *showEvent ) {
	Settings settings;
	readSettings( &settings );

	QMainWindow::showEvent( showEvent );
}



void MainWindow::closeEvent( QCloseEvent *closeEvent ) {
	Settings settings;
	writeSettings( &settings );

	QMainWindow::closeEvent( closeEvent );
}



void MainWindow::readSettings( Settings *settings ) {
	settings->beginGroup( GROUP_NAME );
		resize( settings->value( SIZE_KEY, size() ).toSize() );
		move( settings->value( POSITION_KEY, pos() ).toPoint() );
	settings->endGroup();
}



void MainWindow::writeSettings( Settings *settings ) const {
	settings->beginGroup( GROUP_NAME );
		settings->setValue( SIZE_KEY, size() );
		settings->setValue( POSITION_KEY, pos() );
	settings->endGroup();
}

void MainWindow::aboutPERA() {
	AboutDialog aboutPERADialog;

	aboutPERADialog.exec();
}

} } }
