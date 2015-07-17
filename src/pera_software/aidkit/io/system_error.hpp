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

#include <system_error>

namespace pera_software { namespace aidkit { namespace io {

	template < typename Functor >
		static auto call_and_throw_if_error( Functor &&functor ) -> decltype( functor( static_cast< std::error_code * >( nullptr ))) {
			std::error_code errorCode;
			auto result = functor( &errorCode );

			if ( errorCode )
				throw std::system_error( errorCode );

			return result;
		}

} } }
