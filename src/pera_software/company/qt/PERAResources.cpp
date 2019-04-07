// Copyright 2019 Peter Most, PERA Software Solutions GmbH
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

#include "PERAResources.hpp"
#include <QString>
#include <QFile>
#include <QIcon>

namespace pera_software::company::qt {

using namespace aidkit::qt;

static const QString PREFIX(QStringLiteral(":/pera_software/company/resources/"));

static QString prependPrefix(const QString &iconName) {
	return PREFIX + iconName;
}

QIcon PERAResources::icon() {
	return loadIcon(prependPrefix(QStringLiteral("Icon.png")));
}

QPixmap PERAResources::logo() {
	return QPixmap(prependPrefix(QStringLiteral("Logo.png")));
}

}
