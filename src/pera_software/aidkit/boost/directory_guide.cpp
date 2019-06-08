// Copyright 2019 Peter Most, PERA Software Solutions GmbH
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

#include "directory_guide.hpp"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace boost::filesystem;

namespace pera_software::aidkit::boost {

void directory_guide::walk( const path &directoryPath, directory_visitor* visitor )
{
    for_each( directory_iterator( directoryPath ), directory_iterator(), [=]( const directory_entry &entry ) {
        if ( is_directory( entry.path() ))
            visitor->on_directory( entry );
        else if ( is_regular_file( entry.path() ))
            visitor->on_file( entry );
    });
}



vector< string > queryDirectoryEntries( const string &directoryPath )
{
    vector< string > entries;

    for_each( directory_iterator( directoryPath ), directory_iterator(), [&]( const directory_entry &entry ) {
        entries.push_back( entry.path().string() );
    });
    return entries;
}

}
