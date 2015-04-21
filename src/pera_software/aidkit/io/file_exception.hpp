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
#include "ErrNoException.hpp"
#include <string>

namespace pera_software {
	namespace aidkit {
		namespace io {

			typedef ErrNoExceptionTemplate< class File > FileException;

			// TODO: Rename FileNotFoundException to file_no_found_exception.

			class AIDKIT_EXPORT FileNotFoundException : public FileException {
				public:
					FileNotFoundException( const std::string &fileName );

					const std::string &fileName() const;

				private:
					std::string fileName_;
			};


			// TODO: Check whether EndOfFileException is used.
			// TODO: Rename EndOfFileException to end_of_file_exception.

			class AIDKIT_EXPORT EndOfFileException : public FileException {
				public:
					EndOfFileException();
			};
		}
	}
}
