#include "AidKit_Debugger.hpp"
#include "AidKit_Text.hpp"
#include "AidKit_Misc.hpp"
#include "AidKit_Debug.hpp"
#include "AidKit_Types.hpp"
#include "AidKit_Templates.hpp"
#include "AidKit_DebuggerDisplay.hpp"

#include <stdarg.h>
#include <ctype.h>

#include "AidKit_Warnings.hpp"

using namespace std;

namespace AidKit {

/*
static const CText kSettingsLoadedTxt(
	TEXT( "Settings for '%s' debugger loaded." ),       CText::eEnglish,
	TEXT( "Einstellungen für '%s' Debugger geladen." ), CText::eGerman,
	NULL );

static const CText kNotLoadedTxt(
	TEXT( "Could not load settings for '%s' debugger!" ), CText::eEnglish,
	TEXT( "Konnte Einstellungen für '%s' Debugger nicht laden!" ), CText::eGerman,
	NULL );

static const CText kNotSavedTxt(
	TEXT( "Could not save settings for '%s' debugger!" ), CText::eEnglish,
	TEXT( "Konnte Einstellungen für '%s' Debugger nicht speichern!" ), CText::eGerman,
	NULL );
*/

static const unsigned kDefaultDumpWidth = 16;

//=============================================================================
static char_t *PrepareOutput( char_t Output[], size_t OutputSize, const string_t &Name,
	const char_t Format[], va_list Arguments )
//=============================================================================
{
	int OutputIdx = sn_print_f( Output, OutputSize, TEXT( "%s: " ), Name.c_str() );
	vsn_print_f( &Output[ OutputIdx ], OutputSize - OutputIdx, Format, Arguments );
	AIDKIT_ASSERT( str_len( Output ) < OutputSize );

	return ( Output );
}

//#############################################################################
//#############################################################################
//#############################################################################
//###
//### CDebuggerSettings
//###
//#############################################################################
//#############################################################################
//#############################################################################


//=============================================================================
CDebuggerSettings::CDebuggerSettings( void )
//=============================================================================
{
}



//=============================================================================
CDebuggerSettings::~CDebuggerSettings( void )
//=============================================================================
{
}



//=============================================================================
bool CDebuggerSettings::IsTraceEnabled( const CDebugger *, bool DefaultValue )
//=============================================================================
{
	return ( DefaultValue );
}



//=============================================================================
bool CDebuggerSettings::IsDumpEnabled( const CDebugger *, bool DefaultValue )
//=============================================================================
{
	return ( DefaultValue );
}




//#############################################################################
//#############################################################################
//#############################################################################
//###
//### CDebugger
//###
//#############################################################################
//#############################################################################
//#############################################################################

const string_t CDebugger::LOG_FILE_NAME( TEXT( "Debugger.log" ));

CThreadGuard CDebugger::our_ThreadGuard;

CDebuggerSettings CDebugger::our_DefaultSettings;
CDebuggerSettings *CDebugger::our_pSettings = &our_DefaultSettings;

CDebuggerDisplay CDebugger::our_DefaultDisplay;
CDebuggerDisplay *CDebugger::our_pDisplay = &our_DefaultDisplay;

FILE *CDebugger::our_LogFile = NULL;

#ifdef AIDKIT_DEBUG
	bool CDebugger::our_IsDebugging = true;
#else
	bool CDebugger::our_IsDebugging = false;
#endif


//=============================================================================
bool CDebugger::EnableDebugging( bool Enable )
//=============================================================================
{
	return ( Exchange( &our_IsDebugging, Enable ));
}



//=============================================================================
bool CDebugger::IsDebugging( void )
//=============================================================================
{
	return ( our_IsDebugging );
}



//=============================================================================
CDebuggerDisplay *CDebugger::ExchangeDebuggerDisplay( CDebuggerDisplay *pNewDisplay )
//=============================================================================
{
	CThreadLock ThreadLock( &our_ThreadGuard );

	if ( pNewDisplay == NULL )
		pNewDisplay = &our_DefaultDisplay;

	return ( Exchange( &our_pDisplay, pNewDisplay ));
}



//=============================================================================
CDebuggerSettings *CDebugger::ExchangeDebuggerSettings( CDebuggerSettings *pNewSettings )
//=============================================================================
{
	CThreadLock ThreadLock( &our_ThreadGuard );

	if ( pNewSettings == NULL )
		pNewSettings = &our_DefaultSettings;

	return ( Exchange( &our_pSettings, pNewSettings ));
}



//=============================================================================
CDebugger::CDebugger( const string_t &Name, bool IsTraceEnabled, bool IsDumpEnabled,
	bool IsStandalone )
//=============================================================================
{
	my_Name = Name;

	if ( IsDebugging() ) {
		my_IsStandalone = IsStandalone;
		my_IsTraceEnabled = IsTraceEnabled;
		my_IsDumpEnabled  = IsDumpEnabled;
	}
}



//=============================================================================
CDebugger::~CDebugger( void )
//=============================================================================
{
	if ( IsDebugging() ) {
	}
}



//=============================================================================
void CDebugger::Display( const char_t Data[] )
//=============================================================================
{
	if ( IsDebugging() ) {
		WriteLog( Data );
		
		our_pDisplay->Write( Data );
	}
}




//#############################################################################
//
// Trace
//
//#############################################################################

//=============================================================================
void CDebugger::Trace( const char_t Format[], ... )
//=============================================================================
{
	if ( IsDebugging() ) {
		va_list Arguments;

		va_start( Arguments, Format );
		VTrace( Format, Arguments );
		va_end( Arguments );
	}
}


//=============================================================================
void CDebugger::VTrace( const char_t Format[], va_list Arguments )
//=============================================================================
{
	if ( IsDebugging() ) {
		char_t Output[ kDefaultOutputSize ];

		if ( IsTraceEnabled() ) {
			PrepareOutput( Output, countof( Output ), Name(), Format, Arguments );
			Display( Output );
		}
	}
}





//=============================================================================
bool CDebugger::IsTraceEnabled( void ) const
//=============================================================================
{
	// if the debugger is not a standalone debugger, then get the settings from
	// the CDebuggerSettings instance:

	if ( IsDebugging() ) {
		CThreadLock ThreadLock( &our_ThreadGuard );
		return (( my_IsStandalone ) ? my_IsTraceEnabled : our_pSettings->IsTraceEnabled( this, my_IsTraceEnabled ));
	} else {
		return ( false );
	}
}




//#############################################################################
//
// Dump
//
//#############################################################################

//=============================================================================
static unsigned DataDump( char_t Output[], const void *Data, size_t DataLength,
	unsigned ( *DumpFunction )( char_t [], BYTE, bool ), unsigned DumpWidth )
//=============================================================================
{
	bool IsPrinting = true;
	unsigned OutputIdx = 0;

	while ( DumpWidth-- > 0 ) {
		IsPrinting = (( DataLength > 0 ) ? DataLength-- > 0 : DataLength > 0 );
		OutputIdx += DumpFunction( &Output[ OutputIdx ], *static_cast< const BYTE * >( Data ), IsPrinting );
		Data = ( const BYTE * )Data + 1;
	}
	return ( OutputIdx );
}



//=============================================================================
static unsigned AsciiDump( char_t Output[], BYTE b, bool IsPrinting )
//=============================================================================
{
	unsigned Width;

	if ( IsPrinting ) {
		char_t c = ( is_cntrl( b )) ? TEXT( '.' ) : char_to_unichar( b );
		Width = s_print_f( Output, TEXT( "%c" ), c );
	} else
		Width = s_print_f( Output, TEXT( "%c" ), TEXT( ' ' ));

	return ( Width );
}



//=============================================================================
static unsigned HexDump( char_t Output[], BYTE b, bool IsPrinting )
//=============================================================================
{
	unsigned Width;

	if ( IsPrinting )
		Width = s_print_f( Output, TEXT( " %02X" ), b );
	else
		Width = s_print_f( Output, TEXT( " %2s" ), TEXT( "  " ));

	return ( Width );
}


	

//=============================================================================
void CDebugger::Dump( const void *Memory, size_t MemoryLength )
//=============================================================================
{
	if ( IsDumpEnabled() ) {
		char_t MemoryName[ 20 ];

		sn_print_f( MemoryName, countof( MemoryName ), TEXT( "$%p" ), Memory );
		Dump( MemoryName, Memory, MemoryLength );
	}
}


//=============================================================================
void CDebugger::Dump( const string_t &MemoryName, const void *Memory, size_t MemoryLength )
//=============================================================================
{
	if ( IsDumpEnabled() ) {
		const char_t Gap[] = TEXT( " - " );

		int OutputIdx;
		size_t DumpWidth;
		char_t Output[ kDefaultOutputSize ];

		const BYTE *Data = static_cast< const BYTE * >( Memory );
		size_t DataLength = MemoryLength;

		while ( DataLength > 0 ) {
			DumpWidth = min( kDefaultDumpWidth, DataLength );

			// memset( my_Output, TEXT( ' ' ), countof( my_Output ));

			// Header:
			OutputIdx = sn_print_f( Output, countof( Output ), TEXT( "%s: %s[%04d/%04d]" ),
				Name().c_str(), MemoryName.c_str(), Data - static_cast< const BYTE * >( Memory ), MemoryLength );

			// Hex dump:
			OutputIdx += DataDump( &Output[ OutputIdx ], Data, DataLength, HexDump, kDefaultDumpWidth );

			// Gap between hex dump and ascii dump:
			str_cpy( &Output[ OutputIdx ], Gap );
			OutputIdx += str_len( Gap );

			// ASCII dump:
			OutputIdx += DataDump( &Output[ OutputIdx ], Data, DataLength, AsciiDump, kDefaultDumpWidth );

			AIDKIT_ASSERT( str_len( Output ) < countof( Output ));
			Display( Output );

			Data       += DumpWidth;
			DataLength -= DumpWidth;
		}
	}
}




//=============================================================================
bool CDebugger::IsDumpEnabled( void ) const
//=============================================================================
{
	// if the debugger is not a standalone debugger, then get the settings from
	// the CDebuggerSettings instance:

	if ( IsDebugging() ) {
		CThreadLock ThreadLock( &our_ThreadGuard );
		return (( my_IsStandalone ) ? my_IsDumpEnabled : our_pSettings->IsDumpEnabled( this, my_IsDumpEnabled ));
	} else {
		return ( false );
	} 
}


//#############################################################################
//
// Log
//
//#############################################################################

// Logging is always enabled!

//=============================================================================
bool CDebugger::OpenDebuggerLogFile( const char_t LogFileName[] )
//=============================================================================
{
	if ( LogFileName != NULL )
		our_LogFile = f_open( LogFileName, TEXT( "wt" ));
	else
		our_LogFile = stderr;

	return ( our_LogFile != NULL );
}



//=============================================================================
bool CDebugger::CloseDebuggerLogFile( void )
//=============================================================================
{
	if ( our_LogFile != NULL && our_LogFile != stderr ) {
		if ( fclose( our_LogFile ) == 0 )
			our_LogFile = NULL;
	} else
		our_LogFile = NULL;

	return ( our_LogFile == NULL );
}


//=============================================================================
void CDebugger::WriteLog( const char_t Data[] )
//=============================================================================
{
	if ( our_LogFile != NULL ) {
		f_print_f( our_LogFile, TEXT( "%s\n" ), Data );
		fflush( our_LogFile );
	}
}


		
//=============================================================================
void CDebugger::Log( const char_t Format[], ... )
//=============================================================================
{
	va_list Arguments;
	char_t Output[ kDefaultOutputSize ];

	va_start( Arguments, Format );
	PrepareOutput( Output, countof( Output ), Name(), Format, Arguments );
	va_end( Arguments );

	WriteLog( Output );
}



//#############################################################################
//
// Miscellaneous
//
//#############################################################################


//=============================================================================
void CDebugger::Break( void )
//=============================================================================
{
	if ( IsDebugging() ) {
		debug_break();
	}
}


/*
//=============================================================================
void CDebugger::Rename( const string_t &Name )
//=============================================================================
{
	my_Name = Name;
}
*/


//=============================================================================
const string_t &CDebugger::Name( void ) const
//=============================================================================
{
	return ( my_Name );
}

} // namespace AidKit


/*
//=============================================================================
COutput &CDebugger::Write( const char_t Value[], size_t ValueLength, const type_info & )
//=============================================================================
{
	if ( IsDebugging() ) {
		my_StreamOutput.append( Value, ValueLength );
	}
	return ( *this );
}



//=============================================================================
COutput &CDebugger::Flush( void )
//=============================================================================
{
	if ( IsDebugging() ) {
		Trace( TEXT( "%.*s" ), my_StreamOutput.length(), my_StreamOutput.c_str() );
		my_StreamOutput.erase();
	}
	return ( *this );
}
*/

