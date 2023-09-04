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

#include <type_traits>

namespace pera_software::aidkit {

constexpr std::true_type const_ = {};

template <typename... Args>
	struct overload_cast_impl {
		constexpr overload_cast_impl()
		{
		}

		template <typename Return>
			constexpr auto operator()(Return (*pf)(Args...)) const noexcept -> decltype(pf)
			{
				return pf;
			}

		template <typename Return, typename Class>
			constexpr auto operator()(Return (Class::*pmf)(Args...), std::false_type = {}) const noexcept -> decltype(pmf)
			{
				return pmf;
			}

		template <typename Return, typename Class>
			constexpr auto operator()(Return (Class::*pmf)(Args...) const, std::true_type) const noexcept -> decltype(pmf)
			{
				return pmf;
			}
	};

//template <typename... Args>
//constexpr overload_cast_impl<Args...> overload_cast = {};

template <typename... Args>
static constexpr overload_cast_impl<Args...> overload_cast = {};

}
