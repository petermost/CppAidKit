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

#include "Resources.hpp"
#include <QString>
#include <QFile>
#include <QIcon>

namespace pera_software { namespace aidkit { namespace qt {

static const QString QUIT_ICON_NAME( QStringLiteral( ":/system-shutdown-16x16.png" ));

static const QString DEBUG_ICON_NAME( QStringLiteral( ":/Debug.png" ));
static const QString WARNING_ICON_NAME( QStringLiteral( ":/dialog-warning-16x16.png" ));
static const QString INFORMATION_ICON_NAME( QStringLiteral( ":/dialog-information-16x16.png" ));
static const QString ERROR_ICON_NAME( QStringLiteral( ":/dialog-error-16x16.png" ));

static QIcon loadIcon( const QString &iconName ) {
	Q_ASSERT( QFile::exists( iconName ));
	return QIcon( iconName );
}

QIcon Resources::quitIcon() {
	return QIcon::fromTheme( "application-exit", loadIcon( QUIT_ICON_NAME ));
}

QIcon Resources::debugIcon() {
	return loadIcon( DEBUG_ICON_NAME );
}

QIcon Resources::warningIcon() {
	return QIcon::fromTheme( "dialog-warning", loadIcon( WARNING_ICON_NAME ));
}

QIcon Resources::informationIcon() {
	return QIcon::fromTheme( "dialog-information", loadIcon( INFORMATION_ICON_NAME ));
}

QIcon Resources::errorIcon() {
	return QIcon::fromTheme( "dialog-error", loadIcon( ERROR_ICON_NAME ));
}

} } }
