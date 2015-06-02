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
#include <memory>

namespace pera_software {
	namespace aidkit {

		template< typename T, typename Integer = int, typename Char = char >
			class enum_class {
				public:
					typedef std::basic_string< Char > string_type;
					typedef std::vector< T * > container_type;
					typedef typename container_type::const_iterator const_iterator;

					const Integer value() const {
						return value_;
					}

					const string_type &name() const {
						return *name_;
					}

					static const_iterator begin() {
						return getValuesReference().cbegin();
					}

					static const_iterator end() {
						return getValuesReference().cend();
					}

					// Some find functions for searching via a name or a value:

					static const_iterator find( const string_type &name ) {
						return std::find_if( begin(), end(), [ & ]( const enum_class *other ) {
							return name == other->name();
						});
					}

					static const_iterator find( Integer value ) {
						return std::find_if( begin(), end(), [ & ]( const enum_class *other ) {
							return value == other->value();
						});
					}

				protected:
					enum_class()
						: enum_class( getNextValueReference()++ ) {
					}

					enum_class( const string_type &name )
						: enum_class( getNextValueReference()++, name ) {
					}

					enum_class( Integer value, const string_type &name = string_type() )
						: value_( value ), name_( std::make_shared< string_type >( name )) {
						getValuesReference().push_back( static_cast< T * >( this ));
						getNextValueReference() = value_ + 1;
					}

				private:
					// Must be assignable for vector<>, so we don't declare these attributes as const:

					Integer value_;

					std::shared_ptr< string_type > name_;

					// Initializing order of static template members is quite tricky so we avoid these problems
					// with returning a reference to a static variable from a function. For symmetry reason we
					// use this technique for all static members.

					static inline Integer &getNextValueReference() {
						static Integer s_nextValue = Integer();

						return s_nextValue;
					}

					static inline std::vector< T * > &getValuesReference() {
						static std::vector< T * > s_values;

						return s_values;
					}
			};


		// We only define the equal and less-then operator because if the other one are needed then do:
		// #include <utility>
		// using namespace rel_ops;

		template < typename T, typename Integer, typename Char >
			bool operator == ( const enum_class< T, Integer, Char > &left, const enum_class< T, Integer, Char > &right ) {
				return left.value() == right.value();
			}

		template < typename T, typename Integer, typename Char >
			bool operator < ( const enum_class< T, Integer, Char > &left, const enum_class< T, Integer, Char > &right ) {
				return left.value() < right.value();
			}
	}
}
