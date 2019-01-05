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

#include <string_view>

// IMHO string_ref is a better name then string_view, but apart from that it's now only one
// place which needs to be edited when string_view moves from experimental to std.

namespace pera_software::aidkit::cpp {

	template < typename Char >
		using basic_string_ref = std::basic_string_view< Char >;

	using string_ref    = std::string_view;
	using wstring_ref   = std::wstring_view;
	using u16string_ref = std::u16string_view;
	using u32string_ref = std::u32string_view;

}
