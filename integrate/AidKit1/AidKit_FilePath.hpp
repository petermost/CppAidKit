#ifndef AIDKIT_FILE_PATH
#define AIDKIT_FILE_PATH

#include "AidKit.hpp"
#include "AidKit_System.hpp"
#include "AidKit_Unicode.hpp"

#if defined( AIDKIT_MSC )
	#pragma warning( disable : 4786 ) // identifier was truncated to '255' characters in the browser information
#endif

#include <string>
#include <vector>
#include <stdexcept>

namespace AidKit {
	const char_t kDriveSeparator = TEXT( ':' );
	
	void SplitPath( const char_t *Path, string_t *pDrive, std::vector< string_t > *pDirectories,
		string_t *pName, string_t *pExtension );

	void MergePath( char_t *Path, const string_t &Drive, const std::vector< string_t > &Directories,
		const string_t &Name, const string_t &Extension );

	/*---------------------------------------------------------------------------*/
	class CFilePath {
	/*---------------------------------------------------------------------------*/
		public:
			explicit CFilePath( const char_t Path[] = TEXT( "" ));
			~CFilePath( void );

			const char_t *operator = ( const char_t [] );
			
			void ChangeDrive( const char_t Drive[] );
			void ChangeDirectoryAt( int Position, const char_t Directory[] )
				throw ( std::out_of_range );

			void ChangeName( const char_t Name[] );
			void ChangeExtension( const char_t Extension[] );

			const char_t *Directory( void );
			const char_t *Path( void );

			const char_t *Drive( void ) const;
			const char_t *DirectoryAt( int Position ) const
				throw ( std::out_of_range );

			const char_t *Name( void ) const;
			const char_t *Extension( void ) const;

			operator const char_t *( void );

		private:
			string_t my_Drive;
			std::vector< string_t > my_Directories;
			string_t my_Name;
			string_t my_Extension;

			char_t my_szPath[ MAX_PATH_NAME_LENGTH ];
			char_t my_szDirectory[ MAX_PATH_NAME_LENGTH ];
	};

}

#endif
