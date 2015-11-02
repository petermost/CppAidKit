// CountFileTypes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

enum FileType {
	FileType_UNKNOWN,
	FileType_NATIVE,
	FileType_MANAGED
};
	
struct TypeOccurences {
	TypeOccurences()
	{
		natives = managed = errors = 0;
	}

	void count( FileType type )
	{
		switch ( type ) {
			case FileType_NATIVE:
				++natives;
				break;

			case FileType_MANAGED:
				++managed;
				break;

			case FILE_TYPE_UNKNOWN:
				++errors;
				break;
		}
	}

	int natives;
	int managed;
	int errors;
};

union ImageNtHeaders {
	IMAGE_NT_HEADERS32 header32;
	IMAGE_NT_HEADERS64 header64;
};


void checkSuccess( bool success )
{
	if ( !success ) {
		int error = errno;
		const char *message = strerror( error );
		throw ( exception( message ));
	};
}

FileType determineFileType( const wstring &path )
{
	try {
		size_t n;
		WORD machine = IMAGE_FILE_MACHINE_UNKNOWN;
		FileType fileType = FileType_UNKNOWN;
		IMAGE_DOS_HEADER dosHeader;
		ImageNtHeaders ntHeaders;

		FILE *file = _wfopen( path.c_str(), L"rb" );
		checkSuccess( file != NULL );
		checkSuccess(( n = fread( &dosHeader, 1, sizeof( dosHeader ), file )) == sizeof( dosHeader ));
		checkSuccess( fseek( file, dosHeader.e_lfanew, SEEK_SET ) == 0 );
		checkSuccess(( n = fread( &ntHeaders, 1, sizeof( ntHeaders ), file )) == sizeof( ntHeaders ));
		fclose( file );

		IMAGE_DATA_DIRECTORY *imageDataDirectory = NULL;
		switch ( ntHeaders.header32.OptionalHeader.Magic ) {
			case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
				machine = ntHeaders.header32.FileHeader.Machine;
				imageDataDirectory = &ntHeaders.header32.OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ];
				break;

			case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
				machine = ntHeaders.header64.FileHeader.Machine;
				imageDataDirectory = &ntHeaders.header64.OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ];
				break;

			default:
				throw exception( "Unknown 'ntHeaders.header32.OptionalHeader.Magic' value!" );
				break;
		}
		if ( imageDataDirectory->Size > 0 )
			fileType = FileType_MANAGED;
		else
			fileType = FileType_NATIVE;

		return ( fileType );
	}
	catch ( const exception &error ) {
		wprintf( L"Error '%s' reading '%S'!\n", path.c_str(), error.what() );

		return ( FileType_UNKNOWN );
	}
}


bool hasExtension( const wstring &fileName, const wstring &extension )
{
    if ( fileName.length() > extension.length() ) {
        return ( fileName.compare( fileName.length() - extension.length(), extension.length(), extension) == 0 );
    } else {
        return ( false );
    }
}


void parseDirectory( const wstring &path, const wstring &pattern, TypeOccurences *occurences )
{
	const wstring SLASH( L"\\" );
	const wstring CURRENT( L"." );
	const wstring PARENT( L".." );
	const wstring EXE_EXTENSION( L".exe" );
	const wstring DLL_EXTENSION( L".dll" );

	WIN32_FIND_DATA fileInfo;
	HANDLE directoryHandle;
	
	wprintf( L"." );
	if (( directoryHandle = FindFirstFile(( path + SLASH + pattern ).c_str(), &fileInfo )) != INVALID_HANDLE_VALUE ) {
		do {
			if ( fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
				&& CURRENT != fileInfo.cFileName && PARENT != fileInfo.cFileName )
				{
				parseDirectory( path + SLASH + fileInfo.cFileName, pattern, occurences );
			}
			else {
				wstring fileName = fileInfo.cFileName;
				if ( hasExtension( fileName, EXE_EXTENSION ) || hasExtension( fileName, DLL_EXTENSION )) {
					wstring filePath = path + SLASH + fileName;
					FileType type = determineFileType( filePath );
					wstring message;
					switch ( type ) {
						case FileType_UNKNOWN:
							message = L"ERROR!";
							break;

						case FileType_NATIVE:
							message = L"NATIVE";
							break;

						case FileType_MANAGED:
							message = L"MANAGED";
							break;
					}
					occurences->count( type );

					if ( type == FileType_MANAGED )
						wprintf( L"\n%s = %s\n", filePath.c_str(), message.c_str() );
				}
			}
		}
		while ( FindNextFile( directoryHandle, &fileInfo ));
		FindClose( directoryHandle );
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		TypeOccurences occurences;

		for ( int i = 1; i < argc; ++i )
			parseDirectory( argv[ i ], L"*", &occurences );

		wprintf( L"\nNatives: %d, Managed: %d, Errors: %d\n", occurences.natives, occurences.managed, occurences.errors );
	}
	catch ( const exception &error ) {
		printf( "Error: %s", error.what() );
	}
	return 0;
}

