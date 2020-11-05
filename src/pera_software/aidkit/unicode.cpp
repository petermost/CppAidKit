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

#include "unicode.hpp"
#include <codecvt>
#include <locale>
#include <pera_software/aidkit/io/errno.hpp>

// TODO: Check what is the replacement for codecvt_utf8?
// TODO: Howto convert local platform characters to UTF-8?

namespace pera_software::aidkit {

using namespace io;
using namespace std;

//==================================================================================================

// https://sourceforge.net/p/mingw-w64/bugs/538/
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=69703
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66855

using wstring_utf8_converter = wstring_convert<codecvt_utf8<wchar_t>, wchar_t>;

wstring from_utf8(string_view s)
{
	wstring_utf8_converter converter;
	const char *begin = &(*s.begin());
	const char *end = begin + s.size();
	return converter.from_bytes(begin, end);
}

string to_utf8(wstring_view s)
{
	wstring_utf8_converter converter;
	const wchar_t *begin = &(*s.begin());
	const wchar_t *end = begin + s.size();
	return converter.to_bytes(begin, end);
}

//==================================================================================================

template <typename SrcChar, typename DstChar>
	basic_string<DstChar> convert(const basic_string_view<SrcChar> &sourceString,
		size_t (*convertFunction)(DstChar *dst, const SrcChar **src, size_t len, mbstate_t *state))
	{
		constexpr auto LENGTH_ERROR = static_cast<size_t>(-1);

		mbstate_t state = mbstate_t();

		// Find out how much space we need:

		const SrcChar *sourceStringData = sourceString.data();
		size_t expectedTargetStringLength = convertFunction(nullptr, &sourceStringData, sourceString.length(), &state);
		if (expectedTargetStringLength == LENGTH_ERROR)
			throw make_errno_system_error();

		// Convert the string:

		basic_string<DstChar> targetString(expectedTargetStringLength, DstChar());
		size_t actualTargetStringLength = convertFunction(&targetString[0], &sourceStringData, sourceString.length(), &state);
		if (actualTargetStringLength == LENGTH_ERROR)
			throw make_errno_system_error();

		// Could all characters be converted?

		if (expectedTargetStringLength != actualTargetStringLength)
			throw system_error(make_error_code(errc::illegal_byte_sequence));

		return targetString;
	}

string to_mbs(wstring_view wideString)
{
	return convert(wideString, wcsrtombs);
}

wstring from_mbs(string_view narrowString)
{
	return convert(narrowString, mbsrtowcs);
}

}

namespace std {

ostream &operator<<(ostream &outputStream, wstring_view str)
{
	return outputStream << ::pera_software::aidkit::to_utf8(str);
}

}
