// Copyright 2023 Peter Most, PERA Software Solutions GmbH
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

#include <string>
#include <string_view>

namespace pera_software::aidkit::stdlib {

// A simple extension of std::basic_string_view<> to make the pointer-constructor
// safe for null-pointers.

template <typename T>
	class basic_string_ref : public std::basic_string_view<T>
	{
		public:
			basic_string_ref(const T *ptr)
				: std::basic_string_view<T>(ptr != nullptr ? ptr : &EOS)
			{
			}

			basic_string_ref(const std::basic_string<T> &str)
				: std::basic_string_view<T>(str.data(), str.length())
			{
			}

		private:
			static const T EOS;
};

template <typename T>
	const T basic_string_ref<T>::EOS = 0;

using string_ref = basic_string_ref<char>;
using wstring_ref = basic_string_ref<wchar_t>;

}
