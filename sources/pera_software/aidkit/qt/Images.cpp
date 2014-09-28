// Copyright 2014 Peter Most, PERA Software Solutions GmbH
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

#include <pera_software/aidkit/qt/Images.hpp>
#include <QIcon>
#include <QFile>

namespace pera_software { namespace aidkit { namespace qt {

const QString Images::PERAIcon( ":/images/pera_software/Icon.png" );
const QString Images::PERALogo( ":/images/pera_software/Logo.png" );


const QIcon &Images::operator[]( const QString &iconName )
{
	auto it = icons_.find( iconName );
	if ( it == icons_.end() ) {
		Q_ASSERT( QFile::exists( iconName ));
		it = icons_.insert( iconName, QIcon( iconName ));
	}
	return it.value();
}

class Images Images;

} } }
