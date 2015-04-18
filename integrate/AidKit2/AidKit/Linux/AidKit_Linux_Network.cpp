#include "AidKit_Linux_Network.hpp"
#include <byteswap.h>

#if __BYTE_ORDER != __LITTLE_ENDIAN && __BYTE_ORDER != __BIG_ENDIAN
	#error "Can't determine endianness!"
#endif

using namespace std;

namespace PERA { namespace AidKit { namespace Linux {

constexpr bool islittleendian()
{
	return __BYTE_ORDER == __LITTLE_ENDIAN;
}

constexpr bool isbigendian()
{
	return __BYTE_ORDER == __BIG_ENDIAN;
}

uint16_t ntoh16( uint16_t value )
{
	return islittleendian() ? bswap_16( value ) : value;
}

uint16_t hton16( uint16_t value )
{
	return islittleendian() ? bswap_16( value ) : value;
}

uint32_t ntoh32( uint32_t value )
{
	return islittleendian() ? bswap_32( value ) : value;
}

uint32_t hton32( std::uint32_t value )
{
	return islittleendian() ? bswap_32( value ) : value;
}

uint64_t ntoh64( uint64_t value )
{
	return islittleendian() ? bswap_64( value ) : value;
}

uint64_t hton64( uint64_t value )
{
	return islittleendian() ? bswap_64( value ) : value;
}

} } }
