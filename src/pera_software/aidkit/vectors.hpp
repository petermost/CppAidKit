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
#include <vector>
#include <algorithm>

namespace std {

	template < typename T, typename Char >
		basic_ostream< Char > &operator << ( basic_ostream< Char > &outputStream, const vector< T > &container ) {
			const Char seperator[] = { ',', ' ', '\0' };

			auto it = container.begin();
			if ( it != container.end() ) {
				outputStream << *it++;
				while ( it != container.end() ) {
					outputStream << seperator << *it++;
				}
			}
			return outputStream;
		}
}

namespace pera_software { namespace aidkit {

	template < typename T, typename C >
		void vector_remove_if( std::vector< T > *container, C condition )
		{
			auto newEnd = std::remove_if( container->begin(), container->end(), condition );
			container->erase( newEnd, container->end() );
		}
} }
