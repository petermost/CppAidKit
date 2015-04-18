#include "AidKit_Exception.hpp"

namespace PERA { namespace AidKit {

Exception::Exception() noexcept
{
}

Exception::Exception( const std::string &what )
	: what_( what )
{
}

Exception::~Exception() noexcept
{
}

const char *Exception::what() const noexcept
{
	return what_.c_str();
}

} }
