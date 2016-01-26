// Copyright 2015 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#include "data_mutex.hpp"

/*
template < typename Resource, typename Mutex = boost::recursive_mutex >
	class ThreadResourceLock : private boost::noncopyable {
		public:
			typedef boost::shared_ptr< Resource > Pointer;
			typedef boost::shared_ptr< const Resource > ConstPointer;

			Pointer lock( void )
			{
				my_mutex.lock();

				void ( ThreadResourceLock< Resource >::*unlockMethod )( Resource * ) =
					&ThreadResourceLock< Resource >::unlock;
				Pointer pointer( &my_resource, boost::bind( unlockMethod, this, _1 ));

				return ( pointer );
			}

			void unlock( Resource *resource )
			{
				BOOST_ASSERT( &my_resource == resource );

				my_mutex.unlock();
			}

			ConstPointer lock( void ) const
			{
				my_mutex.lock();

				void ( ThreadResourceLock< Resource >::*unlockMethod )( const Resource * ) const =
					&ThreadResourceLock< Resource >::unlock;
				ConstPointer pointer( &my_resource, boost::bind( unlockMethod, this, _1 ));

				return ( pointer );
			}

			void unlock( const Resource *resource ) const
			{
				BOOST_ASSERT( &my_resource == resource );

				my_mutex.unlock();
			}

		private:
			mutable Mutex my_mutex;
			Resource my_resource;
	};
*/
