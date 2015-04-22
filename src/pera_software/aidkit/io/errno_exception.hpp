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

#include <pera_software/aidkit/aidkit.hpp>
#include <pera_software/aidkit/exception.hpp>
#include <exception>
#include <string>

namespace pera_software {
	namespace aidkit {
		namespace io {

			class AIDKIT_EXPORT errno_exception : public aidkit::exception {
				public:
					static errno_exception last_error();

					errno_exception( int value = 0, const std::string &errorMessage = "" );

					int value() const {
						return errNo_;
					}

					virtual const char *what() const noexcept override;

				private:
					int errNo_;
					std::string errorMessage_;
			};

			template < typename T >
				class errno_exception_template : public errno_exception {
					public:
						static errno_exception_template lastError() {
							return errno_exception_template( errno );
						}

						errno_exception_template( int errNo = 0, const std::string &errorMessage = "" )
							: errno_exception( errNo, errorMessage ) {
						}
				};
		}
	}
}
