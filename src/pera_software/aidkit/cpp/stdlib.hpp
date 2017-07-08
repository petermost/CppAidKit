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

#pragma once

#include <cstdlib>
#include <iterator>
#include <limits>

namespace pera_software { namespace aidkit { namespace cpp {

	// Make an 'alias function' from countof() to std::size():

	template < typename... Args >
		auto countof( Args&&... args ) -> decltype( std::size( std::forward< Args >( args )... )) {
			return std::size( std::forward< Args >( args )... );
		}

	template < typename D, typename S >
		D int_cast( S s ) {
			if ( s > std::numeric_limits< D >::max() )
				throw std::out_of_range( "Source type value is too large for destination type" );
			else if ( s < std::numeric_limits< D >::min() )
				throw std::out_of_range( "Source type value is too small for destination type" );
			else
				return static_cast< D >( s );
		}
} } }
