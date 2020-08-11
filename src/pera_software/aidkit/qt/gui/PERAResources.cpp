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
#include <pera_software/aidkit/qt/core/Strings.hpp>
#include <pera_software/aidkit/qt/gui/Resources.hpp>
#include <QIcon>

static inline void initResource()
{
	Q_INIT_RESOURCE(PERAResources);
}

static inline void cleanupResource()
{
	Q_CLEANUP_RESOURCE(PERAResources);
}

namespace pera_software::aidkit::qt {

#define PREFIX ":/pera_software/resources/"

PERAResources PERAResources::instance_;

PERAResources &PERAResources::instance()
{
	return instance_;
}

PERAResources::PERAResources()
{
	initResource();
}

PERAResources::~PERAResources()
{
	cleanupResource();
}


QIcon PERAResources::icon()
{
	return loadIcon(PREFIX "PERAIcon.png"_qs);
}

QPixmap PERAResources::logo()
{
	return QPixmap(PREFIX "PERALogo.png"_qs);
}

}
