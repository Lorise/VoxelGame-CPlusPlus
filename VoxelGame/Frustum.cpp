#include "stdafx.h"
#include "Frustum.h"

float FRUSTUM::frustum[ 6 ][ 4 ];

void FRUSTUM::Update( const D3DXMATRIX &viewProjection )
{
	float t;

	// Extract the RIGHT clipping plane
	frustum[ 0 ][ 0 ] = viewProjection[ 3 ] - viewProjection[ 0 ];
	frustum[ 0 ][ 1 ] = viewProjection[ 7 ] - viewProjection[ 4 ];
	frustum[ 0 ][ 2 ] = viewProjection[ 11 ] - viewProjection[ 8 ];
	frustum[ 0 ][ 3 ] = viewProjection[ 15 ] - viewProjection[ 12 ];

	// Normalize it
	t = static_cast< float >( sqrt( frustum[ 0 ][ 0 ] * frustum[ 0 ][ 0 ] + frustum[ 0 ][ 1 ] * frustum[ 0 ][ 1 ] + frustum[ 0 ][ 2 ] * frustum[ 0 ][ 2 ] ) );
	frustum[ 0 ][ 0 ] /= t;
	frustum[ 0 ][ 1 ] /= t;
	frustum[ 0 ][ 2 ] /= t;
	frustum[ 0 ][ 3 ] /= t;

	// Extract the LEFT clipping plane
	frustum[ 1 ][ 0 ] = viewProjection[ 3 ] + viewProjection[ 0 ];
	frustum[ 1 ][ 1 ] = viewProjection[ 7 ] + viewProjection[ 4 ];
	frustum[ 1 ][ 2 ] = viewProjection[ 11 ] + viewProjection[ 8 ];
	frustum[ 1 ][ 3 ] = viewProjection[ 15 ] + viewProjection[ 12 ];

	// Normalize it
	t = static_cast< float >( sqrt( frustum[ 1 ][ 0 ] * frustum[ 1 ][ 0 ] + frustum[ 1 ][ 1 ] * frustum[ 1 ][ 1 ] + frustum[ 1 ][ 2 ] * frustum[ 1 ][ 2 ] ) );
	frustum[ 1 ][ 0 ] /= t;
	frustum[ 1 ][ 1 ] /= t;
	frustum[ 1 ][ 2 ] /= t;
	frustum[ 1 ][ 3 ] /= t;

	// Extract the BOTTOM clipping plane
	frustum[ 2 ][ 0 ] = viewProjection[ 3 ] + viewProjection[ 1 ];
	frustum[ 2 ][ 1 ] = viewProjection[ 7 ] + viewProjection[ 5 ];
	frustum[ 2 ][ 2 ] = viewProjection[ 11 ] + viewProjection[ 9 ];
	frustum[ 2 ][ 3 ] = viewProjection[ 15 ] + viewProjection[ 13 ];

	// Normalize it
	t = static_cast< float >( sqrt( frustum[ 2 ][ 0 ] * frustum[ 2 ][ 0 ] + frustum[ 2 ][ 1 ] * frustum[ 2 ][ 1 ] + frustum[ 2 ][ 2 ] * frustum[ 2 ][ 2 ] ) );
	frustum[ 2 ][ 0 ] /= t;
	frustum[ 2 ][ 1 ] /= t;
	frustum[ 2 ][ 2 ] /= t;
	frustum[ 2 ][ 3 ] /= t;

	// Extract the TOP clipping plane
	frustum[ 3 ][ 0 ] = viewProjection[ 3 ] - viewProjection[ 1 ];
	frustum[ 3 ][ 1 ] = viewProjection[ 7 ] - viewProjection[ 5 ];
	frustum[ 3 ][ 2 ] = viewProjection[ 11 ] - viewProjection[ 9 ];
	frustum[ 3 ][ 3 ] = viewProjection[ 15 ] - viewProjection[ 13 ];

	// Normalize it
	t = static_cast< float >( sqrt( frustum[ 3 ][ 0 ] * frustum[ 3 ][ 0 ] + frustum[ 3 ][ 1 ] * frustum[ 3 ][ 1 ] + frustum[ 3 ][ 2 ] * frustum[ 3 ][ 2 ] ) );
	frustum[ 3 ][ 0 ] /= t;
	frustum[ 3 ][ 1 ] /= t;
	frustum[ 3 ][ 2 ] /= t;
	frustum[ 3 ][ 3 ] /= t;

	// Extract the FAR clipping plane
	frustum[ 4 ][ 0 ] = viewProjection[ 3 ] - viewProjection[ 2 ];
	frustum[ 4 ][ 1 ] = viewProjection[ 7 ] - viewProjection[ 6 ];
	frustum[ 4 ][ 2 ] = viewProjection[ 11 ] - viewProjection[ 10 ];
	frustum[ 4 ][ 3 ] = viewProjection[ 15 ] - viewProjection[ 14 ];

	// Normalize it
	t = static_cast< float >( sqrt( frustum[ 4 ][ 0 ] * frustum[ 4 ][ 0 ] + frustum[ 4 ][ 1 ] * frustum[ 4 ][ 1 ] + frustum[ 4 ][ 2 ] * frustum[ 4 ][ 2 ] ) );
	frustum[ 4 ][ 0 ] /= t;
	frustum[ 4 ][ 1 ] /= t;
	frustum[ 4 ][ 2 ] /= t;
	frustum[ 4 ][ 3 ] /= t;

	// Extract the NEAR clipping plane.  This is last on purpose (see pointinfrustum() for reason)
	frustum[ 5 ][ 0 ] = viewProjection[ 3 ] + viewProjection[ 2 ];
	frustum[ 5 ][ 1 ] = viewProjection[ 7 ] + viewProjection[ 6 ];
	frustum[ 5 ][ 2 ] = viewProjection[ 11 ] + viewProjection[ 10 ];
	frustum[ 5 ][ 3 ] = viewProjection[ 15 ] + viewProjection[ 14 ];

	// Normalize it
	t = static_cast< float >( sqrt( frustum[ 5 ][ 0 ] * frustum[ 5 ][ 0 ] + frustum[ 5 ][ 1 ] * frustum[ 5 ][ 1 ] + frustum[ 5 ][ 2 ] * frustum[ 5 ][ 2 ] ) );
	frustum[ 5 ][ 0 ] /= t;
	frustum[ 5 ][ 1 ] /= t;
	frustum[ 5 ][ 2 ] /= t;
	frustum[ 5 ][ 3 ] /= t;
}

FRUSTUM::TYPE_INTERSECTION FRUSTUM::PointInFrustum( const float &x, const float &y, const float &z )
{
	int p;

	for( p = 0; p < 6; p++ )
		if( frustum[ p ][ 0 ] * x + frustum[ p ][ 1 ] * y + frustum[ p ][ 2 ] * z + frustum[ p ][ 3 ] <= 0 )
			return FRUSTUM::OUTFRUSTUM;

	return FRUSTUM::INFRUSTUM;
}

FRUSTUM::TYPE_INTERSECTION FRUSTUM::SphereInFrustum( const float &x, const float &y, const float &z, const float &radius )
{
	int p;
	int c = 0;
	float d;

	for( p = 0; p < 6; p++ )
	{
		d = frustum[ p ][ 0 ] * x + frustum[ p ][ 1 ] * y + frustum[ p ][ 2 ] * z + frustum[ p ][ 3 ];
		if( d <= -radius )
			return OUTFRUSTUM;
		if( d > radius )
			c++;
	}
	return ( c == 6 ) ? INFRUSTUM : INTERSECTIONFRUSTUM;
}

FRUSTUM::TYPE_INTERSECTION FRUSTUM::CubeInFrustum( const float &x, const float &y, const float &z, const float &size )
{
	int c;
	int c2 = 0;

	for( int p = 0; p < 6; p++ )
	{
		c = 0;
		if( frustum[ p ][ 0 ] * ( x - size ) + frustum[ p ][ 1 ] * ( y - size ) + frustum[ p ][ 2 ] * ( z - size ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x + size ) + frustum[ p ][ 1 ] * ( y - size ) + frustum[ p ][ 2 ] * ( z - size ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x - size ) + frustum[ p ][ 1 ] * ( y + size ) + frustum[ p ][ 2 ] * ( z - size ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x + size ) + frustum[ p ][ 1 ] * ( y + size ) + frustum[ p ][ 2 ] * ( z - size ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x - size ) + frustum[ p ][ 1 ] * ( y - size ) + frustum[ p ][ 2 ] * ( z + size ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x + size ) + frustum[ p ][ 1 ] * ( y - size ) + frustum[ p ][ 2 ] * ( z + size ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x - size ) + frustum[ p ][ 1 ] * ( y + size ) + frustum[ p ][ 2 ] * ( z + size ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x + size ) + frustum[ p ][ 1 ] * ( y + size ) + frustum[ p ][ 2 ] * ( z + size ) + frustum[ p ][ 3 ] > 0 )
			c++;

		if( c == 0 )
			return OUTFRUSTUM;

		if( c == 8 )
			c2++;
	}

	return ( c2 == 6 ) ? INFRUSTUM : INTERSECTIONFRUSTUM;
}

FRUSTUM::TYPE_INTERSECTION FRUSTUM::ParallelepipedInFrustum( const float &x, const float &y, const float &z, const float &width, const float &height, const float &depth )
{
	int c;
	int c2 = 0;

	for( int p = 0; p < 6; p++ )
	{
		c = 0;
		if( frustum[ p ][ 0 ] * ( x - width ) + frustum[ p ][ 1 ] * ( y - height ) + frustum[ p ][ 2 ] * ( z - depth ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x + width ) + frustum[ p ][ 1 ] * ( y - height ) + frustum[ p ][ 2 ] * ( z - depth ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x - width ) + frustum[ p ][ 1 ] * ( y + height ) + frustum[ p ][ 2 ] * ( z - depth ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x + width ) + frustum[ p ][ 1 ] * ( y + height ) + frustum[ p ][ 2 ] * ( z - depth ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x - width ) + frustum[ p ][ 1 ] * ( y - height ) + frustum[ p ][ 2 ] * ( z + depth ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x + width ) + frustum[ p ][ 1 ] * ( y - height ) + frustum[ p ][ 2 ] * ( z + depth ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x - width ) + frustum[ p ][ 1 ] * ( y + height ) + frustum[ p ][ 2 ] * ( z + depth ) + frustum[ p ][ 3 ] > 0 )
			c++;
		if( frustum[ p ][ 0 ] * ( x + width ) + frustum[ p ][ 1 ] * ( y + height ) + frustum[ p ][ 2 ] * ( z + depth ) + frustum[ p ][ 3 ] > 0 )
			c++;

		if( c == 0 )
			return OUTFRUSTUM;

		if( c == 8 )
			c2++;
	}

	return ( c2 == 6 ) ? INFRUSTUM : INTERSECTIONFRUSTUM;
}