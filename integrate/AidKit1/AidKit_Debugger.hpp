#ifndef AIDKIT_DEBUGGER_HPP
#define AIDKIT_DEBUGGER_HPP

#include "AidKit.hpp"
#include "AidKit_Static.hpp"
#include "AidKit_Unicode.hpp"
#include "AidKit_ThreadLock.hpp"
#include "AidKit_DebuggerDisplay.hpp"

#include <cstdio>
#include <string>
#include <list>

namespace AidKit {

	class CDebugger;

	//-----------------------------------------------------------------------------
	class CDebuggerSettings {
	//-----------------------------------------------------------------------------
		public:
			CDebuggerSettings( void );
			virtual ~CDebuggerSettings( void );

			virtual bool IsTraceEnabled( const CDebugger *, bool DefaultValue );
			virtual bool IsDumpEnabled( const CDebugger *, bool DefaultValue );
	};


	//-----------------------------------------------------------------------------
	class CDebugger {
	//-----------------------------------------------------------------------------
		public:
			enum { kDefaultOutputSize = 1000 };

			static const string_t LOG_FILE_NAME;

			// General debugging support:

			static bool EnableDebugging( bool Enable );
			static bool IsDebugging( void );

			static CDebuggerDisplay *ExchangeDebuggerDisplay( CDebuggerDisplay * );
			static CDebuggerSettings *ExchangeDebuggerSettings( CDebuggerSettings * );

			CDebugger( const string_t &Name, bool IsTraceEnabled = true, bool IsDumpEnabled = true,
				bool IsStandalone = false );

			~CDebugger( void );

			// Trace functions:

			void Trace( const char_t Format[], ... );
			void VTrace( const char_t Format[], va_list Arguments );

			bool IsTraceEnabled( void ) const;

			// Dump functions:

			void Dump( const void *Memory, size_t MemoryLength );
			void Dump( const string_t &MemoryName, const void *Memory, size_t MemoryLength );

			bool IsDumpEnabled( void ) const;

			// Log functions:

			void Log( const char_t Format[], ... );

			static bool OpenDebuggerLogFile( const char_t LogFileName[] = NULL );
			static bool CloseDebuggerLogFile( void );

			// Miscellaneous functions:

			static void Break( void );

			// void Rename( const string_t &Name );
			const string_t &Name( void ) const;

		private:
			// Compiler generated:
			// CDebugger( const CDebugger & );
			// CDebugger &operator = ( const CDebugger & );

			void Display( const char_t Data[] );
			void WriteLog( const char_t Data[] );

			static CThreadGuard our_ThreadGuard;

			static bool our_IsDebugging;

			static CDebuggerSettings our_DefaultSettings;
			static CDebuggerSettings *our_pSettings;

			static CDebuggerDisplay our_DefaultDisplay;
			static CDebuggerDisplay *our_pDisplay;

			string_t my_Name;

			bool my_IsStandalone;
			bool my_IsTraceEnabled;
			bool my_IsDumpEnabled;

			static std::FILE *our_LogFile;
	};

} // namespace AidKit

#endif
