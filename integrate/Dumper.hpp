#pragma once

#include "../UtilityCpp.h"
#include <vector>
#include <iostream>
#include <type_traits>
#include <boost/io/ios_state.hpp>

#pragma warning( push )
#pragma warning( disable: 4127 )

{ 
	namespace Debugging 
	{
		class UTILITYCPP_API DumperOutput
		{
			public:
				DumperOutput( std::wostream &stream );

				void AddName( const wchar_t name[] );

				template < typename T >
					void AddValue( const T &t )
					{
						mStream << t;
					}

				void AddSeparator();

				void BeginCollection();
				void EndCollection();

				void BeginValue();
				void EndValue();

				void BeginStruct();
				void EndStruct();

			private:
				std::wostream &mStream;
		};

		class UTILITYCPP_API Dumper
		{
			public:
				Dumper( std::wostream &stream )
					: mOutput( stream )
				{
					mObjectCounter = 0;
				}

				template < typename T >
					void Dump( const wchar_t name[], const T &t )
					{
						AddSeparator( mObjectCounter++ );
						mOutput.AddName( name );
						DumpValue( t );
					}

				template < typename T >
					void Dump( const wchar_t name[], const std::vector< T > &collection )
					{
						AddSeparator( mObjectCounter++ );
						mOutput.AddName( name );
						DumpCollection( collection );
					}

				template < typename T >
					void Dump( const T &t )
					{
						AddSeparator( mObjectCounter++ );
						DumpValue( t );
					}

				template < typename T >
					void Dump( const std::vector< T > &collection )
					{
						AddSeparator( mObjectCounter++ );
						DumpCollection( collection );
					}
		
			private:
				template < typename T >
					void DumpValue( const T &t )
					{
						if ( std::is_scalar< T >::value )
							DumpScalar( t );
						else
							DumpStruct( t );
					}

				template < typename T >
					void DumpScalar( const T &t )
					{
						mOutput.BeginValue();
						mOutput.AddValue( t );
						mOutput.EndValue();
					}

				template < typename T >
					void DumpStruct( const T &t )
					{
						int oldObjectCounter = SwapObjectCounter( 0 );
	  
						mOutput.BeginStruct();
						mOutput.AddValue( t );
						mOutput.EndStruct();
	  
						SwapObjectCounter( oldObjectCounter );
					}

				template < typename T >
					void DumpCollection( const std::vector< T > &collection )
					{
						int oldObjectCounter = SwapObjectCounter( 0 );

						mOutput.BeginCollection();
						for ( size_t i = 0; i < collection.size(); ++i )
						{
							AddSeparator( i );
							DumpValue( collection[ i ]);
						}
						mOutput.EndCollection();

						SwapObjectCounter( oldObjectCounter );
					}

				void AddSeparator( int counter )
				{
					if ( counter > 0 )
						mOutput.AddSeparator();
				}

				int SwapObjectCounter( int newValue )
				{
					int oldValue = mObjectCounter;
					mObjectCounter = newValue;
					return oldValue;
				}

				DumperOutput mOutput;
				int mObjectCounter;
		};



		class DumperFormatSetter
		{
			public:
				DumperFormatSetter( std::wostream & );

			private:
				boost::io::ios_base_all_saver mStreamStateSaver;
		};

	}
}

#pragma warning( pop )
