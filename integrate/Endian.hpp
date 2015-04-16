#pragma once

#include <cstdlib>
#include <stdint.h>
#include <boost/static_assert.hpp>
#include <boost/detail/endian.hpp>

namespace RohdeSchwarz 
{ 
	namespace IO 
	{
		// Only Window-8 defines a htonll/ntohll, so we define our own:

		inline unsigned long long htonll( unsigned long long value )
		{
			#if defined( BOOST_BIG_ENDIAN )
				return value;
			#elif defined( BOOST_LITTLE_ENDIAN )
				return _byteswap_uint64( value );
			#else
				#error Unknown Endianness!
			#endif
		}

		inline unsigned long long ntohll( unsigned long long value )
		{
			#if defined( BOOST_BIG_ENDIAN )
				return value;
			#elif defined( BOOST_LITTLE_ENDIAN )
				return _byteswap_uint64( value );
			#else
				#error Unknown Endianness!
			#endif
		}

		// Select the correct hton*()/ntoh*() function based on the size of the value:

		template < size_t Size >
			struct ByteSwapper
			{
			};

		// Template specializations for the different value sizes:

		template <>
			struct ByteSwapper< sizeof( uint8_t )>
			{
				// No need to swap, but this way hton/ntoh works for every datatype.

				static uint8_t hton( uint8_t value )
				{
					return value;
				}

				static uint8_t ntoh( uint8_t value )
				{
					return value;
				}
			};

		BOOST_STATIC_ASSERT( sizeof( unsigned short ) == sizeof( uint16_t ));
		template <>
			struct ByteSwapper< sizeof( uint16_t )> 
			{
				static uint16_t hton( uint16_t value )
				{
					return htons( value );
				}

				static uint16_t ntoh( uint16_t value )
				{
					return ntohs( value );
				}
			};

		BOOST_STATIC_ASSERT( sizeof( unsigned long ) == sizeof( uint32_t ));
		template <>
			struct ByteSwapper< sizeof( uint32_t )> 
			{
				static uint32_t hton( uint32_t value )
				{
					return htonl( value );
				}

				static uint32_t ntoh( uint32_t value )
				{
					return ntohl( value );
				}
			};

		BOOST_STATIC_ASSERT( sizeof( unsigned long long ) == sizeof( uint64_t ));
		template <>
			struct ByteSwapper< sizeof( uint64_t )>
			{
				static uint64_t hton( uint64_t value )
				{
					return htonll( value );
				}

				static uint64_t ntoh( uint64_t value )
				{
					return ntohll( value );
				}
			};
		
		template < typename T >
			T hton( T value )
			{
				BOOST_STATIC_ASSERT_MSG( std::is_integral< T >::value, "hton: T is not an integer!" );

				return ByteSwapper< sizeof( T )>::hton( value );
			}

		template < typename T >
			T ntoh( T value )
			{
				BOOST_STATIC_ASSERT_MSG( std::is_integral< T >::value, "ntoh: T is not an integer!" );

				return ByteSwapper< sizeof( T )>::ntoh( value );
			}

	}
}
