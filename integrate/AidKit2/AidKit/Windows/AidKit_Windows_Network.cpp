#include "AidKit_Windows_Network.hpp"
#include <cstdlib>

using namespace std;

namespace PERA {
namespace AidKit {
namespace Windows {

// Note that current Windows versions are always little endian systems:

constexpr bool IsLittleEndian()
{
	return true;
}

constexpr bool IsBigEndian()
{
	return false;
}

uint16_t ntoh16( uint16_t value )
{
	return IsLittleEndian() ? _byteswap_ushort( value ) : value;
}

uint16_t hton16( uint16_t value )
{
	return IsLittleEndian() ? _byteswap_ushort( value ) : value;
}

uint32_t ntoh32( uint32_t value )
{
	return IsLittleEndian() ? _byteswap_ulong( value ) : value;
}

uint32_t hton32( std::uint32_t value )
{
	return IsLittleEndian() ? _byteswap_ulong( value ) : value;
}

uint64_t ntoh64( uint64_t value )
{
	return IsLittleEndian() ? _byteswap_uint64( value ) : value;
}

uint64_t hton64( uint64_t value )
{
	return IsLittleEndian() ? _byteswap_uint64( value ) : value;
}

}
}
}
