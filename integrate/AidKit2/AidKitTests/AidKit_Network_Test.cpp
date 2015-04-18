#include "../AidKit/AidKit_Network.hpp"
#include "../AidKit/AidKit_Test.hpp"

using namespace std;
using namespace PERA::AidKit::Linux;

static void test_ntoh16_hton16()
{
	AIDKIT_ASSERT( ntoh16( 0x0123 ) == 0x2301 );
	AIDKIT_ASSERT( hton16( 0x2301 ) == 0x0123 );
}

static void test_ntoh32_hton32()
{
	AIDKIT_ASSERT( ntoh32( 0x01234567 ) == 0x67452301 );
	AIDKIT_ASSERT( hton32( 0x67452301 ) == 0x01234567 );
}

static void test_ntoh64_hton64()
{
	AIDKIT_ASSERT( ntoh64( 0x0123456789abcdef ) == 0xefcdab8967452301 );
	AIDKIT_ASSERT( hton64( 0xefcdab8967452301 ) == 0x0123456789abcdef );
}

void runNetworkTests()
{
	test_ntoh16_hton16();
	test_ntoh32_hton32();
	test_ntoh64_hton64();
}

