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

#include "MessagesWidget.hpp"
#include <QColor>
#include <pera_software/aidkit/qt/Resources.hpp>

namespace pera_software { namespace aidkit { namespace qt {

static void showItem( QListWidget *widget, QListWidgetItem *item ) {
	widget->addItem( item );
	widget->scrollToItem( item );
}

MessagesWidget::MessagesWidget( QWidget *parent )
	: QListWidget( parent ) {
}

void MessagesWidget::showInformation( const QString &message ) {
	showItem( this, new QListWidgetItem( Resources::informationIcon(), message ));
}

void MessagesWidget::showWarning( const QString &message ) {
	showItem( this, new QListWidgetItem( Resources::warningIcon(), message ));
}

void MessagesWidget::showError( const QString &message ) {
	showItem( this, new QListWidgetItem( Resources::errorIcon(), message ));
}

void MessagesWidget::showDebug(const QString &message) {
	showItem( this, new QListWidgetItem( Resources::debugIcon(), message ));
}

} } }
