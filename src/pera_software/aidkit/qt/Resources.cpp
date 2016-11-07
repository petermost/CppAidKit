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

#undef NO_THEME_SUPPORT

namespace pera_software { namespace aidkit { namespace qt {

static QIcon loadIcon( const QString &iconName ) {
	Q_ASSERT( QFile::exists( iconName ));
	return QIcon( iconName );
}

static QIcon loadThemeIcon( const QString &name, const QString &alternativeName ) {
	#if defined( NO_THEME_SUPPORT )
		return loadIcon( fallbackName );
	#else
		QIcon icon = QIcon::fromTheme( name );
		if ( icon.isNull() ) {
			icon = loadIcon( alternativeName );
		}
		return icon;
	#endif
}


QIcon Resources::quitIcon() {
	return loadThemeIcon( QStringLiteral( "application-exit" ), QStringLiteral( ":/system-shutdown-16x16.png" ));
}

QIcon Resources::debugIcon() {
	return loadIcon( QStringLiteral( ":/Debug.png" ));
}

QIcon Resources::warningIcon() {
	return loadThemeIcon( QStringLiteral( "dialog-warning" ), QStringLiteral( ":/dialog-warning-16x16.png" ));
}

QIcon Resources::informationIcon() {
	return loadThemeIcon( QStringLiteral( "dialog-information" ), QStringLiteral( ":/dialog-information-16x16.png" ));
}

QIcon Resources::errorIcon() {
	return loadThemeIcon( QStringLiteral( "dialog-error" ), QStringLiteral( ":/dialog-error-16x16.png" ));
}

} } }
