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
#include <sstream>

namespace pera_software::aidkit::containers {

	template < typename Iterator, typename Char >
		std::basic_ostream< Char > &print( std::basic_ostream< Char > &output, Iterator begin, Iterator end,
			cpp::basic_string_ref< Char > prefix, cpp::basic_string_ref< Char > delimiter, cpp::basic_string_ref< Char > suffix ) {

			output << prefix;
			auto it = begin;
			if ( it != end ) {
				output << *it++;
				while ( it != end )
					output << delimiter << *it++;
			}
			output << suffix;

			return output;
		}
}
