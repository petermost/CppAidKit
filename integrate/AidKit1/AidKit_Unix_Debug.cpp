#include "../AidKit_Debug.hpp"
#include "../AidKit_Misc.hpp"
#include "../AidKit_String.hpp"
#include "../AidKit_Unicode.hpp"
#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>

#if defined( AIDKIT_LINUX )

	#include <cxxabi.h>
	#include <execinfo.h>
	//=============================================================================
	int stack_backtrace( void **ppBuffer, int nBufferSize )
	//=============================================================================
	{
		return ( backtrace( ppBuffer, nBufferSize ));
	}


	//=============================================================================
	char *demangler_demanglename( const char *MangledName, char *pOutputBuffer, size_t *pOutputBufferSize, int *pStatus )
	//=============================================================================
	{
		return ( abi::__cxa_demangle( MangledName, pOutputBuffer, pOutputBufferSize, pStatus ));
	}

#else

	//=============================================================================
	int stack_backtrace( void **, int )
	//=============================================================================
	{
		return ( 0 );
	}

	//=============================================================================
	char *demangler_demanglename( const char *, char *, size_t *, int *pStatus )
	//=============================================================================
	{
		*pStatus = -2;

		return ( NULL );
	}


#endif


using namespace std;

namespace AidKit {

namespace Unix {

//=============================================================================
void debug_printf( const char_t Format[], ... )
//=============================================================================
{
	va_list Arguments;

	va_start( Arguments, Format );
	vf_print_f( stderr, Format, Arguments );
	fflush( stdout );
	va_end( Arguments );
}


//#############################################################################
//#############################################################################
//#############################################################################
//###
//### CCallStack
//###
//#############################################################################
//#############################################################################
//#############################################################################


//=============================================================================
CCallStack::CCallStack( void )
	throw ( bad_alloc )
//=============================================================================
{
	// We assume that if backtrace reports the exact same stack size the we've allocated,
	// that it actually would need more space:

	if (( my_Size = stack_backtrace( my_Stack, countof( my_Stack ))) == countof( my_Stack ))
		throw bad_alloc();
}


//=============================================================================
CCallStack::~CCallStack( void )
	throw()
//=============================================================================
{
}



//=============================================================================
size_t CCallStack::Size( void ) const
//=============================================================================
{
	return ( my_Size );
}



//=============================================================================
const void *CCallStack::SymbolAt( size_t i ) const
	throw ( out_of_range )
//=============================================================================
{
	if ( i < Size() )
		return ( my_Stack[ i ] );
	else
		throw out_of_range( "AidKit::Unix::CCallStack::SymbolAt" );
}



//=============================================================================
const char_t *CCallStack::SymbolNameAt( size_t i ) const
	throw ( out_of_range )
//=============================================================================
{
	// We don't use backtrace_symbols, because it puts the name in a format similar to:
	// "versuch(_Z10DumpStack3v+0x1d)[0x8056a1f]" which makes it very hard to get the
	// actual name (DumpStack3).
	// Besides: backtrace_symbols also gets it's information via dladdr ;-) See: backtrace.c, backtracesyms.c

	const char_t *pSymbolName = EMPTY_STRING.c_str();

	if ( i < Size() ) {
		if ( dladdr( my_Stack[ i ], &my_Info ) != 0 ) {
			if ( my_Info.dli_sname != NULL && my_Info.dli_sname[ 0 ] != '\0' )
				pSymbolName = my_Info.dli_sname;
			else if ( my_Info.dli_fname != NULL && my_Info.dli_fname[ 0 ] != '\0' )
				pSymbolName = my_Info.dli_fname;
		}
	} else
		throw out_of_range( "AidKit::Unix::CCallStack::SymbolNameAt" );

	return ( pSymbolName );
}


//#############################################################################
//#############################################################################
//#############################################################################
//###
//### CSymbolTable
//###
//#############################################################################
//#############################################################################
//#############################################################################

// To demangle a c++ identifier you can also use c++filt on the command line.

// Those values are from the source code of __cxa_demangle (cp-demangle.c):

const int MEMORY_FAILURE = -1;
const int INVALID_MANGLED_NAME = -2;
const int MISSING_PARAMETER = -3;

//=============================================================================
CSymbolTable::CSymbolTable( size_t DemanglingBufferSize )
	throw ( bad_alloc )
//=============================================================================
{
	// Buffer size must not be 0 because of a possible realloc call (realloc then tries to free the memory)!

	if ( DemanglingBufferSize == 0 )
		DemanglingBufferSize = 255; 

	my_DemanglingBufferSize = DemanglingBufferSize;
	if (( my_pDemanglingBuffer = static_cast< char * >( malloc( my_DemanglingBufferSize ))) == NULL )
		throw bad_alloc();
}



//=============================================================================
CSymbolTable::~CSymbolTable( void )
	throw()
//=============================================================================
{
	free( my_pDemanglingBuffer );
}


//=============================================================================
const char_t *CSymbolTable::DemangleName( const char_t MangledName[] )
	throw ( bad_alloc, invalid_argument )
//=============================================================================
{
	int Status = 0;
	const char *pDemangledName;

	// The from __cxa_demangle modified buffer size contains the new buffer size,
	// not the length of the demangled name! So we can't use it for string::assign.

	if (( pDemangledName = demangler_demanglename( MangledName, my_pDemanglingBuffer, &my_DemanglingBufferSize, &Status )) != NULL ) {
		my_pDemanglingBuffer = const_cast< char_t * >( pDemangledName ); // Might be a new pointer because of a realloc call.
		if ( Status == INVALID_MANGLED_NAME )
			pDemangledName = MangledName; // Return the original name.
	} else {
		if ( Status == MEMORY_FAILURE )
			throw bad_alloc();
		else if ( Status == MISSING_PARAMETER )
			throw invalid_argument( "AidKit::Unix::CSymbolTable::DemangleName" );
		else
			pDemangledName = MangledName;
	}
	return ( pDemangledName );
}

} // namespace Unix

} // namespace AidKit
