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

#include "basic_file.hpp"
#include <pera_software/aidkit/aidkit.hpp>
#include <string>

namespace pera_software::aidkit::io {

	using file = basic_file< char >;
	using wfile = basic_file< wchar_t >;

	AIDKIT_API bool remove_file( const char fileName[] );
	AIDKIT_API bool remove_file( const char fileName[], std::error_code *errorCode ) noexcept;

	AIDKIT_API void remove_file_if_exists( const char fileName[] );

	// An RAII file deleter for deleting/cleaning up files:

	class AIDKIT_API file_deleter {
		public:
			file_deleter( const std::string &fileName );

			// Destructors in C++11 are implicitly declared as noexcept, so we have to explicitly allow
			// exceptions (http://en.cppreference.com/w/cpp/language/destructor#Exceptions):

			~file_deleter() noexcept( false );

		private:
			std::string fileName_;
	};

}
