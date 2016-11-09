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

#include <pera_software/aidkit/aidkit.hpp>
#include <pera_software/aidkit/qt/widgets/MainWindow.hpp>

namespace pera_software { namespace aidkit { namespace qt {
	class IniSettings;
} } }

namespace pera_software { namespace company { namespace qt {

	class AIDKIT_API PERAMainWindow : public aidkit::qt::MainWindow {
		Q_OBJECT
		public:
			PERAMainWindow( QWidget *parent = nullptr );

			QMenu *addFileMenu();
			QMenu *addHelpMenu();

			QMenu *fileMenu();
			QMenu *helpMenu();

			QAction *quitAction();
			QAction *aboutPERAAction();
			QAction *aboutQtAction();

			virtual void readSettings( aidkit::qt::IniSettings *settings );
			virtual void writeSettings( aidkit::qt::IniSettings *settings ) const;

		public slots:
			void aboutPERA();

		private slots:
			void onShowed();
			void onClosed();

		private:
			QMenu *fileMenu_ = nullptr;
			QMenu *helpMenu_ = nullptr;

			QAction *quitAction_ = nullptr;
			QAction *aboutPERAAction_ = nullptr;
			QAction *aboutQtAction_ = nullptr;
	};

} } }

