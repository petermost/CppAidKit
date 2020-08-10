// Copyright 2017 Peter Most, PERA Software Solutions GmbH
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

#include "Chrono.hpp"
#include <QDataStream>

using namespace std::chrono;

// Ensure that quint64 is big enough to hold the millisconds value:
Q_STATIC_ASSERT_X( sizeof( quint64 ) >= sizeof( milliseconds::rep ), "quint64 is too small to hold milliseconds values!" );

//==================================================================================================

QDataStream &operator<<( QDataStream &out, const milliseconds &value ) {
	out << static_cast< quint64 >( value.count() );

	return out;
}

//==================================================================================================

QDataStream &operator >> ( QDataStream &in, milliseconds &value ) {
	quint64 count;
	in >> count;
	value = milliseconds( count );

	return in;
}




namespace pera_software::aidkit::qt {

int MetaTypeRegistration::s_registrationCounter = 0;

//==================================================================================================

// TODO: Move implementation of 'Schwarz Counter' to its own class

MetaTypeRegistration::MetaTypeRegistration() {
	if ( s_registrationCounter++ == 0 ) {
		qRegisterMetaType< std::chrono::milliseconds >();
		qRegisterMetaTypeStreamOperators< milliseconds >( "std::chrono::milliseconds" );
	}
}

//==================================================================================================

MetaTypeRegistration::~MetaTypeRegistration() {
	if ( --s_registrationCounter == 0 ) {
	}
}

}
