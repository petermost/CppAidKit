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

		~file_deleter() {
			// We want to be notified when the removal fails, so we call the throwing remove version:

			remove_file( fileName_.c_str() );
		}

	private:
		string fileName_;
};

void FileTest::testIsEof() {
	try {
		file file;
		file.is_eof();
		QFAIL( "Expected thrown system_error( errc::invalid_argument )!" );
	} catch ( const system_error &error ) {
		QVERIFY( error.code() == errc::invalid_argument );
	}
}

void FileTest::testIsError() {
	try {
		file file;
		file.is_error();
		QFAIL( "Expected thrown system_error( errc::invalid_argument )!" );
	} catch ( const system_error &error ) {
		QVERIFY( error.code() == errc::invalid_argument );
	}
}


void FileTest::testOpenFailed() {
	try {
		file file;
		string fileName = make_temporary_filename();
		file.open( fileName.c_str(), "r" );
	} catch ( const system_error &error ) {
		QVERIFY( error.code() == errc::no_such_file_or_directory );
	}
}

void FileTest::testOpenSucceeded() {
	try {
		string fileName = make_temporary_filename();
		file_deleter fileDeleter( fileName );

		file file;
		file.open( fileName.c_str(), "w" );
	} catch ( const system_error &error ) {
		QVERIFY( !error.code() );
	}
}

} } }
