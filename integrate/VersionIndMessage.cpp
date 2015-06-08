#include "stdafx.h"
#include "VersionIndMessage.hpp"
#include "SocketMessage.hpp"
#include "SocketMessenger.hpp"
#include "container_archive.hpp"
#include <boost/assert.hpp>
#include <UtilityCpp/Logging/Logger.hpp>

namespace { namespace Communication {

using namespace std;
using namespace boost::system;
using namespace Logging;
using namespace Boost::System;

using boost::system::error_code;

UTILITYCPP_API const unsigned CURRENT_MAJOR_VERSION = 1;
UTILITYCPP_API const unsigned CURRENT_MINOR_VERSION = 0;

//==================================================================================================

SocketMessage EncodeVersionIndMessage( unsigned majorVersion, unsigned minorVersion )
{
	vector< uint8_t > serializedVersion;
	container_output_archive< vector< uint8_t >> outputArchive( &serializedVersion );

	outputArchive << majorVersion;
	outputArchive << minorVersion;

	return SocketMessage( SocketMessage::VersionInd, &serializedVersion );
}

//==================================================================================================

tuple< unsigned, unsigned > DecodeVersionIndMessage( const SocketMessage *message )
{
	BOOST_ASSERT( message->Type == SocketMessage::VersionInd );

	container_input_archive< vector< uint8_t >> inputArchive( &message->Data );

	unsigned majorVersion;
	unsigned minorVersion;

	inputArchive >> majorVersion;
	inputArchive >> minorVersion;

	return make_tuple( majorVersion, minorVersion );
}

//==================================================================================================

void SendCurrentVersion( Logger *logger, SocketMessenger *messenger, const function< void( const error_code & )> &sendHandler )
{
	SendVersion( logger, messenger, CURRENT_MAJOR_VERSION, CURRENT_MINOR_VERSION, sendHandler );
}

//==================================================================================================

void SendVersion( Logger *logger, SocketMessenger *messenger, unsigned majorVersion, unsigned minorVersion,
	const function< void( const error_code & )> &sendHandler )
{
	logger->Info( Format( L"Sending version message '%d.%d'." ) % majorVersion % minorVersion );

	SocketMessage versionMessage = EncodeVersionIndMessage( majorVersion, minorVersion );
	messenger->SendMessageAsync( &versionMessage, [ = ]( const error_code &errorCode )
	{
		if ( errorCode )
			logger->Error( Format( L"Sending version message failed with '%s'!" ) % ToString( errorCode ));

		sendHandler( errorCode );
	});
}

} }
