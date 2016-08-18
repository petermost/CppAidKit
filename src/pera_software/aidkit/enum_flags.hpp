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

#include <initializer_list>
#include <type_traits>

namespace pera_software { namespace aidkit {

	template < typename E >
		class enum_flags {
			public:
				typedef typename std::underlying_type< E >::type int_type;

				static_assert( std::is_enum< E >::value, "enum_flags: Type must be an enum!" );
				static_assert( std::is_unsigned< int_type >::value, "enum_flags: Underlying enum type must be unsigned!" );

				enum_flags() noexcept {
					value_ = 0;
				}

				enum_flags( std::initializer_list< E > enums ) noexcept {
					for ( E e : enums )
						*this |= e;
				}

				// Define operators according to ISO C++ standard 17.5.2.1.3 [bitmask.types]:

				enum_flags &operator |= ( E e ) noexcept {
					value_ |= ( 1u << static_cast< int_type >( e ));

					return *this;
				}

				enum_flags &operator &= ( E e ) noexcept {
					value_ &= ( 1u << static_cast< int_type >( e ));

					return *this;
				}

				enum_flags &operator ^= ( E e ) noexcept {
					value_ ^= ( 1u << static_cast< int_type >( e ));

					return *this;
				}

				enum_flags operator | ( E e ) const noexcept {
					return enum_flags( value_ ) |= e;
				}

				enum_flags operator & ( E e ) const noexcept {
					return enum_flags( value_ ) &= e;
				}

				enum_flags operator ^ ( E e ) const noexcept {
					return enum_flags( value_ ) ^= e;
				}

				enum_flags operator ~() const noexcept {
					return enum_flags( ~value_ );
				}

				explicit operator bool() const noexcept {
					return value_ != 0;
				}

				int_type to_int() const noexcept {
					return value_;
				}

			private:
				enum_flags( int_type value ) noexcept {
					value_ = value;
				}

				int_type value_ = 0;
		};
} }
