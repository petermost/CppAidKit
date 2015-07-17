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

#include <system_error>
#include <pera_software/aidkit/aidkit.hpp>

// Define a file error code:
// http://blog.think-async.com/2010/04/system-error-support-in-c0x-part-4.html

namespace pera_software { namespace aidkit { namespace io {

	enum class file_error {
		unspecific = 1,
		eof
	};

	class AIDKIT_API file_error_category : public std::error_category {
		public:
			static const file_error_category &instance();

			virtual const char *name() const noexcept override;
			virtual std::string message( int error ) const override;
	};

	AIDKIT_API std::error_code make_error_code( file_error error );
	AIDKIT_API std::error_condition make_error_condition( file_error error );

	AIDKIT_API std::error_code get_file_error_code( bool success ) noexcept;

} } }

namespace std {
	template <>
		struct is_error_code_enum< pera_software::aidkit::io::file_error > : public true_type {
		};
}
