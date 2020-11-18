// Copyright 2020 Peter Most, PERA Software Solutions GmbH
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
#include <pera_software/aidkit/qt/core/Path.hpp>
#include <pera_software/aidkit/qt/core/Strings.hpp>
#include <pera_software/aidkit/qt/core/StringPrinter.hpp>

namespace pera_software::aidkit::qt {

TEST(PathTest, testEmptyPath)
{
	Path path;

	ASSERT_TRUE(path.drive().isEmpty());

	ASSERT_TRUE(path.directory(0).isEmpty());
	ASSERT_TRUE(path.directory(1).isEmpty());
	ASSERT_TRUE(path.directory(-1).isEmpty());

	ASSERT_TRUE(path.name().isEmpty());

	ASSERT_TRUE(path.extension().isEmpty());
	ASSERT_TRUE(path.extensionAt(0).isEmpty());
	ASSERT_TRUE(path.extensionAt(1).isEmpty());
	ASSERT_TRUE(path.extensionAt(-1).isEmpty());
}

TEST(PathTest, testFullPath)
{
	Path path("D:/dir1/dir2/name.ext1.ext2"_qs);

	ASSERT_EQ(path.drive(), "D:"_qs);

	ASSERT_EQ(path.directory(0), "/"_qs);

	ASSERT_EQ(path.directory(1), "dir1/"_qs);
	ASSERT_EQ(path.directory(-2), "dir1/"_qs);

	ASSERT_EQ(path.directory(2), "dir2/"_qs);
	ASSERT_EQ(path.directory(-1), "dir2/"_qs);

	ASSERT_EQ(path.name(), "name"_qs);

	ASSERT_EQ(path.extensionAt(0), ".ext1"_qs);
	ASSERT_EQ(path.extensionAt(-2), ".ext1"_qs);

	ASSERT_EQ(path.extensionAt(1), ".ext2"_qs);
	ASSERT_EQ(path.extensionAt(-1), ".ext2"_qs);

	ASSERT_EQ(path.extension(), ".ext2"_qs);
}

TEST(PathTest, testDriveSetterGetter)
{
	Path path;

	path.setDrive("df0"_qs);
	ASSERT_EQ(path.drive(), "df0:"_qs);

	path.setDrive();
	ASSERT_TRUE(path.drive().isEmpty());
}

TEST(PathTest, testDirectorySetterGetter)
{
	Path path("df0:/dir1/dir2/name.ext"_qs);
	ASSERT_EQ(path.directory(), "/dir1/dir2/"_qs);
}

}
