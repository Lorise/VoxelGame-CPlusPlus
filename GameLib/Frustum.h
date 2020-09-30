#pragma once
#include "Headers.h"

namespace lib
{
	class Frustum
	{
	public:
		static void Update( float screenDepth, D3DXMATRIX projectionMatrix, D3DXMATRIX viewMatrix );

		static bool CheckPoint( float x, float y, float z );
		static bool check_cube(float x_center, float y_center, float zCenter, float radius);
		static bool CheckCube_( float x, float y, float z, float size );
		static bool CheckSphere( float xCenter, float yCenter, float zCenter, float radius );
		static bool CheckRectangle( float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize );

	private:
		static D3DXPLANE m_planes[ 6 ];
	};
}