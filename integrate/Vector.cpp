#include "stdafx.h"
#include "Vector.hpp"

// Explicitly instantiate vector< uint8_t > so that the symbols can be found across DLL boundaries:

template class UTILITYCPP_API std::allocator< std::uint8_t >;
template class UTILITYCPP_API std::vector< std::uint8_t >;
