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
#include <QTime>
#include <pera_software/aidkit/qt/gui/Resources.hpp>
#include <limits>

namespace pera_software::aidkit::qt {

using namespace std;

static QStandardItem *disableFeatures(QStandardItem *item) {
	item->setEditable(false);
	item->setSelectable(false);
	return item;
}

static QList<QStandardItem *> makeRowItems(const QIcon &icon, const QString &message) {
	QList<QStandardItem *> rowItems;

	rowItems.append(disableFeatures(new QStandardItem(Resources::clockIcon(), QTime::currentTime().toString())));
	rowItems.append(disableFeatures(new QStandardItem(icon, message)));

	return rowItems;
}

MessagesModel::MessagesModel( QObject *parent )
	: QStandardItemModel( parent ) {

	setHorizontalHeaderLabels(QList<QString>({tr("Time"), tr("Text")}));
}

void MessagesModel::setMaximumItemCount( int maximumItemCount ) {
	maximumItemCount_ = maximumItemCount;
}

void MessagesModel::showInformation( const QString &message ) {
	showItem( makeRowItems( Resources::informationIcon(), message ));
}

void MessagesModel::showWarning( const QString &message ) {
	showItem( makeRowItems( Resources::warningIcon(), message ));
}

void MessagesModel::showError( const QString &message ) {
	showItem( makeRowItems( Resources::errorIcon(), message ));
}

void MessagesModel::showDebug(const QString &message) {
	showItem( makeRowItems( Resources::debugIcon(), message ));
}

void MessagesModel::showItem(const QList<QStandardItem *> items ) {
	QList<QStandardItem *> rowItems;

	appendRow( items );

	if ( maximumItemCount_.has_value() ) {
		while ( rowCount() > *maximumItemCount_ )
			delete takeItem( 0 );
	}
}

}
