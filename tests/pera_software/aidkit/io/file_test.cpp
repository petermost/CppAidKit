// Copyright 2015 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#include <pera_software/aidkit/io/file.hpp>
#include "file_test.hpp"
#include <QTest>

namespace pera_software::aidkit::io {

using namespace std;

// Explicit template instantiations to catch compiler errors early:

template class basic_file< char, file_locked_category >;
template class basic_file< wchar_t, file_locked_category >;

static FileTest fileTest;

#if defined( AIDKIT_MINGW )
static void nullHandler( const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t ) {
}
#endif

static const file::open_modes WRITE_ACCESS = file::open_modes( file::open_mode::write ) | file::open_mode::extended;

static const char *makeTemporaryFilename() {
	return "pera_software.aidkit.io.file_test.cpp.dat";
}

//==================================================================================================

FileTest::FileTest() {
	#if defined( AIDKIT_MINGW )
		// Disable the invalid error handler from the msvcrt:

		_set_invalid_parameter_handler( nullHandler );
#endif
}

//==================================================================================================

void FileTest::initTestCase() {
	remove_file_if_exists( makeTemporaryFilename() );
}

//==================================================================================================

void FileTest::cleanupTestCase() {
	remove_file_if_exists( makeTemporaryFilename() );
}

//==================================================================================================

template < typename Functor >
	void expectError( const error_code &expectedErrorCode, Functor &&functor ) {
		try {
			functor();
			QFAIL( "Expected thrown system_error!" );
		} catch ( const system_error &error ) {
			QCOMPARE( error.code(), expectedErrorCode );
		}
	}

//==================================================================================================

template < typename Functor >
	void expectSuccess( Functor &&functor ) {
		try {
			functor();
		} catch ( const system_error &error ) {
			string failMessage = "Unexcepted system error thrown: " + error.code().message() + " !";
			QFAIL( failMessage.c_str() );
		}
	}

//==================================================================================================

void FileTest::testInvalidIsEof() {
	expectError( make_error_code( errc::invalid_argument ), [ & ] {
		file file;
		file.is_eof();
	});
}

//==================================================================================================

void FileTest::testInvalidGet() {
	expectError( make_error_code( errc::invalid_argument ), [ & ] {
		file file;
		file.get();
	});
}

//==================================================================================================

void FileTest::testInvalidIsError() {
	expectError( make_error_code( errc::invalid_argument ), [ & ] {
		file file;
		file.is_error();
	});
}

//==================================================================================================

void FileTest::testInvalidClose() {
	expectError( make_error_code( errc::invalid_argument ), [ & ] {
		file file;
		file.close();
	});
}

//==================================================================================================

void FileTest::testInvalidCloseAndClose() {
	expectError( make_error_code( errc::invalid_argument ), [ & ] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), WRITE_ACCESS );
		file.close();
		file.close();
	});
}

//==================================================================================================

void FileTest::testOpenFailed() {
	expectError( make_error_code( errc::no_such_file_or_directory ), [ & ] {
		file file;
		string fileName = makeTemporaryFilename();
		file.open( fileName.c_str(), file::open_mode::read );
	});
}

//==================================================================================================

void FileTest::testOpenSucceeded() {
	expectSuccess([ & ] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter( fileName );

		file file;
		file.open( fileName.c_str(), file::open_mode::write );
	});
}

//==================================================================================================

void FileTest::testGetCharReturnsEof() {
	expectError( make_error_code( file_error::eof ), [ & ] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), WRITE_ACCESS );
		file.get();
	});
}

//==================================================================================================

void FileTest::testGetStringReturnsEof() {
	expectError( make_error_code( file_error::eof ), [ & ] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), WRITE_ACCESS );

		char str[ 100 ];
		file.get( str, 10 );
	});
}

//==================================================================================================

void FileTest::testReadReturnsEof() {
	expectError( make_error_code( file_error::eof ), [ & ] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), WRITE_ACCESS );

		char buffer[ 100 ];
		file.read( buffer, sizeof( buffer ), 1 );
	});
}

//==================================================================================================

void FileTest::testCloseAndDestructor() {
	expectSuccess([ & ] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), WRITE_ACCESS );
		file.close();
	});
}

//==================================================================================================

void FileTest::testOpenReadWrite() {
	expectError( make_error_code( errc::no_such_file_or_directory ), [ & ] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), file::open_modes( file::open_mode::write ) | file::open_mode::read );
	});
}

}
