#include "stdafx.h"
#include "functional.h"
#include "EnginePointers.h"

int rand( int min, int max )
{
	if( max - min == 0 )
		return 0;

	return min + rand() % ( max - min );
}

namespace mf
{
	D3DLIGHT9 InitDirectionalLight( D3DLIGHT9 &light, const D3DXVECTOR3 &direction, const D3DXCOLOR& color )
	{
		ZeroMemory( &light, sizeof( light ) );

		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = color * 0.3f;
		light.Diffuse = color;
		light.Specular = color * 0.15f;
		light.Direction = direction;

		return light;
	}

	D3DLIGHT9 InitPointLight( D3DLIGHT9 &light, D3DXVECTOR3 &position, D3DXCOLOR &color )
	{
		ZeroMemory( &light, sizeof( light ) );

		light.Type = D3DLIGHT_POINT;
		light.Ambient = color * 0.4f;
		light.Diffuse = color;
		light.Specular = color * 0.6f;
		light.Position = position;
		light.Range = 1000.0f;
		light.Falloff = 1.0f;
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.0f;
		light.Attenuation2 = 0.0f;

		return light;
	}

	D3DLIGHT9 InitSpotLight( D3DLIGHT9 &light, D3DXVECTOR3  &position, D3DXVECTOR3 &direction, D3DXCOLOR &color )
	{
		ZeroMemory( &light, sizeof( light ) );

		light.Type = D3DLIGHT_SPOT;
		light.Ambient = color * 0.4f;
		light.Diffuse = color;
		light.Specular = color * 0.6f;
		light.Position = position;
		light.Direction = direction;
		light.Range = 1000.0f;
		light.Falloff = 1.0f;
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.0f;
		light.Attenuation2 = 0.0f;
		light.Theta = 0.5f;
		light.Phi = 0.7f;

		return light;
	}

	D3DMATERIAL9 InitMtrl( D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p )
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient = a;
		mtrl.Diffuse = d;
		mtrl.Specular = s;
		mtrl.Emissive = e;
		mtrl.Power = p;

		return mtrl;
	}

	void CreateBox( const float &w, const float &h, const float &d, const bool &centerWidth, const bool &centerHeight, const bool &centerDepth, LPD3DXMESH &mesh )
	{
		float offsetX = 0, offsetY = 0, offsetZ = 0;
		if( centerWidth )
			offsetX = -w / 2.f;
		if( centerHeight )
			offsetY = -h / 2.f;
		if( centerDepth )
			offsetZ = -d / 2.f;

		std::vector<DWORD> vIB;
		std::vector<VERTEX3> vVB;
		std::vector<DWORD> vAB;
		DWORD offset = 0;

		// fill in the front face index data
		vIB.push_back( 0 + offset );
		vIB.push_back( 1 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 0 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 3 + offset );

		// fill in the front face vertex data
		vVB.push_back( VERTEX3( 0.f + offsetX, 0.f + offsetY, 0.f + offsetZ, 0.f, 0.f, -1.f, 0.f, 1.f ) );
		vVB.push_back( VERTEX3( 0.f + offsetX, h + offsetY, 0.f + offsetZ, 0.f, 0.f, -1.f, 0.f, 0.f ) );
		vVB.push_back( VERTEX3( w + offsetX, h + offsetY, 0.f + offsetZ, 0.f, 0.f, -1.f, 1.f, 0.f ) );
		vVB.push_back( VERTEX3( w + offsetX, 0.f + offsetY, 0.f + offsetZ, 0.f, 0.f, -1.f, 1.f, 1.f ) );

		vAB.push_back( 0 );
		vAB.push_back( 0 );

		offset += 4;

		// fill in the back face index data
		vIB.push_back( 0 + offset );
		vIB.push_back( 1 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 0 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 3 + offset );

		// fill in the back face vertex data
		vVB.push_back( VERTEX3( 0.f + offsetX, 0.f + offsetY, d + offsetZ, 0.f, 0.f, 1.f, 1.f, 1.f ) );
		vVB.push_back( VERTEX3( w + offsetX, 0.f + offsetY, d + offsetZ, 0.f, 0.f, 1.f, 0.f, 1.f ) );
		vVB.push_back( VERTEX3( w + offsetX, h + offsetY, d + offsetZ, 0.f, 0.f, 1.f, 0.f, 0.f ) );
		vVB.push_back( VERTEX3( 0.f + offsetX, h + offsetY, d + offsetZ, 0.f, 0.f, 1.f, 1.f, 0.f ) );

		vAB.push_back( 1 );
		vAB.push_back( 1 );

		offset += 4;

		// fill in the top face index data
		vIB.push_back( 0 + offset );
		vIB.push_back( 1 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 0 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 3 + offset );

		//fill in the top face vertex data
		vVB.push_back( VERTEX3( 0.f + offsetX, h + offsetY, 0.f + offsetZ, 0.f, 1.f, 0.f, 0.f, 1.f ) );
		vVB.push_back( VERTEX3( 0.f + offsetX, h + offsetY, d + offsetZ, 0.f, 1.f, 0.f, 0.f, 0.f ) );
		vVB.push_back( VERTEX3( w + offsetX, h + offsetY, d + offsetZ, 0.f, 1.f, 0.f, 1.f, 0.f ) );
		vVB.push_back( VERTEX3( w + offsetX, h + offsetY, 0.f + offsetZ, 0.f, 1.f, 0.f, 1.f, 1.f ) );

		vAB.push_back( 2 );
		vAB.push_back( 2 );

		offset += 4;

		// fill in the bottom face index data
		vIB.push_back( 0 + offset );
		vIB.push_back( 1 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 0 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 3 + offset );

		// fill in the bottom face vertex data
		vVB.push_back( VERTEX3( 0.f + offsetX, 0.f + offsetY, 0.f + offsetZ, 0.f, -1.f, 0.f, 0.f, 1.f ) );
		vVB.push_back( VERTEX3( w + offsetX, 0.f + offsetY, 0.f + offsetZ, 0.f, -1.f, 0.f, 0.f, 0.f ) );
		vVB.push_back( VERTEX3( w + offsetX, 0.f + offsetY, d + offsetZ, 0.f, -1.f, 0.f, 1.f, 0.f ) );
		vVB.push_back( VERTEX3( 0.f + offsetX, 0.f + offsetY, d + offsetZ, 0.f, -1.f, 0.f, 1.f, 1.f ) );

		vAB.push_back( 3 );
		vAB.push_back( 3 );

		offset += 4;

		// fill in the left face index data
		vIB.push_back( 0 + offset );
		vIB.push_back( 1 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 0 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 3 + offset );

		// fill in the left face vertex data
		vVB.push_back( VERTEX3( 0.f + offsetX, 0.f + offsetY, d + offsetZ, -1.f, 0.f, 0.f, 0.f, 1.f ) );
		vVB.push_back( VERTEX3( 0.f + offsetX, h + offsetY, d + offsetZ, -1.f, 0.f, 0.f, 0.f, 0.f ) );
		vVB.push_back( VERTEX3( 0.f + offsetX, h + offsetY, 0.f + offsetZ, -1.f, 0.f, 0.f, 1.f, 0.f ) );
		vVB.push_back( VERTEX3( 0.f + offsetX, 0.f + offsetY, 0.f + offsetZ, -1.f, 0.f, 0.f, 1.f, 1.f ) );

		vAB.push_back( 4 );
		vAB.push_back( 4 );

		offset += 4;

		// fill in the right face index data
		vIB.push_back( 0 + offset );
		vIB.push_back( 1 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 0 + offset );
		vIB.push_back( 2 + offset );
		vIB.push_back( 3 + offset );

		// fill in the right face vertex data
		vVB.push_back( VERTEX3( w + offsetX, 0.f + offsetY, 0.f + offsetZ, 1.f, 0.f, 0.f, 0.f, 1.f ) );
		vVB.push_back( VERTEX3( w + offsetX, h + offsetY, 0.f + offsetZ, 1.f, 0.f, 0.f, 0.f, 0.f ) );
		vVB.push_back( VERTEX3( w + offsetX, h + offsetY, d + offsetZ, 1.f, 0.f, 0.f, 1.f, 0.f ) );
		vVB.push_back( VERTEX3( w + offsetX, 0.f + offsetY, d + offsetZ, 1.f, 0.f, 0.f, 1.f, 1.f ) );

		vAB.push_back( 5 );
		vAB.push_back( 5 );

		offset += 4;

		D3DXCreateMeshFVF( offset / 2, offset, D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX3::FVF, g_pEngine->core->lpd3dd9, &mesh );

		VERTEX3 *pVB = nullptr;
		mesh->LockVertexBuffer( D3DLOCK_DISCARD, reinterpret_cast< void** >( &pVB ) );
		copy( vVB.begin(), vVB.end(), pVB );
		mesh->UnlockVertexBuffer();

		DWORD *pIB = nullptr;
		mesh->LockIndexBuffer( D3DLOCK_DISCARD, reinterpret_cast< void** >( &pIB ) );
		copy( vIB.begin(), vIB.end(), pIB );
		mesh->UnlockIndexBuffer();

		DWORD *pAB = nullptr;
		mesh->LockAttributeBuffer( D3DLOCK_DISCARD, &pAB );
		copy( vAB.begin(), vAB.end(), pAB );
		mesh->UnlockAttributeBuffer();

		std::vector<DWORD> adjacencyBuffer( mesh->GetNumFaces() * 3 );
		mesh->GenerateAdjacency( 0.f, &adjacencyBuffer[ 0 ] );
		mesh->OptimizeInplace( D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, &adjacencyBuffer[ 0 ], nullptr, nullptr, nullptr );
	}
}