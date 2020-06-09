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

#include "formatter.hpp"

namespace pera_software::aidkit::boost {

using namespace std;
using namespace ::boost::io;

formatter::formatter(string_view formatString) noexcept
	: format_(nullptr)
{
	format_.exceptions(format_error_bits::no_error_bits);
	format_.parse(string(formatString));
}

string formatter::str() const noexcept
{
	return format_.str();
}

}
