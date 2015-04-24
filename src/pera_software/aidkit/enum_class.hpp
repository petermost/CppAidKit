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

namespace pera_software {
	namespace aidkit {

		template< typename T, typename I = int, typename C = char >
			class enum_class {
				public:
					typedef typename std::vector< T >::const_iterator const_iterator;

					const I value() const
					{
						return value_;
					}

					const std::basic_string< C > name() const
					{
						return name_;
					}

					static const_iterator begin()
					{
						return values().cbegin();
					}

					static const_iterator end()
					{
						return values().cend();
					}

					// Some find functions for searching via a name or a value:

					static const_iterator find( const std::basic_string< C > &name )
					{
						return std::find_if( begin(), end(), [ & ]( const enum_class &other ) { return name == other.name(); });
					}

					static const_iterator find( I value )
					{
						return std::find_if( begin(), end(), [ = ]( const enum_class &other ) { return value == other.value(); });
					}

				protected:
					enum_class()
						: value_( nextValue()++ )
					{
						values().push_back( *static_cast< T * >( this ));;
					}

					enum_class( I value )
						: value_( value )
					{
						values().push_back( *static_cast< T * >( this ));;
						nextValue() = value_ + 1;
					}

					// TODO: Check whether we can ensure that this ctor is getting called with a string literal
					enum_class( const C *name )
						: value_( nextValue()++ ), name_( name )
					{
						values().push_back( *static_cast< T * >( this ));;
					}

					enum_class( I value, const C *name )
						: value_( value ), name_( name )
					{
						values().push_back( *static_cast< T * >( this ));;
						nextValue() = value_ + 1;
					}

				private:
					// Must be assignable for vector<>, so we don't declare these attributes as const:

					I value_;

					// TODO: Ensure that name_ is never null!
					const C *name_;

					// Initializing order of static template members is quite tricky so we avoid these problems
					// with returning a reference to a static variable from a function. For symmetry reason we
					// use this technique for all static members.

					static inline I &nextValue()
					{
						static I nextValue_s = I();

						return nextValue_s;
					}

					static inline std::vector< T > &values()
					{
						static std::vector< T > values_s;

						return values_s;
					}
			};


		// We only define the equal and less-then operator because if the other one are needed then do:
		// #include <utility>
		// using namespace rel_ops;

		template < typename T, typename I, typename C >
			bool operator == ( const enum_class< T, I, C > &left, const enum_class< T, I, C > &right )
			{
				return left.value() == right.value();
			}

		template < typename T, typename I, typename C >
			bool operator < ( const enum_class< T, I, C > &left, const enum_class< T, I, C > &right )
			{
				return left.value() < right.value();
			}

		template < typename E >
			std::vector< E > make_enum_vector()
			{
				return std::vector< E >( E::begin(), E::end() );
			}
	}
}
