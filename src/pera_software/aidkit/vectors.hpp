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

#pragma once

#include <pera_software/aidkit/aidkit.hpp>
#include <pera_software/aidkit/cpp/string_ref.hpp>
#include "containers.hpp"
#include <vector>
#include <algorithm>
#include <sstream>

namespace pera_software::aidkit::vectors {

	template < typename T, typename C >
		void remove_if( std::vector< T > *values, C condition )
		{
			auto newEnd = std::remove_if( values->begin(), values->end(), condition );
			values->erase( newEnd, values->end() );
		}

	template < typename T >
		void remove( std::vector< T > *values, const T &value )
		{
			remove_if( values, [ = ]( const T &currentValue ) {
				return currentValue == value;
			});
		}

	template < typename T >
		void pop_front( std::vector< T > *values )
		{
			values->erase( values->begin() );
		}
}

namespace std {

	template < typename T >
		ostream &operator << ( ostream &output, const vector< T > &values ) {
			constexpr char EMPTY[] = { '\0' };
			constexpr char COMMA[] = { ',', ' ', '\0' };

			return pera_software::aidkit::containers::join( output, values, EMPTY, COMMA, EMPTY );
		}
}
