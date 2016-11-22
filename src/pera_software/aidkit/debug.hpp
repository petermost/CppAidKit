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

#include "aidkit.hpp"
#include "exception.hpp"
#include <string>

namespace pera_software { namespace aidkit {

	void AIDKIT_API check_assertion( bool condition, const std::string &expression, const std::string &fileName,
			int lineNumber, const std::string &functionName );

	class AIDKIT_API assertion_exception : public aidkit::exception {
		public:
			assertion_exception( const std::string &expression, const std::string &file_name,
					int line_number, const std::string &function_name );

			const std::string &expression() const noexcept;

			const std::string &file_name() const noexcept;

			const std::string &function_name() const noexcept;

			int line_number() const noexcept;

			const std::string &message() const noexcept override;

		private:
			std::string expression_;
			std::string fileName_;
			int lineNumber_;
			std::string functionName_;

			std::string message_;
	};

} }

#define AIDKIT_VERIFY( expression ) \
	pera_software::aidkit::check_assertion( expression, #expression, __FILE__, __LINE__, __func__ )

#if defined( AIDKIT_DEBUG )
	#define AIDKIT_ASSERT( expression ) \
		AIDKIT_VERIFY( expression )
#else
	#define AIDKIT_ASSERT( expression )
#endif
