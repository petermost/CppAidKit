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
#include <functional>
#include <pera_software/aidkit/cpp/string_ref.hpp>

namespace pera_software::aidkit {

	template< typename T, typename Int = int >
		class enum_class {
			public:
				enum_class( const enum_class &other ) = default;
				enum_class &operator = ( const enum_class &other ) = default;

				Int value() const noexcept {
					return value_;
				}

				cpp::string_ref name() const noexcept {
					return name_;
				}

				// Some find functions for searching via a name or a value:

				static std::vector< T > find( cpp::string_ref name ) {
					std::vector< T > foundEnums;

					for_each([ & ]( const T &other ) {
						if ( name == other.name() )
							foundEnums.push_back( other );
					});
					return foundEnums;
				}

				static std::vector< T > find( Int value ) {
					std::vector< T > foundEnums;

					for_each([ & ]( const T &other ) {
						if ( value == other.value() )
							foundEnums.push_back( other );
					});
					return foundEnums;
				}

				// Get all defined enum values:

				static std::vector< T > values() {
					std::vector< T > values;
					values.reserve( get_container().size() );

					for_each([ & ]( const T &t ) {
						values.push_back( t );
					});
					return values;
				}

				// Allow iterating through all enum values:

				static void for_each( const std::function< void ( const T & )> &function ) {
					std::for_each( get_container().cbegin(), get_container().cend(), [ & ]( const T *t ) {
						function( *t );
					});
				}

			protected:
				enum_class()
					: enum_class( get_next_value(), EMPTY_NAME ) {
				}

				enum_class( Int value )
					: enum_class( value, EMPTY_NAME ) {
				}

				enum_class( const std::string &name )
					: enum_class( get_next_value(), name ) {
				}

				enum_class( Int value, const std::string &name ) {
					value_ = value;
					name_ = name;

					get_container().push_back( static_cast< const T * >( this ));
				}

			private:
				static const std::string EMPTY_NAME;

				static Int get_next_value() {
					return get_container().empty() ? 0 : get_container().back()->value_ + 1;
				}

				static std::vector< const T * > &get_container() {
					// - Use a function level static container so we don't get a problem with the
					//   undefined initialization order of file level statics.
					// - If using a std::vector<> is inconvenient then boost contains a small_vector<>.
					static std::vector< const T * > s_values;

					return s_values;
				}

				Int value_;
				std::string name_;
		};

	template < typename T, typename Int >
		const std::string enum_class< T, Int >::EMPTY_NAME;

	// We only define the equal and less-then operator because if the other ones are needed then
	// do:
	// #include <utility>
	// using namespace rel_ops;

	template < typename T, typename Int >
		bool operator == ( const enum_class< T, Int > &left, const enum_class< T, Int > &right ) {
			return left.value() == right.value();
		}

	template < typename T, typename Int >
		bool operator < ( const enum_class< T, Int > &left, const enum_class< T, Int > &right ) {
			return left.value() < right.value();
		}
}
