#pragma once

#include <cstdint>

namespace PERA { namespace AidKit { namespace Boost {

constexpr bool is_little_endian();
constexpr bool is_big_endian();

std::uint16_t network_to_host_16( std::uint16_t value );
std::uint16_t host_to_network_16( std::uint16_t value );

std::uint32_t network_to_host_32( std::uint32_t value );
std::uint32_t host_to_network_32( std::uint32_t value );

std::uint64_t network_to_host_64( std::uint64_t value );
std::uint64_t host_to_network_64( std::uint64_t value );

} } }
