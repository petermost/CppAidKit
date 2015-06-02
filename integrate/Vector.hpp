#pragma once

#include <UtilityCpp/UtilityCpp.h>
#include <cstdint>
#include <iterator>
#include <vector>

// Explicitly instantiate vector< uint8_t > so that the symbols can be found across DLL boundaries:

template class UTILITYCPP_API std::allocator< std::uint8_t >;
template class UTILITYCPP_API std::vector< std::uint8_t >;

namespace std 
{
	template < typename T >
		wostream &operator << ( wostream &outputStream, const vector< T > &container ) 
		{
			for ( auto it = container.begin(); it != container.end(); ++it )
			{
				if ( it != container.begin() )
					outputStream << L", ";

				outputStream << *it;
			}
			return outputStream;
		}
}

{
	template < typename Iterator >
		std::vector< typename Iterator::value_type > make_vector( Iterator first, Iterator last )
		{
			return vector< typename Iterator::value_type >( first, last );
		}

	template < typename T, typename C >
		void vector_remove_if( std::vector< T > *container, C condition )
		{
			auto newEnd = std::remove_if( container->begin(), container->end(), condition );
			container->erase( newEnd, container->end() );
		}

}
