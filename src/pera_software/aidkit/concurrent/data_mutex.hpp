// Copyright 2019 Peter Most, PERA Software Solutions GmbH
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

namespace pera_software::aidkit::concurrent {

	template < typename T, typename Mutex >
		class data_ptr;

	template < typename T, typename Mutex >
		class const_data_ptr;

	/// A compile time guaranteed mutex.
	/**
	 * This special mutex guarantees that the embedded data can only be accessed after the
	 * associated mutex has been successfully locked.
	 */
	template < typename T, typename Mutex = std::mutex >
		class data_mutex {
			public:
				/// Initialize the embedded resource with the given parameters.
				template < typename ... Args >
					data_mutex( Args && ... args )
						: data_( std::forward< Args >( args ) ... )
					{
					}

				data_mutex( const data_mutex & ) = delete;
				data_mutex &operator = ( const data_mutex & ) = delete;

			private:
				friend data_ptr< T, Mutex >;
				friend const_data_ptr< T, Mutex >;

				void lock() const noexcept
				{
					mutex_.lock();
				}

				void unlock() const noexcept
				{
					mutex_.unlock();
				}

				T data_;
				mutable Mutex mutex_;
		};

	template < typename T, typename Mutex = std::mutex >
		class data_ptr {
			public:
				explicit data_ptr( data_mutex< T, Mutex > *dataMutex ) noexcept
					: data_( &dataMutex->data_ ), mutex_( &dataMutex->mutex_ )
				{
					mutex_->lock();
				}

				~data_ptr()
				{
					mutex_->unlock();
				}

				T *operator -> () noexcept
				{
					return data_;
				}

				T &operator * () noexcept
				{
					return *data_;
				}

				data_ptr( const data_ptr & ) = delete;
				data_ptr &operator = ( const data_ptr & ) = delete;

			private:
				T *data_;
				mutable Mutex *mutex_;
		};

	template < typename T, typename Mutex = std::mutex >
		class const_data_ptr {
			public:
				explicit const_data_ptr( const data_mutex< T, Mutex > *dataMutex ) noexcept
					: data_( &dataMutex->data_ ), mutex_( &dataMutex->mutex_ )
				{
					mutex_->lock();
				}

				~const_data_ptr()
				{
					mutex_->unlock();
				}

				const T *operator -> () const noexcept
				{
					return data_;
				}

				const T &operator * () const noexcept
				{
					return *data_;
				}

				const_data_ptr( const const_data_ptr & ) = delete;
				const_data_ptr &operator = ( const const_data_ptr & ) = delete;

			private:
				const T *data_;
				mutable Mutex *mutex_;
		};


}
