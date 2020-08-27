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

#include "PERASettings.hpp"
#include <pera_software/PERA.hpp>
#include <QWidget>

namespace pera_software::aidkit::qt {

// Colons (':') would be stored as %3A so we replace them with a dot ('.'):

static const QString COLONS(QStringLiteral("::"));
static const QString DOT(QStringLiteral("."));

static const QString SIZE_KEY(QStringLiteral("size"));
static const QString POSITION_KEY(QStringLiteral("position"));


PERASettings::PERASettings(const QString &applicationName, QObject *parent)
	:iniFile_(QSettings::Format::IniFormat, QSettings::Scope::UserScope, QString::fromUtf8(PERA::NAME), applicationName, parent)
{
}

void PERASettings::writeGeometry(const QWidget *widget)
{
	writeSize(widget);
	writePosition(widget);
}

void PERASettings::readGeometry(QWidget *widget)
{
	readSize(widget);
	readPosition(widget);
}

void PERASettings::writeSize(const QWidget *widget)
{
	iniFile_.beginGroup(makeGroupName(widget));
		iniFile_.setValue(SIZE_KEY, widget->size());
	iniFile_.endGroup();
}

void PERASettings::readSize(QWidget *widget)
{
	iniFile_.beginGroup(makeGroupName(widget));
		widget->resize(iniFile_.value(SIZE_KEY, widget->size()).toSize());
	iniFile_.endGroup();
}

void PERASettings::writePosition(const QWidget *widget)
{
	iniFile_.beginGroup(makeGroupName(widget));
		iniFile_.setValue(POSITION_KEY, widget->pos());
	iniFile_.endGroup();
}

void PERASettings::readPosition(QWidget *widget)
{
	iniFile_.beginGroup(makeGroupName(widget));
		widget->move(iniFile_.value(POSITION_KEY, widget->pos()).toPoint());
	iniFile_.endGroup();
}

QString PERASettings::fileName() const
{
	return iniFile_.fileName();
}

QString PERASettings::makeGroupName(const QObject *object)
{
	return QString::fromUtf8(object->metaObject()->className()).replace(COLONS, DOT);
}

}
