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

#pragma once

#include <pera_software/aidkit/aidkit.hpp>
#include <QStandardItemModel>
#include <optional>

namespace pera_software::aidkit::qt {

	class AIDKIT_API MessagesModel : public QStandardItemModel {
		Q_OBJECT
		public:
			explicit MessagesModel( QObject *parent = nullptr );

			void setMaximumItemCount( int maximumItemCount );

			void showInformation( const QString &message );
			void showWarning( const QString &message );
			void showError( const QString &message );
			void showDebug( const QString &message );

		private:
			void showItem(const QList<QStandardItem *> &items);

			std::optional< int > maximumItemCount_;
	};

}
