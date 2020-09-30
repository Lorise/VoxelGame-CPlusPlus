#pragma once
#include "Headers.h"

namespace lib
{
	class Random
	{
	private:
		int SeedArray[ 56 ];
		const int MBIG = 2147483647;
		const int MSEED = 161803398;
		const int MZ = 0;
		int inext;
		int inextp;

	public:
		Random();
		Random( int Seed );

		int Next();
		int Next( int minValue, int maxValue );
		int Next( int maxValue );
		double NextDouble();
		void NextBytes( byte* buffer, int length );

	protected:
		double Sample();

	private:
		int InternalSample();
		double GetSampleForLargeRange();
	};
}
