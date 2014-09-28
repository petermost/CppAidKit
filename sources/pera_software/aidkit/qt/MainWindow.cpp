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

#include <pera_software/aidkit/qt/MainWindow.hpp>
#include <pera_software/aidkit/qt/AboutDialog.hpp>
#include <pera_software/aidkit/qt/Images.hpp>
#include <QApplication>
#include <QSettings>

namespace pera_software { namespace aidkit { namespace qt {

const QString GROUP_NAME( "MainWindow" );
const QString SIZE_KEY( "size" );
const QString POSITION_KEY( "position" );

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle( QString( "%1 - (c) by %2 - %3" ).arg( QApplication::applicationName() )
		.arg( QApplication::organizationName() ).arg( QApplication::organizationDomain() ));

	setWindowIcon( Images[ Images::PERAIcon ] );
}



void MainWindow::showEvent( QShowEvent *showEvent )
{
	QSettings settings;
	readSettings( &settings );

	QMainWindow::showEvent( showEvent );
}



void MainWindow::closeEvent( QCloseEvent *closeEvent )
{
	QSettings settings;
	writeSettings( &settings );

	QMainWindow::closeEvent( closeEvent );
}



void MainWindow::readSettings( QSettings *settings )
{
	settings->beginGroup( GROUP_NAME );
		resize( settings->value( SIZE_KEY, size() ).toSize() );
		move( settings->value( POSITION_KEY, pos() ).toPoint() );
		doReadSettings( settings );
	settings->endGroup();
}



void MainWindow::writeSettings( QSettings *settings ) const
{
	settings->beginGroup( GROUP_NAME );
		settings->setValue( SIZE_KEY, size() );
		settings->setValue( POSITION_KEY, pos() );
		doWriteSettings( settings );
	settings->endGroup();
}

void MainWindow::aboutPERA()
{
	AboutDialog aboutPERADialog;

	aboutPERADialog.exec();
}

} } }
