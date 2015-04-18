#include "AidKit_Boost_DirectoryGuide.hpp"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace boost::filesystem;

namespace PERA { namespace AidKit { namespace Boost {



void DirectoryGuide::walk( const path &directoryPath, DirectoryVisitor* visitor )
{
	for_each( directory_iterator( directoryPath ), directory_iterator(), [=]( const directory_entry &entry ) {
		if ( is_directory( entry.path() ))
			visitor->onVisitDirectory( entry );
		else if ( is_regular_file( entry.path() ))
			visitor->onVisitFile( entry );
	});
}



list< string > queryDirectoryEntries( const string &directoryPath )
{
	list< string > entries;

	for_each( directory_iterator( directoryPath ), directory_iterator(), [&]( const directory_entry &entry ) {
		entries.push_back( entry.path().string() );
	});
	return entries;
}

} } }

