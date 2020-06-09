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
#include <string_view>
#include <sstream>

namespace pera_software::aidkit::containers {

template <typename Iterator>
	std::ostream &join(std::ostream &output, Iterator begin, Iterator end,
		std::string_view prefix, std::string_view delimiter, std::string_view suffix)
	{
		output << prefix;
		auto it = begin;
		if (it != end) {
			output << *it++;
			while (it != end)
				output << delimiter << *it++;
		}
		output << suffix;

		return output;
	}

template <typename Container>
	std::ostream &join(std::ostream &output, const Container &container,
		std::string_view prefix, std::string_view delimiter, std::string_view suffix)
	{
		return join(output, container.begin(), container.end(), prefix, delimiter, suffix);
	}

template <typename Iterator>
	std::string join(Iterator begin, Iterator end,
		std::string_view prefix, std::string_view delimiter, std::string_view suffix)
	{
		std::ostringstream valueStream;

		join(valueStream, begin, end, prefix, delimiter, suffix);

		return valueStream.str();
	}

template <typename Container>
	std::string join(const Container &container,
		std::string_view prefix, std::string_view delimiter, std::string_view suffix)
	{
		return join(container.begin(), container.end(), prefix, delimiter, suffix);
	}
}
