#include "AidKit_Qt_Network.hpp"


#if Q_BYTE_ORDER != Q_LITTLE_ENDIAN && Q_BYTE_ORDER != Q_BIG_ENDIAN
	#error "Can't determine endianness!"
#endif

namespace PERA { namespace AidKit { namespace Qt {

constexpr bool isLittleEndian()
{
	return Q_BYTE_ORDER == Q_LITTLE_ENDIAN;
}

constexpr bool isBigEndian()
{
	return Q_BYTE_ORDER == Q_BIG_ENDIAN;
}

} } }
