#pragma once

#include "../UtilityCpp.h"
#include <ctype.h>
#include <string>
#include <algorithm>
#include <functional>

#define STRINGIZE( name ) #name
#define STRINGIZE_SYMBOL( symbol ) STRINGIZE( symbol )

#define WSTRINGIZE( name ) L#name
#define WSTRINGIZE_SYMBOL( symbol ) WSTRINGIZE( symbol )


extern UTILITYCPP_API const std::string EMPTY_STRING;
extern UTILITYCPP_API const std::wstring EMPTY_WSTRING;

template < typename Char >
	UTILITYCPP_API bool is_not_space( Char c );


//=============================================================================

template < typename Char >
	const std::basic_string< Char > trim_left( const std::basic_string< Char > &s )
	{
		return std::basic_string< Char >( find_if( s.begin(), s.end(), is_not_space< Char > ), s.end() );
	}

//=============================================================================

template < typename Char >
	const std::basic_string< Char > trim_right( const std::basic_string< Char > &s )
	{
		return std::basic_string< Char >( s.begin(), find_if( s.rbegin(), s.rend(), is_not_space< Char > ).base() );
	}

//=============================================================================

template< typename Char >
	const std::basic_string< Char > trim_left( const std::basic_string< Char > &s, Char c )
	{
		return std::basic_string< Char >( find_if( s.begin(), s.end(), bind1st( not_equal_to< Char >(), c )), s.end() );
	}

//=============================================================================

template< typename Char >
	const std::basic_string< Char > trim_right( const std::basic_string< Char > &s, Char c )
	{
		return std::basic_string< Char >( s.begin(), find_if( s.rbegin(), s.rend(), bind1st( not_equal_to< Char >(), c )).base() );
	}

} }
