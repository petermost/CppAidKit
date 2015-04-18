#ifndef PERA_AIDKIT_WINDOWS_NETWORK_HPP
#define PERA_AIDKIT_WINDOWS_NETWORK_HPP

#include <cstdint>

namespace PERA {
namespace AidKit {
namespace Windows {

constexpr bool IsLittleEndian();
constexpr bool IsBigEndian();

std::uint16_t ntoh16( std::uint16_t value );
std::uint16_t hton16( std::uint16_t value );

std::uint32_t ntoh32( std::uint32_t value );
std::uint32_t hton32( std::uint32_t value );

std::uint64_t ntoh64( std::uint64_t value );
std::uint64_t hton64( std::uint64_t value );

}
}
}

#endif // NETWORK_HPP
