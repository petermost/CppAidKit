// Copyright 2017 Peter Most, PERA Software Solutions GmbH
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

#include "Widgets.hpp"
#include <QWidget>
#include <QSettings>

namespace pera_software { namespace aidkit { namespace qt {

// Colons (':') would be stored as %3A so we replace them with a dot ('.'):

static const QLatin1Literal COLONS( "::" );
static const QLatin1Literal DOT( "." );

static const QString SIZE_KEY( QStringLiteral( "size" ));
static const QString POSITION_KEY( QStringLiteral( "position" ));

QString Widgets::makeGroupName(const QObject *object) {
	return QString( object->metaObject()->className() ).replace( COLONS, DOT );
}

void Widgets::readGeometry(QWidget *widget, QSettings *settings) noexcept {
	settings->beginGroup( makeGroupName( widget ));
		widget->resize( settings->value( SIZE_KEY, widget->size() ).toSize() );
		widget->move( settings->value( POSITION_KEY, widget->pos() ).toPoint() );
	settings->endGroup();
}

void Widgets::writeGeometry(const QWidget *widget, QSettings *settings) noexcept {
	settings->beginGroup( makeGroupName( widget ));
		settings->setValue( SIZE_KEY, widget->size() );
		settings->setValue( POSITION_KEY, widget->pos() );
	settings->endGroup();
}

} } }
