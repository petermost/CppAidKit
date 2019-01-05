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

namespace pera_software::aidkit::qt {

bool Resources::isThemeSupportEnabled = true;

//##################################################################################################

void Resources::enableThemeSupport() {
	isThemeSupportEnabled = true;
}

void Resources::disableThemeSupport() {
	isThemeSupportEnabled = false;
}

QIcon Resources::quitIcon() {
	return loadIcon( QStringLiteral( "application-exit" ), QStringLiteral( ":/system-shutdown-16x16.png" ));
}

QIcon Resources::debugIcon() {
	return loadIcon( QStringLiteral( ":/Debug.png" ), QStringLiteral( ":/Debug.png" ));
}

QIcon Resources::warningIcon() {
	return loadIcon( QStringLiteral( "dialog-warning" ), QStringLiteral( ":/dialog-warning-16x16.png" ));
}

QIcon Resources::informationIcon() {
	return loadIcon( QStringLiteral( "dialog-information" ), QStringLiteral( ":/dialog-information-16x16.png" ));
}

QIcon Resources::errorIcon() {
	return loadIcon( QStringLiteral( "dialog-error" ), QStringLiteral( ":/dialog-error-16x16.png" ));
}

static QIcon loadExistingIcon( const QString &iconName ) {
	Q_ASSERT( QFile::exists( iconName ));
	return QIcon( iconName );
}

QIcon Resources::loadIcon( const QString &name, const QString &alternativeName ) {
	if ( !isThemeSupportEnabled )
		return loadExistingIcon( alternativeName );
	else {
		QIcon icon = QIcon::fromTheme( name );
		if ( icon.isNull() ) {
			icon = loadExistingIcon( alternativeName );
		}
		return icon;
	}
}

}
