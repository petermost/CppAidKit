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
#include <pera_software/aidkit/boost/directory_guide.hpp>
#include <pera_software/aidkit/compiler.hpp>

namespace pera_software::aidkit::boost {

using namespace std;
using namespace ::boost::filesystem;

AIDKIT_PRAGMA_GCC_WARNING_DISABLE(weak-vtables)

struct DirectoryVisitor : public directory_visitor {
	vector<path> files;
	vector<path> directories;

	void on_directory(const directory_entry &entry) override
	{
		directories.push_back(entry);
	}

	void on_file(const directory_entry &entry) override
	{
		files.push_back(entry);
	}
};

TEST(DirectoryGuideTest, testWalk)
{
	DirectoryVisitor visitor;
	directory_guide guide;
	guide.walk(current_path(), &visitor);
	ASSERT_GT(visitor.files.size(), 0);
	ASSERT_GT(visitor.directories.size(), 0);
}

}
