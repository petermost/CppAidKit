// Copyright 2014 Peter Most, PERA Software Solutions GmbH
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

#include <exception>
#include <string>
#include <pera_software/aidkit/AidKit.hpp>

namespace pera_software {
	namespace aidkit {

			class AIDKIT_EXPORT exception : public std::exception {
				public:
					exception() noexcept;

					virtual ~exception() noexcept;

					virtual const char *what() const noexcept = 0;
			};
	}
}
