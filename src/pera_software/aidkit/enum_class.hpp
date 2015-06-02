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
#include <string>
#include <algorithm>
#include <memory>

namespace pera_software {
	namespace aidkit {

		template< typename T, size_t SIZE, typename Integer = int, typename Char = char >
			class enum_class {
				public:
					typedef std::basic_string< Char > string_type;
					typedef typename std::array< const T *, SIZE >::const_iterator const_iterator;

					const Integer value() const {
						return value_;
					}

					const string_type &name() const {
						return *name_;
					}

					static const_iterator cbegin() {
						return s_values.cbegin();
					}

					static const_iterator cend() {
						return s_values.cend();
					}

					// Some find functions for searching via a name or a value:

					static const_iterator find( const string_type &name ) {
						return std::find_if( cbegin(), cend(), [ & ]( const enum_class *other ) {
							return name == other->name();
						});
					}

					static const_iterator find( Integer value ) {
						return std::find_if( cbegin(), cend(), [ & ]( const enum_class *other ) {
							return value == other->value();
						});
					}

				protected:
					enum_class()
						: enum_class( s_nextValue++ ) {
					}

					enum_class( const string_type &name )
						: enum_class( s_nextValue++, name ) {
					}

					enum_class( Integer value, const string_type &name = string_type() )
						: value_( value ), name_( std::make_shared< string_type >( name )) {
						s_values[ s_nextIndex++ ] = static_cast< const T * >( this );
						s_nextValue = value_ + 1;
					}

				private:
					Integer value_;
					std::shared_ptr< string_type > name_;

					static Integer s_nextValue;

					static size_t s_nextIndex;
					static std::array< const T *, SIZE > s_values;
			};

		template < typename T, size_t SIZE, typename Integer, typename Char >
			Integer enum_class< T, SIZE, Integer, Char >::s_nextValue = Integer();

		template < typename T, size_t SIZE, typename Integer, typename Char >
			size_t enum_class< T, SIZE, Integer, Char >::s_nextIndex = 0;

		template < typename T, size_t SIZE, typename Integer, typename Char >
			std::array< const T *, SIZE > enum_class< T, SIZE, Integer, Char >::s_values;

		// We only define the equal and less-then operator because if the other one are needed then do:
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
	}
}
