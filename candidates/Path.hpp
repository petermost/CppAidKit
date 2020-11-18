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

#pragma once

#include <pera_software/aidkit/aidkit.hpp>
#include <QFlags>
#include <QString>
#include <QVector>
#include <QStringView>

namespace pera_software::aidkit::qt {

class AIDKIT_API Path {
	public:
		enum ToStringOption {
			Drive       = 1 << 0,
			Directories = 1 << 1,
			Name        = 1 << 2,
			Extensions  = 1 << 3
		};
		Q_DECLARE_FLAGS(ToStringOptions, ToStringOption)

		Path() = default;
		Path(QStringView path);

		void setDrive();
		void setDrive(QString drive);
		QString drive() const;

		void setDirectory(int index, QString directory);
		QString directory() const;
		QString directory(int index) const;

		QString name() const;
		QString extension() const;
		QString extensionAt(int index) const;

		QString toString() const;
		QString toString(ToStringOptions options) const;

	private:
		QString drive_;
		QVector<QString> directories_;
		QString name_;
		QVector<QString> extensions_;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Path::ToStringOptions)
}
