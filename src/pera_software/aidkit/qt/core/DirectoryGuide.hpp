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

#include <QObject>
#include <pera_software/aidkit/aidkit.hpp>

class QString;
class QFileInfo;

namespace pera_software { namespace aidkit { namespace qt {

	class AIDKIT_API DirectoryGuide : public QObject {
		Q_OBJECT
		public:
			explicit DirectoryGuide( QObject *parent = nullptr );
			void walk( const QFileInfo &parentDirectory, class DirectoryVisitor *visitor );

		signals:
			// We could have used signals here, but signals can't return a value and so the
			// feature to cancel the directory walking wouldn't have been possible.

		public slots:
	};

	class AIDKIT_API DirectoryVisitor : public QObject {
		Q_OBJECT
		public:
			explicit DirectoryVisitor( QObject *parent = nullptr );
			virtual ~DirectoryVisitor();

		protected:
			friend DirectoryGuide;

			virtual bool visitDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory );
			virtual bool visitFile( const QFileInfo &parentDirectory, const QFileInfo &currentFile );
			virtual bool leaveDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory );
	};

} } }
