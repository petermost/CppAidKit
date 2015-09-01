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

#include <pera_software/aidkit/aidkit.hpp>
#include <vector>
#include <assert.h>
#include <iterator>
#include <algorithm>

namespace pera_software { namespace aidkit { namespace container {

template < typename T, std::size_t SIZE >
	class static_array {
		public:
			typedef T value_type;

			typedef value_type *pointer;
			typedef const value_type *const_pointer;

			typedef value_type &reference;
			typedef const value_type &const_reference;

			typedef value_type *iterator;
			typedef const value_type *const_iterator;

			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;

			typedef std::reverse_iterator< iterator > reverse_iterator;
			typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

			// We must not define a constructor because this container should be usable even if it
			// was only 0-initialized and a constructor would 'override' the already made changes.

			// vvvvvvvvvv std::array methods vvvvvvvvvv

			iterator begin() noexcept {
				return data();
			}

			const_iterator begin() const noexcept {
				return data();
			}

			iterator end() noexcept {
				return data() + size_;
			}

			const_iterator end() const noexcept {
				return data() + size_;
			}

			reverse_iterator rbegin() noexcept {
				return reverse_iterator( end() );
			}

			const_reverse_iterator rbegin() const noexcept {
				return const_reverse_iterator( end() );
			}

			reverse_iterator rend() noexcept {
				return reverse_iterator( begin() );
			}

			const_reverse_iterator rend() const noexcept {
				return const_reverse_iterator( begin() );
			}

			const_iterator cbegin() const noexcept {
				return data();
			}

			const_iterator cend() const noexcept {
				return data() + size_;
			}

			const_reverse_iterator crbegin() const noexcept {
				return const_reverse_iterator( end() );
			}

			const_reverse_iterator crend() const noexcept {
				return const_reverse_iterator( begin() );
			}

			reference front() noexcept {
				return *begin();
			}

			constexpr const_reference front() const noexcept {
				return *cbegin();
			}

			reference back() noexcept {
				return size_ ? *( end() - 1 ) : *end();
			}

			constexpr const_reference back() const noexcept {
				return size_ ? *( end() - 1 ) : *end();
			}

			// Capacity.

			constexpr size_type size() const noexcept {
				return size_;
			}

			constexpr size_type max_size() const noexcept  {
				return SIZE;
			}

			constexpr bool empty() const noexcept {
				return size() == 0;
			}

			// Element access.

			reference operator[]( size_type i ) noexcept {
				return *( data() + i );
			}

			constexpr const_reference operator[]( size_type i ) const noexcept {
				return *( data() + i );
			}

			reference at( size_type i )	{
				if ( i >= size_ )
					throw std::out_of_range( "static_array::at()" );

				return ( *this )[ i ];
			}

			constexpr const_reference at( size_type i ) const {
				if ( i >= size_ )
					throw std::out_of_range( "static_array::at()" );

				return ( *this )[ i ];
			}

			pointer data() noexcept {
				return elements_;
			}

			const_pointer data() const noexcept	{
				return elements_;
			}

			// ^^^^^^^^^^ std::array methods ^^^^^^^^^^

//			static_array &operator = ( const static_array &other ) {
//				assign( other.begin(), other.end() );

//				return *this;
//			}

//			static_array &operator = ( std::initializer_list< T > elements ) {
//				assign( elements.begin(), elements.end() );

//				return *this;
//			}

//			template < typename Iterator >
//				void assign( Iterator beginIterator, Iterator endIterator ) {
//					assert( static_cast< size_type >( std::distance( beginIterator, endIterator )) <= SIZE );

//					std::copy( beginIterator, endIterator, begin() );
//					size_ = std::distance( beginIterator, endIterator );
//				}

//			void push_back( const T &t ) {
//				assert( size_ < SIZE );

//				// Adjust the size *after* copying to stay exception safe:

//				elements_[ size_ ] = t;
//				++size_;
//			}

//			iterator erase( iterator pos ) {
//				assert( pos >= begin() && pos < end() );

//				iterator endIterator = std::move( pos + 1, end(), pos );
//				--size_;
//				return endIterator;
//			}

		private:
			std::size_t size_;
			T elements_[ SIZE ];
	};

} } }
