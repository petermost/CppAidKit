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

#include <pera_software/aidkit/AidKit.hpp>
#include <pera_software/aidkit/Exception.hpp>
#include <exception>
#include <string>

namespace pera_software {
	namespace aidkit {
		namespace io {

			class AIDKIT_EXPORT ErrNoException : public Exception
			{
				public:
					static ErrNoException LastError();

					ErrNoException( int errNo = 0, const std::string &errorMessage = "" );

					int errNo() const
						{ return errNo_; }

					virtual const char *what() const noexcept override;

				private:
					int errNo_;
					std::string errorMessage_;
			};

			template < typename T >
				class ErrNoExceptionTemplate : public ErrNoException
				{
					public:
						static ErrNoExceptionTemplate LastError()
						{
							return ErrNoExceptionTemplate( errno );
						}

						ErrNoExceptionTemplate( int errNo = 0, const std::string &errorMessage = "" )
							: ErrNoException( errNo, errorMessage )
						{
						}
				};
		}
	}
}
