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

#pragma once

#include <mutex>
#include <memory>
#include <functional>

namespace pera_software { namespace aidkit { namespace concurrent {

	template < typename T, typename Mutex = std::recursive_mutex >
		class data_mutex {
			public:
				using native_handle_type = typename Mutex::native_handle_type;
				using pointer = std::unique_ptr< T, std::function< void ( T * ) >>;
				using const_pointer = std::unique_ptr< const T, std::function< void ( const T * ) >>;

				template < typename ... Args >
					data_mutex( Args && ... args )
						: data_( std::forward< Args >( args ) ... ) {
						lockCount_ = 0;
					}

				pointer lock() {
					mutex_.lock();
					return make_pointer();
				}

				pointer try_lock() noexcept {
					if ( mutex_.try_lock() )
						return make_pointer();
					else
						return pointer();
				}

				const_pointer lock() const {
					mutex_.lock();
					return make_const_pointer();
				}

				const_pointer try_lock() const noexcept {
					if ( mutex_.try_lock() )
						return make_const_pointer();
					else
						return const_pointer();
				}

				native_handle_type native_handle() {
					return mutex_.native_handle();
				}

				// These methods follow the same idea then those in shared_ptr<> where unique() is
				// implemented in terms of use_count():

				bool is_locked() const noexcept {
					return lock_count() > 0;
				}

				int lock_count() const noexcept {
					return lockCount_;
				}

			private:
				void unlock( const T *data_ptr ) const {

					// Protect against pointer.reset( some_pointer ):

					if ( data_ptr == &data_ ) {
						--lockCount_;
						mutex_.unlock();
					}
				}

				// If a pointer is requested, then we know that locking has succeeded and we can
				// increment the lock counter:

				pointer make_pointer() noexcept {
					++lockCount_;
					auto unlocker = [ = ]( T *data_ptr ) {
						unlock( data_ptr );
					};
					return pointer( &data_, unlocker );
				}

				const_pointer make_const_pointer() const noexcept {
					++lockCount_;
					auto unlocker = [ = ]( const T *data_ptr ) {
						unlock( data_ptr );
					};
					return const_pointer( &data_, unlocker );
				}

				T data_;
				mutable Mutex mutex_;
				mutable int lockCount_;
		};
} } }
