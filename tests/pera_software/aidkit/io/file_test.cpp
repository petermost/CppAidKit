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
			// We want to be notified when the removal fails, so we throw an exception:

			error_code errorCode;
			if ( !remove_file( fileName_.c_str(), &errorCode ) && errorCode != errc::no_such_file_or_directory )
				throw system_error( errorCode );
		}

	private:
		string fileName_;
};

#if defined( AIDKIT_MINGW )
static void nullHandler( const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t ) {
}
#endif

static const enum_flags< file::open_mode > WRITE_ACCESS({ file::open_mode::write, file::open_mode::extended });

//==================================================================================================

FileTest::FileTest() {
	#if defined( AIDKIT_MINGW )
		// Disable the invalid error handler from the msvcrt:

		_set_invalid_parameter_handler( nullHandler );
	#endif
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
		string fileName = make_temporary_filename();
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
		string fileName = make_temporary_filename();
		file.open( fileName.c_str(), file::open_mode::read );
	});
}

//==================================================================================================

void FileTest::testOpenSucceeded() {
	expectSuccess([ & ] {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file;
		file.open( fileName.c_str(), file::open_mode::write );
	});
}

//==================================================================================================

void FileTest::testGetCharReturnsEof() {
	expectError( make_error_code( file_error::eof ), [ & ] {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), WRITE_ACCESS );
		file.get();
	});
}

//==================================================================================================

void FileTest::testGetStringReturnsEof() {
	expectError( make_error_code( file_error::eof ), [ & ] {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), WRITE_ACCESS );

		char str[ 100 ];
		file.get( str, 10 );
	});
}

//==================================================================================================

void FileTest::testReadReturnsEof() {
	expectError( make_error_code( file_error::eof ), [ & ] {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), WRITE_ACCESS );

		char buffer[ 100 ];
		file.read( buffer, sizeof( buffer ), 1 );
	});
}

//==================================================================================================

void FileTest::testCloseAndDestructor() {
	expectSuccess([ & ] {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), WRITE_ACCESS );
		file.close();
	});
}

//==================================================================================================

void FileTest::testOpenReadWrite() {
	expectError( make_error_code( errc::invalid_argument ), [ & ] {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file( fileName.c_str(), make_flags({ file::open_mode::write, file::open_mode::read }));
	});
}

} } }
