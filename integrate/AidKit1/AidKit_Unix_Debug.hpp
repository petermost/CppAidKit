#ifndef AIDKIT_UNIX_DEBUG_HPP
#define AIDKIT_UNIX_DEBUG_HPP

#include "../AidKit.hpp"
#include "../AidKit_Unicode.hpp"
#include <stdexcept>
#include <dlfcn.h> // Add '-ldl' '-rdynamic' to the linker options!

namespace AidKit {

	namespace Unix {

		void debug_printf( const char_t Format[], ... );

		#if defined( AIDKIT_I386 )
			#define debug_break() asm( "int $3" )
		#endif

		//-----------------------------------------------------------------------------
		class CCallStack {
		//-----------------------------------------------------------------------------
			public:
				CCallStack( void )
					throw ( std::bad_alloc );

				~CCallStack( void )
					throw();

				// Compiler generated copy constructor/assignment operator are safe.

				size_t Size( void ) const;

				const void *SymbolAt( size_t i ) const
					throw ( std::out_of_range );

				const char_t *SymbolNameAt( size_t i ) const
					throw ( std::out_of_range );

			private:
				void *my_Stack[ 200 ];
				int my_Size;
				mutable Dl_info my_Info;
		};

		//-----------------------------------------------------------------------------
		class CSymbolTable {
		//-----------------------------------------------------------------------------
			public:
				CSymbolTable( size_t DemanglingBufferSize = 255 )
					throw ( std::bad_alloc );

				~CSymbolTable( void )
					throw();

				const char_t *DemangleName( const char_t MangledName[] )
					throw ( std::bad_alloc, std::invalid_argument );

			private:
				CSymbolTable( const CSymbolTable & );
				CSymbolTable &operator = ( const CSymbolTable & );

				char *my_pDemanglingBuffer;
				size_t my_DemanglingBufferSize;
		};
	}

}

#endif
