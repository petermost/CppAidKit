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
#include <pera_software/aidkit/qt/core/Persistable.hpp>

class QSettings;

namespace pera_software { namespace company { namespace qt {

	class AIDKIT_API PERAMainWindow : public aidkit::qt::MainWindow, public aidkit::qt::Persistable {
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

		public Q_SLOTS:
			void aboutPERA();
			static void aboutPERA( QWidget *parent );

		protected:
			void readSettings( QSettings *settings ) noexcept override;
			void writeSettings( QSettings *settings ) const noexcept override;

		private:
			QMenu *fileMenu_ = nullptr;
			QMenu *helpMenu_ = nullptr;

			QAction *quitAction_ = nullptr;
			QAction *aboutPERAAction_ = nullptr;
			QAction *aboutQtAction_ = nullptr;
	};

} } }

