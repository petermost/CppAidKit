#pragma once

// Copyright (C) by P. Most, PERA Software Solutions GmbH under the GNU LGPL

#include <memory>
#include <mutex>
#include "AidKit_Debug.hpp"

namespace PERA { namespace AidKit {

template < typename Resource, typename Mutex = std::recursive_mutex >
	class ResourceMutex {
		public:
			typedef std::shared_ptr< Resource > Pointer;
			typedef std::shared_ptr< const Resource > ConstPointer;

			ResourceMutex()
			{
			}
			
			ResourceMutex( const ResourceMutex & ) = delete;
			ResourceMutex &operator = ( const ResourceMutex & ) = delete;

			Pointer lock( void )
			{
				mutex.lock();

				return Pointer( &resource, [ this ]( Resource *resource )  {
					ResourceMutex::unlock( resource );
				});
			}

			void unlock( Resource *resource )
			{
				AIDKIT_ASSERT( &this->resource == resource );

				mutex.unlock();
			}

			ConstPointer lock( void ) const
			{
				mutex.lock();

				return ConstPointer( &resource, [ this ]( const Resource *resource ) {
					ResourceMutex::unlock( resource );
				});
			}

			void unlock( const Resource *resource ) const
			{
				AIDKIT_ASSERT( &this->resource == resource );

				mutex.unlock();
			}

		private:
			mutable Mutex mutex;
			Resource resource;
	};

} }

