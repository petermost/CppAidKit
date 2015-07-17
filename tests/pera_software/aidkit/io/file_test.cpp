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

namespace pera_software { namespace aidkit { namespace io {

using namespace std;

// Explicit template instantiations to catch compiler errors early:

template class basic_file< char, file_locked_category >;
template class basic_file< wchar_t, file_locked_category >;

//template bool basic_file< char, file_locked_category >::print< int, int >( error_code *, const char *, int, int  );
//template bool basic_file< char, file_locked_category >::is_eof() const;

static FileTest fileTest;

// An RAII file deleter for deleting/cleaning up the temporary files:

class file_deleter {
	public:
		file_deleter( const string &fileName ) {
			fileName_ = fileName;
		}

		// Destructors in C++11 are implicitly declared as noexcept, so we have to explicitly allow
		// exceptions (http://en.cppreference.com/w/cpp/language/destructor#Exceptions):

		~file_deleter() noexcept( false ) {
			// We want to be notified when the removal fails, so we call the throwing remove version:

			remove_file( fileName_.c_str() );
		}

	private:
		string fileName_;
};

static void nullHandler( const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t ) {
}

FileTest::FileTest() {
	#if defined( AIDKIT_MINGW )
		// Disable the invalid error handler from the msvcrt:

		_set_invalid_parameter_handler( nullHandler );
	#endif
}

template < typename Functor >
	void expectSystemError( Functor &&functor, const error_code &expectedErrorCode ) {
		try {
			functor();
			QFAIL( "Expected thrown system_error!" );
		} catch ( const system_error &error ) {
			QVERIFY( error.code() == expectedErrorCode );
		}
	}

void FileTest::testInvalidIsEof() {
	expectSystemError([ & ] {
		file file;
		file.is_eof();
	}, make_error_code( errc::invalid_argument ));
}

void FileTest::testInvalidGet() {
	expectSystemError([ & ] {
		file file;
		file.get();
	}, make_error_code( errc::invalid_argument ));
}

void FileTest::testInvalidIsError() {
	expectSystemError([ & ] {
		file file;
		file.is_error();
	}, make_error_code( errc::invalid_argument ));
}

void FileTest::testInvalidClose() {
	expectSystemError([ & ] {
		file file;
		file.close();
	}, make_error_code( errc::invalid_argument ));
}

void FileTest::testInvalidCloseAndClose() {
	expectSystemError([ & ] {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), "w+" );
		file.close();
		file.close();
	}, make_error_code( errc::invalid_argument ));
}

void FileTest::testOpenFailed() {
	expectSystemError([ & ] {
		file file;
		string fileName = make_temporary_filename();
		file.open( fileName.c_str(), "r" );
	}, make_error_code( errc::no_such_file_or_directory ));
}

void FileTest::testOpenSucceeded() {
	try {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file;
		file.open( fileName.c_str(), "w" );
	} catch ( const system_error & ) {
		QFAIL( "Unexpected system_error thrown!" );
	}
}

void FileTest::testGetCharReturnsEof() {
	try {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), "w+" );
		file.get();
		QFAIL( "Expected thrown system_error( file_error::eof )!" );
	} catch ( const system_error &error ) {
		QVERIFY( error.code() == file_error::eof );
	}
}

void FileTest::testGetStringReturnsEof() {
	try {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), "w+" );

		char str[ 100 ];
		file.get( str, 10 );
		QFAIL( "Expected thrown system_error( file_error::eof )!" );
	} catch ( const system_error &error ) {
		QVERIFY( error.code() == file_error::eof );
	}
}

void FileTest::testReadReturnsEof() {
	try {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), "w+" );

		char buffer[ 100 ];
		file.read( buffer, sizeof( buffer ), 1 );
		QFAIL( "Expected thrown system_error( file_error::eof )!" );
	} catch ( const system_error &error ) {
		QVERIFY( error.code() == file_error::eof );
	}
}

void FileTest::testCloseAndDestructor() {
	try {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), "w+" );
		file.close();
	} catch ( const system_error & ) {
		QFAIL( "Unexpected system_error thrown!" );
	}
}


} } }
