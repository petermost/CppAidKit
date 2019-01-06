// Copyright 2016 Peter Most, PERA Software Solutions GmbH
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

namespace pera_software::aidkit::qt {

//==================================================================================================

MainWindow::MainWindow( QWidget *parent )
	: QMainWindow( parent ) {
}

//==================================================================================================

void MainWindow::showEvent( QShowEvent *showEvent ) {
	QMainWindow::showEvent( showEvent );

	Q_EMIT visibleChanged( true );
}

//==================================================================================================

void MainWindow::hideEvent( QHideEvent *hideEvent ) {
	QMainWindow::hideEvent( hideEvent );

	Q_EMIT visibleChanged( false );

}

//==================================================================================================

void MainWindow::closeEvent( QCloseEvent *closeEvent ) {
	QMainWindow::closeEvent( closeEvent );

	Q_EMIT closed();
}

}
