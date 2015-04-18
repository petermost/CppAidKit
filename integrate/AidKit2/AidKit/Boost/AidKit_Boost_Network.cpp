#include "AidKit_Boost_Network.hpp"
#include "../AidKit_Network.hpp"
#include <boost/detail/endian.hpp>

// We test for little/big endian just in case that BOOST_PDP_ENDIAN is defined:

#if !defined( BOOST_LITTLE_ENDIAN ) && !defined( BOOST_BIG_ENDIAN )
	#error "Can't determine endianness!"
#endif

namespace PERA { namespace AidKit { namespace Boost {

constexpr bool is_little_endian()
{
	#if defined( BOOST_LITTLE_ENDIAN )
		return true;
	#else
		return false;
	#endif
}

constexpr bool is_big_endian()
{
	#if defined( BOOST_BIG_ENDIAN )
		return true;
	#else
		return false;
	#endif
}

// Note: We don't need to check for the endianness because the implementations of ntoh/hton already
// check for it!

uint16_t network_to_host_16( uint16_t value )
{
	return ntoh16( value );
}

uint16_t host_to_network_16( uint16_t value )
{
	return hton16( value );
}

uint32_t network_to_host_32( uint32_t value )
{
	return ntoh32( value );
}

uint32_t host_to_network_32( uint32_t value )
{
	return hton32( value );
}

uint64_t network_to_host_64( uint64_t value )
{
	return ntoh64( value );
}

uint64_t host_to_network_64( uint64_t value )
{
	return hton64( value );
}

} } }
