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

#pragma once

#include <vector>
#include <string>
#include <boost/filesystem.hpp>

namespace pera_software::aidkit::boost {

class directory_visitor {
    public:
        virtual ~directory_visitor();

        virtual void on_directory( const ::boost::filesystem::directory_entry &entry ) = 0;
        virtual void on_file( const ::boost::filesystem::directory_entry &entry ) = 0;
};

class directory_guide {
    public:
        void walk( const ::boost::filesystem::path &directoryPath, directory_visitor *visitor );
};

std::vector< std::string > queryDirectoryEntries( const ::boost::filesystem::path &directoryPath );

}
