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

#include "MessagesModel.hpp"
#include <QColor>
#include <pera_software/aidkit/qt/Resources.hpp>
#include <limits>

namespace pera_software { namespace aidkit { namespace qt {

using namespace std;
using namespace cpp;

MessagesModel::MessagesModel( QObject *parent )
	: QStandardItemModel( parent ) {
}

void MessagesModel::setMaximumItemCount( int maximumItemCount ) {
	maximumItemCount_ = maximumItemCount;
}

void MessagesModel::showInformation( const QString &message ) {
	showItem( new QStandardItem( Resources::informationIcon(), message ));
}

void MessagesModel::showWarning( const QString &message ) {
	showItem( new QStandardItem( Resources::warningIcon(), message ));
}

void MessagesModel::showError( const QString &message ) {
	showItem( new QStandardItem( Resources::errorIcon(), message ));
}

void MessagesModel::showDebug(const QString &message) {
	showItem( new QStandardItem( Resources::debugIcon(), message ));
}

void MessagesModel::showItem( QStandardItem *item ) {
	appendRow( item );

	if ( has_value( maximumItemCount_ )) {
		while ( rowCount() > *maximumItemCount_ )
			delete takeItem( 0 );
	}
}

} } }
