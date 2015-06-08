#pragma once

#include "container_buffer.hpp"
#include <boost/serialization/vector.hpp>

// Workaround for: https://svn.boost.org/trac/boost/ticket/5904
#pragma warning( push )
#pragma warning( disable : 4702 )
#include <boost/iostreams/stream_buffer.hpp>
#pragma warning( pop ) 

// Workaround for: https://svn.boost.org/trac/boost/ticket/7873
#pragma warning( push )
#pragma warning( disable : 4244 4310 )
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#pragma warning( pop ) 

template < typename Container >
	class container_output_archive {
		public:
			container_output_archive( Container *container )
				: outputBuffer_( container ), outputStream_( &outputBuffer_ ), outputArchive_( outputStream_ )
			{
			}

			template< class T >  
				container_output_archive &operator << ( T &&t )
				{
					outputArchive_ << std::forward< T >( t );
					outputStream_.flush();
					return *this;
				}

		private:
			boost::iostreams::stream_buffer< container_output_buffer< Container >> outputBuffer_;
			std::ostream outputStream_;
			boost::archive::binary_oarchive outputArchive_;
	};


template< typename Container >
	class container_input_archive {
		public:
			container_input_archive( const Container *container )
				: inputBuffer_( container ), inputStream_( &inputBuffer_ ), inputArchive_( inputStream_ )
			{
			}

			template< class T >
				container_input_archive &operator >>( T &&t )
				{
					inputArchive_ >> std::forward< T >( t );
					return *this;
				}

		private:
			boost::iostreams::stream_buffer< container_input_buffer< Container >> inputBuffer_;
			std::istream inputStream_;
			boost::archive::binary_iarchive inputArchive_;
	};
