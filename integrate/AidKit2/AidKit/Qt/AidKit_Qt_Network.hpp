#pragma once

#include <QtGlobal>
#include <QtEndian>

namespace PERA { namespace AidKit { namespace Qt {

constexpr bool isLittleEndian();
constexpr bool isBigEndian();

// Qt provides a full set of functions for converting 16,32 and 64 bits to/from network to host, so
// we don't need to provide some missing functionality.

} } }

