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

	// TODO: Rename to join?

	template < typename Iterator >
		std::ostream &print( std::ostream &output, Iterator begin, Iterator end,
			cpp::string_ref prefix, cpp::string_ref delimiter, cpp::string_ref suffix )
		{
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

	template < typename Container >
		std::ostream &print( std::ostream &output, const Container &container,
			cpp::string_ref prefix, cpp::string_ref delimiter, cpp::string_ref suffix )
		{
			return print( output, container.begin(), container.end(), prefix, delimiter, suffix );
		}

	template < typename Iterator >
		std::string print(Iterator begin, Iterator end,
			cpp::string_ref prefix, cpp::string_ref delimiter, cpp::string_ref suffix )
		{
			std::ostringstream valueStream;

			print( valueStream, begin, end, prefix, delimiter, suffix );

			return valueStream.str();
		}

	template < typename Container >
		std::string print(const Container &container,
			cpp::string_ref prefix, cpp::string_ref delimiter, cpp::string_ref suffix )
		{
			return print(container.begin(), container.end(), prefix, delimiter, suffix);
		}
}
