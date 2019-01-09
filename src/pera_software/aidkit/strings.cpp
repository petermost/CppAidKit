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

#include "strings.hpp"
#include <locale>
#include <algorithm>

namespace pera_software::aidkit {

using namespace	std;

static bool is_space(char c) {
	return isspace( c, locale() );
}

static bool is_not_space(char c) {
	return !is_space( c );
}

const string trim_left(const string &s, const function<bool (char)> &predicate) {
	return string( find_if( s.begin(), s.end(), predicate ), s.end() );
}

const string trim_right(const string &s, const function<bool (char)> &predicate) {
	return string( s.begin(), find_if( s.rbegin(), s.rend(), predicate ).base() );
}


const string trim_left(const string &s) {
	return trim_left( s, is_not_space );
}

const string trim_right(const string &s) {
	return trim_right( s, is_not_space );
}

const string trim_left(const string &s, char c) {
	return trim_left( s, [ = ]( char sc ) {
		return sc != c;
	});
}

const string trim_right(const string &s, char c) {
	return trim_right( s, [ = ]( char sc ) {
		return sc != c;
	});
}

}
