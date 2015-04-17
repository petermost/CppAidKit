#include "stdafx.h"
#include "File.hpp"
#include <io.h>
#include <cerrno>
#include <stdarg.h>


using namespace std;
using namespace boost;
using namespace filesystem;

using std::shared_ptr;

//#########################################################################################################

FileNotFoundException::FileNotFoundException( const path &fileName )
	: FileException( ENOENT )
{
	mFileName = fileName;
}

const path &FileNotFoundException::FileName() const
{
	return mFileName;
}

//#########################################################################################################

EndOfFileException::EndOfFileException()
	: FileException( EOF, L"EOF" )
{
}

//#########################################################################################################

File::File()
{
}


File::File( shared_ptr< FILE > file )
{
	if ( file )
		mFile = file;
	else
		BOOST_THROW_EXCEPTION( FileException( EINVAL ));
}

File::File( const path &fileName, open_mode mode )
{
	open( fileName, mode );
}


File::~File()
{
}


static const wchar_t *make_mode_string( File::open_mode mode )
{
	switch ( mode )
	{
		case File::open_mode::read:
			return L"rb";

		case File::open_mode::write:
			return L"wb";

		case File::open_mode::append:
			return L"ab";

		case File::open_mode::read_write:
			return L"r+b";

		case File::open_mode::write_read:
			return L"w+b";

		case File::open_mode::append_read_write:
			return L"a+b";

		default:
			return L"";
	}
}


void File::open( const path &fileName, open_mode mode )
{
	FILE *file;

	if (( file = _wfopen( fileName.c_str(), make_mode_string( mode ))) != nullptr )
	{
		// We don't bind the deleter to File::close to prevent exceptions from the destructor.

		mFile = shared_ptr< FILE >( file, _fclose_nolock );
		mName = fileName;
	}
	else
	{
		if ( errno == ENOENT )
			BOOST_THROW_EXCEPTION( FileNotFoundException( fileName ));
		else
			BOOST_THROW_EXCEPTION( FileException::LastError() );
	}
}


void File::close()
{
	if ( mFile )
	{
		// Close the file via the deleter because we don't know whether to use fclose or _fclose_nolock!

		auto deleter = get_deleter< int (*)( FILE * )>( mFile );
		if ( deleter != nullptr && ( *deleter )( mFile.get() ) == EOF )
			BOOST_THROW_EXCEPTION( FileException::LastError() );
	}
}


void File::set_buffer( void *buffer, buffer_mode mode, size_t size )
{
	setvbuf( mFile.get(), static_cast< char * >( buffer ), static_cast< int >( mode ), size );
}


void File::put( const string &str )
{
	if ( fputs( str.c_str(), mFile.get() ) == EOF && error() )
		BOOST_THROW_EXCEPTION( FileException::LastError() );
}


void File::put( const wstring &str )
{
	if ( fputws( str.c_str(), mFile.get() ) == WEOF && error() )
		BOOST_THROW_EXCEPTION( FileException::LastError() );
}


int File::print( const char format[], ... )
{
	va_list arguments;

	va_start( arguments, format );
	int count = vfprintf( mFile.get(), format, arguments );
	va_end( arguments );

	if ( count < 0 )
		BOOST_THROW_EXCEPTION( FileException::LastError() );

	return count;
}

int File::print( const wchar_t format[], ... )
{
	va_list arguments;

	va_start( arguments, format );
	int count = vfwprintf( mFile.get(), format, arguments );
	va_end( arguments );

	if ( count < 0 )
		BOOST_THROW_EXCEPTION( FileException::LastError() );

	return count;
}


File::position_t File::tell()
{
	position_t position;

	if (( position = _ftelli64_nolock( mFile.get() )) != -1 )
		return position;
	else
		BOOST_THROW_EXCEPTION( FileException::LastError() );
}

void File::seek( position_t position, origin origin )
{
	if ( _fseeki64_nolock( mFile.get(), position, static_cast< int >( origin )) != 0 )
		BOOST_THROW_EXCEPTION( FileException::LastError() );
}

void File::rewind()
{
	::rewind( mFile.get() ); 
}

void File::flush()
{
	if ( fflush( mFile.get() ) == EOF )
		BOOST_THROW_EXCEPTION( FileException::LastError() );
}

const path &File::name() const
{
	return mName;
}

File::length_t File::length() const
{
	int64_t length;

	if (( length = _filelengthi64( _fileno( mFile.get() ))) != -1 )
		return length;
	else
		BOOST_THROW_EXCEPTION( FileException::LastError() );
}

} }


//fpos_t getpos()
//{
//	fpos_t pos;

//	if ( fgetpos( mFile, &pos ) == 0 )
//		return pos;
//	else
//		throw FileException::LastError();
//}

//void setpos( fpos_t pos )
//{
//	if ( fsetpos( mFile, &pos ) != 0 )
//		throw FileException::LastError();
//}

