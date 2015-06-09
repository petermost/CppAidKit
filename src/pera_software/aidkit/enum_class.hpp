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

#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

namespace pera_software { namespace aidkit {

	template< typename T, size_t SIZE, typename Integer = int, typename String = std::string >
		class enum_class {
			public:
				// Compiler generated copy constructor and assignment operator are fine:

				enum_class( const enum_class & ) = default;
				enum_class &operator = ( const enum_class & ) = default;

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
					values.reserve( s_values.size() );
					for_each([ & ]( const T &t ) {
						values.push_back( t );
					});
					return values;
				}

			protected:
				enum_class()
					: enum_class( s_nextValue++ ) {
				}

				enum_class( const String &name )
					: enum_class( s_nextValue++, name ) {
				}

				enum_class( Integer value, const String &name = String() )
					: value_( value ), name_( std::make_shared< String >( name )) {
					s_values[ s_valuesSize++ ] = static_cast< const T * >( this );
					s_nextValue = value_ + 1;
				}

			private:
				typedef typename std::array< const T *, SIZE >::const_iterator const_iterator;

				static const_iterator cbegin() noexcept {
					return s_values.cbegin();
				}

				static const_iterator cend() noexcept {
					return s_values.cbegin() + s_valuesSize;
				}

				static Integer s_nextValue;

				// We don't embed the string_type to avoid the copy cost when an enum gets
				// assigned to another enum:

				Integer value_;
				std::shared_ptr< String > name_;

				// We use an array to store the values because it is usable even if it is only
				// statically initialized with zeros:

				static size_t s_valuesSize;
				static std::array< const T *, SIZE > s_values;
		};

	template < typename T, size_t SIZE, typename Integer, typename Char >
		Integer enum_class< T, SIZE, Integer, Char >::s_nextValue;

	template < typename T, size_t SIZE, typename Integer, typename Char >
		size_t enum_class< T, SIZE, Integer, Char >::s_valuesSize;

	template < typename T, size_t SIZE, typename Integer, typename Char >
		std::array< const T *, SIZE > enum_class< T, SIZE, Integer, Char >::s_values;

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
