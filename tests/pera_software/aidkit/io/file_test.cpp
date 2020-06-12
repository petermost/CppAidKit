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

#include <gtest/gtest.h>
#include <pera_software/aidkit/io/file.hpp>

namespace pera_software::aidkit::io {

using namespace std;
using namespace filesystem;

static path makeTemporaryFilename()
{
	return make_temporary_filename("file_test.dat");
}

class FileTest : public testing::Test {
	protected:
		void SetUp() override;
		void TearDown() override;
};

void FileTest::SetUp()
{
	// Try to remove the temporary file in the TearDown() method was not called:
	remove_file_if_exists(makeTemporaryFilename());
}

void FileTest::TearDown()
{
	remove_file_if_exists(makeTemporaryFilename());
}

// Explicit template instantiations to catch compiler errors early:

template class basic_file<file_locked_category>;

static const file::open_modes WRITE_ACCESS = file::open_modes(file::open_mode::write) | file::open_mode::extended;

//==================================================================================================

template <typename Functor>
	void expectError(const error_code &expectedErrorCode, Functor &&functor)
	{
		try {
			functor();
			FAIL() << "Expected thrown 'system_error'!";
		} catch (const system_error &error) {
			ASSERT_EQ(error.code(), expectedErrorCode);
		}
	}

//==================================================================================================

template <typename Functor>
	void expectSuccess(Functor &&functor)
	{
		try {
			functor();
		} catch (const system_error &error) {
			string failMessage = "Unexcepted 'system_error' thrown: " + error.code().message() + " !";
			FAIL() << failMessage;
		}
	}

//==================================================================================================

TEST_F(FileTest, testInvalidIsEof)
{
	expectError(make_error_code(errc::invalid_argument), [&] {
		file file;
		file.is_eof();
	});
}

//==================================================================================================

TEST_F(FileTest, testInvalidGet)
{
	expectError(make_error_code(errc::invalid_argument), [&] {
		file file;
		file.get();
	});
}

//==================================================================================================

TEST_F(FileTest, testInvalidIsError)
{
	expectError(make_error_code(errc::invalid_argument), [&] {
		file file;
		file.is_error();
	});
}

//==================================================================================================

TEST_F(FileTest, testInvalidClose)
{
	expectError(make_error_code(errc::invalid_argument), [&] {
		file file;
		file.close();
	});
}

//==================================================================================================

TEST_F(FileTest, testInvalidCloseAndClose)
{
	expectError(make_error_code(errc::invalid_argument), [&] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter(fileName);

		file file(fileName.c_str(), WRITE_ACCESS);
		file.close();
		file.close();
	});
}

//==================================================================================================

TEST_F(FileTest, testOpenFailed)
{
	expectError(make_error_code(errc::no_such_file_or_directory), [&] {
		file file;
		string fileName = makeTemporaryFilename();
		file.open(fileName.c_str(), file::open_mode::read);
	});
}

//==================================================================================================

TEST_F(FileTest, testOpenSucceeded)
{
	expectSuccess([&] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter(fileName);

		file file;
		file.open(fileName.c_str(), file::open_mode::write);
	});
}

//==================================================================================================

TEST_F(FileTest, testGetCharReturnsEof)
{
	expectError(make_error_code(file_error::eof), [&] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter(fileName);

		file file(fileName.c_str(), WRITE_ACCESS);
		file.get();
	});
}

//==================================================================================================

TEST_F(FileTest, testGetStringReturnsEof)
{
	expectError(make_error_code(file_error::eof), [&] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter(fileName);

		file file(fileName.c_str(), WRITE_ACCESS);

		char str[100];
		file.get(str, 10);
	});
}

//==================================================================================================

TEST_F(FileTest, testReadReturnsEof)
{
	expectError(make_error_code(file_error::eof), [&] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter(fileName);

		file file(fileName.c_str(), WRITE_ACCESS);

		char buffer[100];
		file.read(buffer, sizeof(buffer), 1);
	});
}

//==================================================================================================

TEST_F(FileTest, testCloseAndDestructor)
{
	expectSuccess([&] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter(fileName);

		file file(fileName.c_str(), WRITE_ACCESS);
		file.close();
	});
}

//==================================================================================================

TEST_F(FileTest, testOpenReadWrite)
{
	expectError(make_error_code(errc::no_such_file_or_directory), [&] {
		string fileName = makeTemporaryFilename();
		file_deleter fileDeleter(fileName);

		file file(fileName.c_str(), file::open_modes(file::open_mode::write) | file::open_mode::read);
	});
}


}
