#pragma once

#include <UtilityCpp/UtilityCpp.h>
#include <UtilityCpp/Boost/System.hpp>
#include <tuple>
#include <functional>

namespace 
{
	namespace Logging
	{
		class Logger;
	}
	namespace Communication
	{
		struct SocketMessage;
		class SocketMessenger;

		extern UTILITYCPP_API const unsigned CURRENT_MAJOR_VERSION;
		extern UTILITYCPP_API const unsigned CURRENT_MINOR_VERSION;

		UTILITYCPP_API SocketMessage EncodeVersionIndMessage( unsigned majorVersion, unsigned minorVersion );
		UTILITYCPP_API std::tuple< unsigned /* majorVersion */, unsigned /* minorVersion */ > DecodeVersionIndMessage( const SocketMessage * );

		UTILITYCPP_API void SendCurrentVersion( Logging::Logger *, SocketMessenger *, 
			const std::function< void ( const boost::system::error_code & )> &sendHandler );

		// This function is meant to be used for testing so a incompatible version can be tested:

		UTILITYCPP_API void SendVersion( Logging::Logger *, SocketMessenger *, unsigned majorVersion, unsigned minorVersion,
			const std::function< void ( const boost::system::error_code & )> &sendHandler );

	}
}
