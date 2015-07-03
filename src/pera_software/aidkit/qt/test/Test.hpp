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

#include <QList>
#include <QStringList>
#include <pera_software/aidkit/aidkit.hpp>
#include <array>
#include <QVector>

namespace pera_software {
	namespace aidkit {
		namespace qt {

			class AIDKIT_API Test : public QObject {
				Q_OBJECT
				public:
					template < typename Functor >
						static void forEach( Functor &&functor ) {
							for ( std::size_t i = 0; i < s_testsSize; ++i ) {
								functor( s_tests[ i ]);
							}
						}

					static int executeTests( const QStringList &arguments );

					static QVector< Test * > queryTests();

				protected:
					Test();
					virtual ~Test();

				private:
					enum { SIZE = 100 };
					static std::size_t s_testsSize;
					static std::array< Test *, SIZE > s_tests;
			};
		}
	}
}
