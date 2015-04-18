#pragma once

#include <cstdint>
#include <endian.h>

namespace PERA { namespace AidKit { namespace Linux {

constexpr bool islittleendian();
constexpr bool isbigendian();

std::uint16_t ntoh16( std::uint16_t value );
std::uint16_t hton16( std::uint16_t value );

std::uint32_t ntoh32( std::uint32_t value );
std::uint32_t hton32( std::uint32_t value );

std::uint64_t ntoh64( std::uint64_t value );
std::uint64_t hton64( std::uint64_t value );

} } }
