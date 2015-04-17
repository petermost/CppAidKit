#include "stdafx.h"
#include "Exception.hpp"
#include "../Strings/Unicode.hpp"

using namespace std;
using namespace Strings;

namespace std {

wostream &operator << ( wostream &outputStream, const exception &e )
{
	outputStream << e.what();
	return outputStream;
}

}


const char *Exception::what() const
{
	mMessage = wstring_to_string( Message() );

	return mMessage.c_str();
}

} }
