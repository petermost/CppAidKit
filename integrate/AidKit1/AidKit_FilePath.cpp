#include "AidKit_FilePath.hpp"
#include "AidKit_StlHelper.hpp"
#include <string.h>
#include "AidKit_Warnings.hpp"


using namespace std;

namespace AidKit {

//=============================================================================
void SplitPath( const char_t *Path, string_t *pDrive, vector< string_t > *pDirectories,
	string_t *pName, string_t *pExtension )
//=============================================================================
{
	const char_t *p = Path;
	do {
		if ( *p == TEXT( ':' )) {
			pDrive->assign( Path, p + 1 );
			Path = p + 1;
		}
		else if ( *p == TEXT( '/' ) || *p == TEXT( '\\' )) {
			pDirectories->push_back( string_t( Path, p + 1 ));
			Path = p + 1;
		}
		else if ( *p == TEXT( '\0' )) {
			const char_t *pDot = str_r_chr( Path, TEXT( '.' ));
			if ( pDot != NULL ) {
				pName->assign( Path, pDot );
				pExtension->assign( pDot, p );
			} else {
				pName->assign( Path, p );
			}
			Path = p + 1;
		}
	} while ( *p++ != TEXT( '\0' ));
}



//=============================================================================
void MergePath( char_t *Path, const string_t &Drive, const vector< string_t > &Directories,
	const string_t &Name, const string_t &Extension )
//=============================================================================
{
	vector< string_t >::const_iterator itDirectory;

	Path += Drive.copy( Path, Drive.length() );
	for ( itDirectory = Directories.begin(); itDirectory != Directories.end(); ++itDirectory ) {
		Path += itDirectory->copy( Path, itDirectory->length() );
	}
	Path += Name.copy( Path, Name.length() );
	Path += Extension.copy( Path, Extension.length() );

	*Path = TEXT( '\0' );
}

//#############################################################################
//#############################################################################
//#############################################################################
//###
//### CFilePath
//###
//#############################################################################
//#############################################################################
//#############################################################################


//=============================================================================
CFilePath::CFilePath( const char_t Path[] )
//=============================================================================
{
	SplitPath( Path, &my_Drive, &my_Directories, &my_Name, &my_Extension );
}



//=============================================================================
CFilePath::~CFilePath( void )
//=============================================================================
{
}



//=============================================================================
const char_t *CFilePath::operator = ( const char_t Path[] )
//=============================================================================
{
	SplitPath( Path, &my_Drive, &my_Directories, &my_Name, &my_Extension );
	return ( CFilePath::Path() );
}



//=============================================================================
void CFilePath::ChangeDrive( const char_t Drive[] )
//=============================================================================
{
	my_Drive = Drive;
}



//=============================================================================
void CFilePath::ChangeDirectoryAt( int Position, const char_t Directory[] )
	throw ( out_of_range )
//=============================================================================
{
	vector< string_t >::size_type Index = ( Position >= 0 ) ? Position : my_Directories.size() + Position;

	vector_at( my_Directories, Index ) = Directory;
}



//=============================================================================
void CFilePath::ChangeName( const char_t Name[] )
//=============================================================================
{
	my_Name = Name;
}



//=============================================================================
void CFilePath::ChangeExtension( const char_t Extension[] )
//=============================================================================
{
	my_Extension = Extension;
}





//=============================================================================
const char_t *CFilePath::Path( void )
//=============================================================================
{
	MergePath( my_szPath, my_Drive, my_Directories, my_Name, my_Extension );
	return ( my_szPath );
}




//=============================================================================
const char_t *CFilePath::Directory( void )
//=============================================================================
{
	MergePath( my_szDirectory, my_Drive, my_Directories, string_t(), string_t() );
	return ( my_szDirectory );
}



//=============================================================================
const char_t *CFilePath::Drive( void ) const
//=============================================================================
{
	return ( my_Drive.c_str() );
}




//=============================================================================
const char_t *CFilePath::DirectoryAt( int Position ) const
	throw ( out_of_range )
//=============================================================================
{
	vector< string_t >::size_type Index = ( Position >= 0 ) ? Position : my_Directories.size() + Position;

	return ( vector_at( my_Directories, Index ).c_str() );
}



//=============================================================================
const char_t *CFilePath::Name( void ) const
//=============================================================================
{

	return ( my_Name.c_str() );
}


//=============================================================================
const char_t *CFilePath::Extension( void ) const
//=============================================================================
{
	return ( my_Extension.c_str() );
}


//=============================================================================
CFilePath::operator const char_t * ( void )
//=============================================================================
{
	return ( Path() );
}

} // namespace AidKit
