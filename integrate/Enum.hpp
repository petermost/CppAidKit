#pragma once

#include "DisableWarnings.hpp"
#include <vector>
#include <string>
#include <algorithm>

namespace RohdeSchwarz 
{
	template< typename T, typename Integer = int, typename Character = char >
		class Enum {
			public:
				typedef typename std::vector< T >::const_iterator const_iterator;

				const Integer value() const
				{
					return value_;
				}

				const std::basic_string< Character > name() const
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

				static const_iterator find( const std::basic_string< Character > &name )
				{
					return std::find_if( begin(), end(), [ & ]( const Enum &other ) { return name == other.name(); });
				}

				static const_iterator find( Integer value )
				{
					return std::find_if( begin(), end(), [ = ]( const Enum &other ) { return value == other.value(); });
				}

			protected:
				Enum()
					: value_( nextValue()++ )
				{
					values().push_back( *static_cast< T * >( this ));;
				}

				Enum( Integer value )
					: value_( value )
				{
					values().push_back( *static_cast< T * >( this ));;
					nextValue() = value_ + 1;
				}

				Enum( const Character *name ) 
					: value_( nextValue()++ ), name_( name )
				{
					values().push_back( *static_cast< T * >( this ));;
				}

				Enum( Integer value, const Character *name )
					: value_( value ), name_( name )
				{
					values().push_back( *static_cast< T * >( this ));;
					nextValue() = value_ + 1;
				}

			private:
				// Must be assignable for vector<>, so we don't declare these attributes as const:

				Integer value_;
				const Character *name_;

				// Initializing order of static template members is quite tricky so we avoid these problems 
				// with returning a reference to a static variable from a function. For symmetry reason we
				// use this technique for all static members.

				static inline Integer &nextValue()
				{
					static Integer nextValue_s = Integer();

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

	template < typename T, typename Integer, typename Character >
		bool operator == ( const Enum< T, Integer, Character > &left, const Enum< T, Integer, Character > &right )
		{
			return left.value() == right.value();
		}

	template < typename T, typename Integer, typename Character >
		bool operator < ( const Enum< T, Integer, Character > &left, const Enum< T, Integer, Character > &right )
		{
			return left.value() < right.value();
		}

	template < typename Enum >
		std::vector< Enum > make_enum_vector()
		{
			return std::vector< Enum >( Enum::begin(), Enum::end() );
		}
}
