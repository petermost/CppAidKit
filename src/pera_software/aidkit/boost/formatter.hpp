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

#pragma once

#include <pera_software/aidkit/aidkit.hpp>
#include <pera_software/aidkit/cpp/string_ref.hpp>
#include <boost/format.hpp>
#include <string>

namespace pera_software::aidkit::boost {

	// A small wrapper class which disables the exceptions in boost::format otherwise:
	// - The constructor might throw a bad_format_string exception.
	// - The operator % () might throw a too_many_args exception.
	// - The method str() might throw a too_few_args exception.

	class AIDKIT_API formatter {
		public:
			formatter( cpp::string_ref formatString ) noexcept;

			template< class T >
				formatter &operator % ( T &&x ) {
					format_ % std::forward< T >( x );

					return *this;
				}

			std::string  str() const noexcept;

		private:
			::boost::format format_;
	};

}
