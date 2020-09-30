#include "Random.h"

namespace lib
{
	Random::Random() : Random( timeGetTime() )
	{
	}

	Random::Random( int Seed )
	{
		int num1 = 161803398 - ( Seed == INT_MIN ? INT_MAX : abs( Seed ) );
		this->SeedArray[ 55 ] = num1;
		int num2 = 1;

		for ( int index1 = 1; index1 < 55; ++index1 )
		{
			int index2 = 21 * index1 % 55;
			this->SeedArray[ index2 ] = num2;
			num2 = num1 - num2;
			if ( num2 < 0 )
				num2 += INT_MAX;
			num1 = this->SeedArray[ index2 ];
		}

		for ( int index1 = 1; index1 < 5; ++index1 )
		{
			for ( int index2 = 1; index2 < 56; ++index2 )
			{
				this->SeedArray[ index2 ] -= this->SeedArray[ 1 + ( index2 + 30 ) % 55 ];
				if ( this->SeedArray[ index2 ] < 0 )
					this->SeedArray[ index2 ] += INT_MAX;
			}
		}

		this->inext = 0;
		this->inextp = 21;

		Seed = 1;
	}

	int Random::Next()
	{
		return this->InternalSample();
	}

	int Random::Next( int minValue, int maxValue )
	{
		if ( minValue > maxValue )
		{
			return 0;
			//throw new ArgumentOutOfRangeException( "minValue", Environment.GetResourceString( "Argument_MinMaxValue", ( object ) "minValue", ( object ) "maxValue" ) );
		}

		long num = ( long )maxValue - ( long )minValue;

		if ( num <= ( long )INT_MAX )
			return ( int )( this->Sample() * ( double )num ) + minValue;

		return ( int )( ( long )( this->GetSampleForLargeRange() * ( double )num ) + ( long )minValue );
	}

	int Random::Next( int maxValue )
	{
		if ( maxValue < 0 )
		{
			return 0;
			//throw new ArgumentOutOfRangeException( "maxValue", Environment.GetResourceString( "ArgumentOutOfRange_MustBePositive", ( object ) "maxValue" ) );
		}

		return ( int )( this->Sample() * ( double )maxValue );
	}

	double Random::NextDouble()
	{
		return this->Sample();
	}

	void Random::NextBytes( byte* buffer, int length )
	{
		if ( buffer == nullptr )
		{
			return;
			//throw new ArgumentNullException( "buffer" );
		}

		for ( int index = 0; index < length; ++index )
			buffer[ index ] = ( byte )( this->InternalSample() % 256 );
	}

	double Random::Sample()
	{
		return ( double ) this->InternalSample() * 4.6566128752458E-10;
	}

	int Random::InternalSample()
	{
		int inext = this->inext;
		int inextp = this->inextp;
		int index1;

		if ( ( index1 = inext + 1 ) >= 56 )
			index1 = 1;

		int index2;

		if ( ( index2 = inextp + 1 ) >= 56 )
			index2 = 1;

		int num = this->SeedArray[ index1 ] - this->SeedArray[ index2 ];

		if ( num == INT_MAX )
			--num;
		if ( num < 0 )
			num += INT_MAX;

		this->SeedArray[ index1 ] = num;
		this->inext = index1;
		this->inextp = index2;

		return num;
	}

	double Random::GetSampleForLargeRange()
	{
		int num = this->InternalSample();

		if ( this->InternalSample() % 2 == 0 )
			num = -num;

		return ( ( double )num + 2147483646.0 ) / 4294967293.0;
	}
}