#pragma once

#define COORD_TO_CHUNK_X( coord ) ( int( coord ) >> 4 )
#define COORD_TO_CHUNK_Y( coord ) ( int( coord ) >> 7 )
#define COORD_TO_CHUNK_Z( coord ) ( int( coord ) >> 4 )
#define COORD_TO_COORD_CHUNK_X( coord ) ( int( coord ) & ( CONSTANT::nChunckSizeX - 1 ) )
#define COORD_TO_COORD_CHUNK_Y( coord ) ( int( coord ) & ( CONSTANT::nChunckSizeY - 1 ) )
#define COORD_TO_COORD_CHUNK_Z( coord ) ( int( coord ) & ( CONSTANT::nChunckSizeZ - 1 ) )

struct VERTEX2
{
	VERTEX2() {}
	VERTEX2( const float &x, const float &y, const float &tu, const float &tv )
	{
		this->position = D3DXVECTOR3( x, y, 0 );
		this->tex = D3DXVECTOR2( tu, tv );
	}

	D3DXVECTOR3 position;
	D3DXVECTOR2 tex;

	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
};

struct VERTEX3
{
	VERTEX3() {}
	VERTEX3( const float &x, const float &y, const float &z, const float &nx, const float &ny, const float &nz, const float &tx, const float &ty )
	{
		this->position = D3DXVECTOR3( x, y, z );
		this->normal = D3DXVECTOR3( nx, ny, nz );
		this->tex = D3DXVECTOR2( tx, ty );
	}

	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
};

template< class T >
void SafeRelease( T &t )
{
	if( t )
	{
		t->Release();
		t = nullptr;
	}
}

template< class T >
void SafeDeletePtr( T *ptr )
{
	if( ptr )
	{
		delete ptr;
		ptr = nullptr;
	}
}

template< class T >
void SafeDeleteArray( T *arr )
{
	if( arr )
	{
		delete[] arr;
		arr = nullptr;
	}
}

int rand( int min, int max );

namespace mf
{
	template< class T >
	struct RECT
	{
		RECT() {}
		RECT( const T &x, const T &y, const T &width, const T &height )
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
		T x, y;
		T width, height;
	};

	const D3DXCOLOR WHITE( D3DCOLOR_XRGB( 255, 255, 255 ) );
	const D3DXCOLOR BLACK( D3DCOLOR_XRGB( 0, 0, 0 ) );
	const D3DXCOLOR GRAY( D3DCOLOR_XRGB( 128, 128, 128 ) );
	const D3DXCOLOR LIGHT_GRAY( D3DCOLOR_XRGB( 192, 192, 192 ) );
	const D3DXCOLOR RED( D3DCOLOR_XRGB( 255, 0, 0 ) );
	const D3DXCOLOR GREEN( D3DCOLOR_XRGB( 0, 255, 0 ) );
	const D3DXCOLOR BLUE( D3DCOLOR_XRGB( 0, 0, 255 ) );
	const D3DXCOLOR YELLOW( D3DCOLOR_XRGB( 255, 255, 0 ) );
	const D3DXCOLOR CYAN( D3DCOLOR_XRGB( 0, 255, 255 ) );
	const D3DXCOLOR MAGENTA( D3DCOLOR_XRGB( 255, 0, 255 ) );

	D3DLIGHT9 InitDirectionalLight( D3DLIGHT9 &light, const D3DXVECTOR3 &direction, const D3DXCOLOR &color );
	D3DLIGHT9 InitPointLight( D3DLIGHT9 &light, D3DXVECTOR3 &position, D3DXCOLOR  &color );
	D3DLIGHT9 InitSpotLight( D3DLIGHT9 &light, D3DXVECTOR3  &position, D3DXVECTOR3 &direction, D3DXCOLOR &color );

	D3DMATERIAL9 InitMtrl( D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p );

	const D3DMATERIAL9 WHITE_MTRL = InitMtrl( WHITE, WHITE, WHITE, BLACK, 2.0f );
	const D3DMATERIAL9 GRAY_MTRL = InitMtrl( GRAY, GRAY, GRAY, BLACK, 2.0f );
	const D3DMATERIAL9 LIGHT_GRAY_MTRL = InitMtrl( LIGHT_GRAY, LIGHT_GRAY, LIGHT_GRAY, BLACK, 2.0f );
	const D3DMATERIAL9 RED_MTRL = InitMtrl( RED, RED, RED, BLACK, 2.0f );
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl( GREEN, GREEN, GREEN, BLACK, 2.0f );
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl( BLUE, BLUE, BLUE, BLACK, 2.0f );
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl( YELLOW, YELLOW, YELLOW, BLACK, 2.0f );

	void CreateBox( const float &w, const float &h, const float &d, const bool &centerWidth, const bool &centerHeight, const bool &centerDepth, LPD3DXMESH &mesh );
	void CreateSphere( int LatLines, int LongLines );
}