#include <AidKit/AidKit.hpp>
#include <stdexcept>

using namespace std;

template < const int LOWER_LIMIT, const int UPPER_LIMIT >
	class IntegerRange {
		public:
			static int CheckRange( int Value )
			{
				if ( Value < LOWER_LIMIT )
					throw ( out_of_range( "IntegerRange: Value < " AIDKIT_STRINGIZING_SYMBOL( LOWER_LIMIT )));
				else if ( Value > UPPER_LIMIT )
					throw ( out_of_range( "IntegerRange: Value > " AIDKIT_STRINGIZING_SYMBOL( UPPER_LIMIT )));
				else
					return ( Value );
			}

				
			explicit IntegerRange( int Value )
				{ my_Value = CheckRange( Value ); }

			int operator = ( int Value )
				{ return ( my_Value = CheckRange( Value )); }

			operator int ( void ) const
				{ return ( my_Value ); }

		private:
			int my_Value;
};

typedef IntegerRange< 0, 100 > Age;


int main(void)
{
	try {
		Age age( 110 );
	} catch ( const out_of_range &error ) {
		printf( "Age out of range: %s\n", error.what() );
	}
	return 0;
}
