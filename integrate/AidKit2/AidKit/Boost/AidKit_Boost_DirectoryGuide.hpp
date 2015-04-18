#pragma once

#include <list>
#include <string>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>

namespace PERA { namespace AidKit { namespace Boost {

class DirectoryVisitor {
	public:
		virtual void onVisitDirectory( const boost::filesystem::directory_entry &entry ) = 0;
		virtual void onVisitFile( const boost::filesystem::directory_entry &entry ) = 0;
};

class DirectoryGuide {
	public:
		void walk( const boost::filesystem::path &directoryPath, DirectoryVisitor *visitor );
};

std::list< std::string > queryDirectoryEntries( const std::string &directoryPath );

} } }
