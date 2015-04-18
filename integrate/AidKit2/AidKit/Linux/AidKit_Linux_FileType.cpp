#include "AidKit_Linux_FileType.hpp"

using namespace std;

namespace PERA { namespace AidKit { namespace Linux {


FileType::FileType()
{
	if (( _cookie = magic_open( MAGIC_NONE )) == NULL )
		throw FileTypeException( 0, "Initializing libmagic (magic_open) failed!" );

	if ( magic_load( _cookie, NULL ) == -1 )
		throw FileTypeException( _cookie );
}

FileType::~FileType()
{
	if ( _cookie != NULL )
		magic_close( _cookie );
}

const std::string FileType::determineFileType( const string &fileName )
{
	const char *fileType;

	if (( fileType = magic_file( _cookie, fileName.c_str() )) != NULL )
		return string( fileType );
	else
		throw FileTypeException( _cookie );
}

//#############################################################################

FileTypeException::FileTypeException( magic_t magicCookie )
{
	_errorCode = magic_errno( magicCookie );
	_errorMessage = magic_error( magicCookie );
}


FileTypeException::FileTypeException( int errorCode, const string &errorMessage )
{
	_errorCode = errorCode;
	_errorMessage = errorMessage;
}

FileTypeException::~FileTypeException()
	throw()
{
}

const char *FileTypeException::what() const
	throw()
{
	return _errorMessage.c_str();
}

int FileTypeException::errorCode() const
{
	return _errorCode;
}

const string &FileTypeException::errorMessage() const
{
	return _errorMessage;
}

}
}
}

