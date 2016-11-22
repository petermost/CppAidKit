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

#include "debug.hpp"

namespace pera_software { namespace aidkit {

using namespace std;

void check_assertion( bool condition, const string &expression, const string &fileName, int lineNumber,
	const string &functionName ) {
	if ( !condition )
		throw assertion_exception( expression, fileName, lineNumber, functionName );
}

assertion_exception::assertion_exception( const string &expression, const string &fileName, int lineNumber, const string &functionName )
	: expression_( expression ), fileName_( fileName ), lineNumber_( lineNumber ), functionName_( functionName ) {

	message_ = fileName_ + "(" + to_string( lineNumber_ ) + "): " + functionName_ + ": Assertion '" + expression_ + "' failed!";
}

const string &assertion_exception::expression() const noexcept {
	return expression_;
}

const string &assertion_exception::file_name() const noexcept {
	return fileName_;
}

const string &assertion_exception::function_name() const noexcept {
	return functionName_;
}

int assertion_exception::line_number() const noexcept {
	return lineNumber_;
}

const string &assertion_exception::message() const noexcept {
	return message_;
}

} }
