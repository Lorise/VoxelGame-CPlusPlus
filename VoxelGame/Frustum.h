#pragma once

class FRUSTUM
{
public:
	enum TYPE_INTERSECTION
	{
		OUTFRUSTUM,
		INTERSECTIONFRUSTUM,
		INFRUSTUM
	};

	static void Update( const D3DXMATRIX &viewProjection );

	static TYPE_INTERSECTION PointInFrustum( const float &x, const float &y, const float &z );
	static TYPE_INTERSECTION SphereInFrustum( const float &x, const float &y, const float &z, const float &radius );
	static TYPE_INTERSECTION CubeInFrustum( const float &x, const float &y, const float &z, const float &size );
	static TYPE_INTERSECTION ParallelepipedInFrustum( const float &x, const float &y, const float &z, const float &width, const float &height, const float &depth );

private:
	static float frustum[ 6 ][ 4 ];
};