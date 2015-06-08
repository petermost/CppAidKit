#include "stdafx.h"
#include <UtilityCpp/Communication/SocketMessage.hpp>
#include <UtilityCpp/Communication/VersionIndMessage.hpp>
#include <UtilityCppUnitTest/Testing/Assertions.hpp>

namespace { namespace Communication {

using namespace std;
using namespace Testing;
using namespace NUnit::Framework;

[ TestFixture ]
public ref struct VersionIndMessageTest
{
	[ Test ]
	void TestEncodeDecode()
	{
		const unsigned expectedMajorVersion = 13;
		const unsigned expectedMinorVersion = 8;

		SocketMessage socketMessage = EncodeVersionIndMessage( expectedMajorVersion, expectedMinorVersion );
		tuple< unsigned, unsigned > actualVersion = DecodeVersionIndMessage( &socketMessage );

		Assert::AreEqual( expectedMajorVersion, get< 0 >( actualVersion ));
		Assert::AreEqual( expectedMinorVersion, get< 1 >( actualVersion ));
	}
};

} }
