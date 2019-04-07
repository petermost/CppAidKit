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

// The icons are from 'Oxygen'.

namespace pera_software::aidkit::qt {

static const QString PREFIX(QStringLiteral(":/pera_software/aidkit/resources/"));

static QIcon loadIcon(const QString &iconName) {
	return QIcon(PREFIX + iconName);
}

QIcon Resources::quitIcon() {
	return loadIcon(QStringLiteral("system-shutdown-16x16.png"));
}

QIcon Resources::debugIcon() {
	return loadIcon(QStringLiteral("Debug.png"));
}

QIcon Resources::warningIcon() {
	return loadIcon(QStringLiteral("dialog-warning-16x16.png"));
}

QIcon Resources::informationIcon() {
	return loadIcon(QStringLiteral("dialog-information-16x16.png"));
}

QIcon Resources::errorIcon() {
	return loadIcon(QStringLiteral("dialog-error-16x16.png"));
}

QIcon Resources::clockIcon() {
	return loadIcon(QStringLiteral("clock-16x16.png"));
}


}
