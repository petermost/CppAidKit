// Copyright 2020 Peter Most, PERA Software Solutions GmbH
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

#include "Translator.hpp"
#include <pera_software/aidkit/qt/core/Strings.hpp>

static inline void initResource()
{
	Q_INIT_RESOURCE(AidKitTranslations);
}

static inline void cleanupResource()
{
	Q_CLEANUP_RESOURCE(AidKitTranslations);
}

namespace pera_software::aidkit::qt {

Translator::Translator()
{
	initResource();
}

Translator::~Translator()
{
	cleanupResource();
}

bool Translator::load()
{
	return QTranslator::load(":/pera_software/aidkit/translations/AidKitTranslations.qm"_qs);
}

}
