// Copyright 2015 Peter Most, PERA Software Solutions GmbH
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

#include <QObject>
#include <QVector>
#include <QStringList>
#include <pera_software/aidkit/aidkit.hpp>

namespace pera_software { namespace aidkit { namespace qt {

class AIDKIT_API Test : public QObject {
	Q_OBJECT
	public:
		static int main( int argc, char *argv[] ) noexcept;

		QString name() const noexcept;

	protected:
		Test() noexcept;
		virtual ~Test();

		static QVector< Test * > executeTests( const QStringList &arguments ) noexcept;

	private:
		static QVector< Test * > &tests() noexcept;
};

} } }
