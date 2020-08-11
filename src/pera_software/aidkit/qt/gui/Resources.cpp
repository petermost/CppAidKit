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
#include <pera_software/aidkit/qt/core/Strings.hpp>
#include <QFile>
#include <QIcon>

// The icons are from 'Oxygen'.

static inline void initResource()
{
	Q_INIT_RESOURCE(AidKitResources);
}

static inline void cleanupResource()
{
	Q_CLEANUP_RESOURCE(AidKitResources);
}

namespace pera_software::aidkit::qt {

#define PREFIX ":/pera_software/aidkit/resources/"

QIcon loadIcon(const QString &iconName)
{
	if (QFile::exists(iconName))
		return QIcon(iconName);
	else
		return QIcon();
}

Resources Resources::instance_;

Resources &Resources::instance()
{
	return instance_;
}

Resources::Resources()
{
	initResource();
}

Resources::~Resources()
{
	cleanupResource();
}


QIcon Resources::quitIcon()
{
	return loadIcon(PREFIX "system-shutdown-16x16.png"_qs);
}

QIcon Resources::debugIcon()
{
	return loadIcon(PREFIX "Debug.png"_qs);
}

QIcon Resources::warningIcon()
{
	return loadIcon(PREFIX "dialog-warning-16x16.png"_qs);
}

QIcon Resources::informationIcon()
{
	return loadIcon(PREFIX "dialog-information-16x16.png"_qs);
}

QIcon Resources::errorIcon()
{
	return loadIcon(PREFIX "dialog-error-16x16.png"_qs);
}

QIcon Resources::clockIcon()
{
	return loadIcon(PREFIX "clock-16x16.png"_qs);
}

QIcon Resources::settingsIcon()
{
	return loadIcon(PREFIX "configure-16x16.png"_qs);
}


}
