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

#pragma once

#include <pera_software/aidkit/qt/AidKit.hpp>
#include <QMainWindow>

class QSettings;

namespace pera_software {
	namespace aidkit {
		namespace qt {

			class AIDKIT_EXPORT MainWindow : public QMainWindow {
				Q_OBJECT
				public:
					MainWindow(QWidget *parent = 0);

				public slots:
					void aboutPERA();

				protected:
					virtual void doReadSettings( QSettings *settings ) = 0;
					virtual void doWriteSettings( QSettings *settings ) const = 0;

					virtual void showEvent(QShowEvent *showEvent) override;
					virtual void closeEvent(QCloseEvent *closeEvent) override;

				private:
					virtual void readSettings( QSettings *settings );
					virtual void writeSettings( QSettings *settings ) const;
			};
		}
	}
}

