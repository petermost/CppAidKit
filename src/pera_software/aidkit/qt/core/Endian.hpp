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

#include <QtEndian>
#include <QtGlobal>

namespace pera_software::aidkit::qt {

	// Select the correct hton*()/ntoh*() function based on the size of the value:

	template < size_t Size >
		struct ByteSwapper {
		};

	// Template specializations for the different value sizes:

	template <>
		struct ByteSwapper< sizeof( quint8 )> {
			using value_type = quint8;

			// No need to swap, but this way hton/ntoh works for every datatype in generic code.

			static quint8 hton( quint8 value ) {
				return value;
			}

			static quint8 ntoh( quint8 value ) {
				return value;
			}
		};

	template <>
		struct ByteSwapper< sizeof( quint16 )> {

			using value_type = quint16;

			static quint16 hton( quint16 value ) {
				return qToBigEndian( value );
			}

			static quint16 ntoh( quint16 value ) {
				return qFromBigEndian( value );
			}
		};

	template <>
		struct ByteSwapper< sizeof( quint32 )> {

			using value_type = quint32;

			static quint32 hton( quint32 value ) {
				return qToBigEndian( value );
			}

			static quint32 ntoh( quint32 value ) {
				return qFromBigEndian( value );
			}
		};

	template <>
		struct ByteSwapper< sizeof( quint64 )> {

			using value_type = quint64;

			static quint64 hton( quint64 value ) {
				return qToBigEndian( value );
			}

			static quint64 ntoh( quint64 value ) {
				return qFromBigEndian( value );
			}
		};

	template < typename T >
		T hton( T value )
		{
			Q_STATIC_ASSERT_X( std::is_integral< T >::value, "hton: T is not an integer!" );

			using byteSwapper = ByteSwapper< sizeof( T )>;
			return static_cast< T >( byteSwapper::hton( static_cast< typename byteSwapper::value_type >( value )));
		}

	template < typename T >
		T ntoh( T value )
		{
			Q_STATIC_ASSERT_X( std::is_integral< T >::value, "ntoh: T is not an integer!" );

			using byteSwapper = ByteSwapper< sizeof( T )>;
			return static_cast< T >( byteSwapper::ntoh( static_cast< typename byteSwapper::value_type >( value )));
		}

}
