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

#include <vector>
#include <string>
#include <algorithm>

namespace pera_software { namespace aidkit {

	template< typename T, size_t SIZE, typename Integer = int, typename String = std::string >
		class enum_class {
			public:
				enum_class( const enum_class &other ) noexcept {
					value_ = other.value_;
					name_ = other.name_;
					isOwner_ = false;
				}

				enum_class &operator = ( const enum_class &other ) noexcept {
					if ( this != &other ) {
						value_ = other.value_;
						name_ = other.name_;
						isOwner_ = false;
					}
					return *this;
				}

				const Integer value() const noexcept {
					return value_;
				}

				const String &name() const noexcept {
					return *name_;
				}

				// Some find functions for searching via a name or a value:

				static std::vector< T > find( const String &name ) {
					std::vector< T > foundEnums;
					for_each([ & ]( const T &other ) {
						if ( name == other.name() )
							foundEnums.push_back( other );
					});
					return foundEnums;
				}

				static std::vector< T > find( Integer value ) {
					std::vector< T > foundEnums;
					for_each([ & ]( const T &other ) {
						if ( value == other.value() )
							foundEnums.push_back( other );
					});
					return foundEnums;
				}

				// Allow iterating through all enum values:

				template < typename Functor >
					static void for_each( Functor &&functor ) {
						std::for_each( cbegin(), cend(), [ & ]( const T *t ) {
							functor( *t );
						});
					}

				// Get all defined enum values:

				static std::vector< T > values() {
					std::vector< T > values;
					values.reserve( make_values().size() );
					for_each([ & ]( const T &t ) {
						values.push_back( t );
					});
					return values;
				}

			protected:
				enum_class()
					: enum_class( make_next_value() ) {
				}

				enum_class( const String &name )
					: enum_class( make_next_value(), name ) {
				}

				enum_class( Integer value, const String &name = String() ) {
					value_ = value;
					name_ = new String( name );
					isOwner_ = true;

					make_values().push_back( static_cast< const T * >( this ));
				}

				~enum_class() {
					if ( isOwner_ )
						delete name_;
				}

			private:
				using const_iterator = typename std::vector< const T * >::const_iterator;

				static std::vector< const T * > &make_values() {
					static std::vector< const T * > s_values;

					return s_values;
				}

				static Integer make_next_value() {
					return make_values().empty() ? 0 : make_values().back()->value_ + 1;
				}

				// We don't:
				// - Embed the string_type to avoid the copy cost when an enum_class gets copied.
				// - Use a shared_ptr because copying would then always incremente/decrement the
				//   reference counter which is most likely not in the cache.

				Integer value_;
				String *name_;
				bool isOwner_;

				static const_iterator cbegin() noexcept {
					return make_values().cbegin();
				}

				static const_iterator cend() noexcept {
					return make_values().cend();
				}
		};

	// We only define the equal and less-then operator because if the other ones are needed then
	// do:
	// #include <utility>
	// using namespace rel_ops;

	template < typename T, size_t SIZE, typename Integer, typename Char >
		bool operator == ( const enum_class< T, SIZE, Integer, Char > &left, const enum_class< T, SIZE, Integer, Char > &right ) {
			return left.value() == right.value();
		}

	template < typename T, size_t SIZE, typename Integer, typename Char >
		bool operator < ( const enum_class< T, SIZE, Integer, Char > &left, const enum_class< T, SIZE, Integer, Char > &right ) {
			return left.value() < right.value();
		}
} }
