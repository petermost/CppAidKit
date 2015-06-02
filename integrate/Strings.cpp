#include "stdafx.h"
#include "Strings.hpp"

using namespace std;


UTILITYCPP_API const string EMPTY_STRING( "" );
UTILITYCPP_API const wstring EMPTY_WSTRING( L"" );

template <>
	UTILITYCPP_API bool is_not_space( char c )
	{
		return !isspace( c );
	}

template <>
	UTILITYCPP_API bool is_not_space( wchar_t c )
	{
		return !iswspace( c );
	}

// Explicitly instantiate the templates to detect compiler errors:

template const string trim_left( const string & );
template const string trim_right( const string & );
template const string trim_left( const string &, char c );
template const string trim_right( const string &, char c );

template const wstring trim_left( const wstring & );
template const wstring trim_right( const wstring & );
template const wstring trim_left( const wstring &, wchar_t c );
template const wstring trim_right( const wstring &, wchar_t c );

} }
