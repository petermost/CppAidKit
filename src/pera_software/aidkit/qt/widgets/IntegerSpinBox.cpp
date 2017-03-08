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

#include "IntegerSpinBox.hpp"
#include <limits>

namespace pera_software { namespace aidkit { namespace qt {

using namespace std;

//==================================================================================================

IntegerSpinBox::IntegerSpinBox( QWidget *parent )
	: QSpinBox( parent ) {

	// QSpinBox sets the default range (i.e. minimum, maximum) from 0 to 99 which IMHO isn't suitable
	// for most cases. So to avoid surprises we set the range to the minimum/maximum values of the
	// integer:

	setRange( numeric_limits< int >::min(), numeric_limits< int >::max() );
}

//==================================================================================================

IntegerSpinBox::IntegerSpinBox( int value, QWidget *parent )
	: IntegerSpinBox( parent ) {

	setValue( value );
}

} } }
