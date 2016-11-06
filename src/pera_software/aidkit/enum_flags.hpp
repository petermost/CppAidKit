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

				constexpr enum_flags() = default;
				constexpr enum_flags( const enum_flags & ) = default;

				constexpr enum_flags( E e ) noexcept
					: value_( to_bit( e )) {
				}

				// Define operators according to ISO C++ standard 17.5.2.1.3 [bitmask.types]:

				constexpr enum_flags &operator |= ( enum_flags other ) noexcept {
					value_ |= other.value_;

					return *this;
				}

				constexpr enum_flags &operator &= ( enum_flags other ) noexcept {
					value_ &= other.value_;

					return *this;
				}

				constexpr enum_flags &operator ^= ( enum_flags other ) noexcept {
					value_ ^= other.value_;

					return *this;
				}

				constexpr enum_flags operator | ( enum_flags other ) const noexcept {
					return enum_flags( value_ ) |= other;
				}

				constexpr enum_flags operator & ( enum_flags other ) const noexcept {
					return enum_flags( value_ ) &= other;
				}

				constexpr enum_flags operator ^ ( enum_flags other ) const noexcept {
					return enum_flags( value_ ) ^= other;
				}

				constexpr enum_flags operator ~() const noexcept {
					return enum_flags( ~value_ );
				}

				// Allow comparing:

				constexpr bool operator == ( enum_flags other ) const noexcept {
					return value_ == other.value_;
				}

				constexpr bool operator != ( enum_flags other ) const noexcept {
					return value_ != other.value_;
				}

				constexpr explicit operator bool () const noexcept {
					return value_ != 0;
				}

				constexpr int_type to_int() const noexcept {
					return value_;
				}

			private:
				static inline constexpr int_type to_bit( E e ) {
					return 1u << static_cast< int_type >( e );
				}

				constexpr enum_flags( int_type value ) noexcept
					: value_( value ) {
				}

				int_type value_ = 0;
		};

	// I've tried to enable literals like e = a | b with the approach from:
	// https://www.justsoftwaresolutions.co.uk/cplusplus/using-enum-classes-as-bitfields.html)
	// but then enum_flags | enum_flags failed and it was just not worth it to try to fix it.
	//
	//	template< typename E >
	//		typename std::enable_if< enum_flags< E >::enable_bitmask_operators, enum_flags< E >>::type operator | ( E lhs, E rhs ) {
	//			return enum_flags< E >( lhs ) | rhs;
	//		}

	//	template< typename E >
	//		typename std::enable_if< enum_flags< E >::enable_bitmask_operators, enum_flags< E >>::type operator & ( E lhs, E rhs ) {
	//			return enum_flags< E >( lhs ) & rhs;
	//		}

	//	template< typename E >
	//		typename std::enable_if< enum_flags< E >::enable_bitmask_operators, enum_flags< E >>::type operator ^ ( E lhs, E rhs ) {
	//			return enum_flags< E >( lhs ) ^ rhs;
	//		}

	//	template< typename E >
	//		typename std::enable_if< enum_flags< E >::enable_bitmask_operators, enum_flags< E >>::type operator ~ ( E lhs ) {
	//			return ~enum_flags< E >( lhs );
	//		}

} }
