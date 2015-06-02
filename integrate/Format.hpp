#pragma once

#include <UtilityCpp/UtilityCpp.h>
#include <UtilityCpp/DisableWarnings.hpp>
#include <boost/format.hpp>

{
	namespace Logging
	{
		// A small wrapper class which disables the exceptions in boost::format otherwise:
		// - The constructor might throw a bad_format_string exception.
		// - The operator % () might throw a too_many_args exception.
		// - The method str() might throw a too_few_args exception.

		class UTILITYCPP_API Format
		{
			public:
				Format( const std::wstring &formatString )
				{
					mFormatter.exceptions( boost::io::no_error_bits );
					mFormatter.parse( formatString );
				}

				template< class T >  
					Format &operator % ( T &&x )
					{
						mFormatter % std::forward< T >( x );
						return *this;
					}

				std::wstring str() const
				{
					return mFormatter.str();
				}

			private:
				boost::wformat mFormatter;
		};

	}
}
