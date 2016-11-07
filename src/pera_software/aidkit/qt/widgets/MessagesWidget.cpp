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

class MessagesWidgetItem : public QListWidgetItem {
	public:
		MessagesWidgetItem( const QIcon &icon, const QString &message )
			: QListWidgetItem( icon, message ) {
		}
};

class InformationWidgetItem : public MessagesWidgetItem {
	public:
		InformationWidgetItem( const QString &message )
			: MessagesWidgetItem( Resources::informationIcon(), message ) {
		}
};

class WarningWidgetItem : public MessagesWidgetItem {
	public:
		WarningWidgetItem( const QString &message )
			: MessagesWidgetItem( Resources::warningIcon(), message ) {
		}
};

class ErrorWidgetItem : public MessagesWidgetItem {
	public:
		ErrorWidgetItem( const QString &message )
			: MessagesWidgetItem( Resources::errorIcon(), message ) {
		}
};

class DebugWidgetItem : public MessagesWidgetItem {
	public:
		DebugWidgetItem( const QString &message )
			: MessagesWidgetItem( Resources::debugIcon(), message ) {
		}
};

static void showItem( MessagesWidget *widget, MessagesWidgetItem *item ) {
	widget->addItem( item );
	widget->scrollToItem( item );
}

MessagesWidget::MessagesWidget( QWidget *parent )
	: QListWidget( parent ) {
}

void MessagesWidget::showInformation( const QString &message ) {
	showItem( this, new InformationWidgetItem( message ));
}

void MessagesWidget::showWarning( const QString &message ) {
	showItem( this, new WarningWidgetItem( message ));
}

void MessagesWidget::showError( const QString &message ) {
	showItem( this, new ErrorWidgetItem( message ));
}

void MessagesWidget::showDebug(const QString &message) {
	showItem( this, new DebugWidgetItem( message ));
}

} } }
