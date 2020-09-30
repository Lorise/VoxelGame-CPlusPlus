#include "Game.h"
#include "../VoxelGame/GameEngine.h"

namespace lib
{
	D3DMATERIAL9 Game::WHITE_MTRL;
	D3DMATERIAL9 Game::RED_MTRL;
	D3DMATERIAL9 Game::GREEN_MTRL;
	D3DMATERIAL9 Game::BLUE_MTRL;
	D3DMATERIAL9 Game::YELLOW_MTRL;

	D3DXCOLOR Game::WHITE;
	D3DXCOLOR Game::BLACK;
	D3DXCOLOR Game::RED;
	D3DXCOLOR Game::GREEN;
	D3DXCOLOR Game::BLUE;
	D3DXCOLOR Game::YELLOW;
	D3DXCOLOR Game::CYAN;
	D3DXCOLOR Game::MAGENTA;

	Game::Game()
	{
		WHITE = D3DCOLOR_XRGB( 255, 255, 255 );
		BLACK = D3DCOLOR_XRGB( 0, 0, 0 );
		RED = D3DCOLOR_XRGB( 255, 0, 0 );
		GREEN = D3DCOLOR_XRGB( 0, 255, 0 );
		BLUE = D3DCOLOR_XRGB( 0, 0, 255 );
		YELLOW = D3DCOLOR_XRGB( 255, 255, 0 );
		CYAN = D3DCOLOR_XRGB( 0, 255, 255 );
		MAGENTA = D3DCOLOR_XRGB( 255, 0, 255 );

		WHITE_MTRL = InitMtrl( WHITE, WHITE, WHITE, BLACK, 2.0f );
		RED_MTRL = InitMtrl( RED, RED, RED, BLACK, 2.0f );
		GREEN_MTRL = InitMtrl( GREEN, GREEN, GREEN, BLACK, 2.0f );
		BLUE_MTRL = InitMtrl( BLUE, BLUE, BLUE, BLACK, 2.0f );
		YELLOW_MTRL = InitMtrl( YELLOW, YELLOW, YELLOW, BLACK, 2.0f );		
	}

	Game::~Game()
	{

	}

	HRESULT Game::Init()
	{
		return S_OK;
	}

	void Game::Event()
	{

	}

	void Game::Update()
	{

	}

	void Game::FixedUpdate()
	{
	}

	void Game::PreRender()
	{
	}

	void Game::Render()
	{
		g_engine->core->d3dd9->Clear( NULL, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x1a8cff, 1.f, 0 );

		g_engine->core->d3dd9->BeginScene();

		g_engine->core->d3dd9->EndScene();

		g_engine->core->d3dd9->Present( nullptr, nullptr, nullptr, nullptr );
	}

	void Game::Cleanup()
	{

	}

	HRESULT Game::SetupPixelFog( DWORD Color, FLOAT start, FLOAT end ) const
	{
		HRESULT hr;

		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGCOLOR, Color );
		if ( FAILED( hr ) )
			return E_FAIL;

		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGTABLEMODE, D3DFOG_LINEAR );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGSTART, *reinterpret_cast< DWORD * >( &start ) );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGEND, *reinterpret_cast< DWORD * >( &end ) );
		if ( FAILED( hr ) )
			return E_FAIL;

		return D3D_OK;
	}

	HRESULT Game::SetupPixelFog( DWORD Color, _D3DFOGMODE Mode, FLOAT density ) const
	{
		HRESULT hr;

		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGCOLOR, Color );
		if ( FAILED( hr ) )
			return E_FAIL;

		if ( Mode != D3DFOG_LINEAR )
		{
			hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGTABLEMODE, Mode );
			if ( FAILED( hr ) )
				return E_FAIL;
			hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGDENSITY, *reinterpret_cast< DWORD * >( &density ) );
			if ( FAILED( hr ) )
				return E_FAIL;
		}
		else
			return E_FAIL;

		return D3D_OK;
	}

	HRESULT Game::SetupVertexFog( DWORD Color, BOOL UseRange, FLOAT start, FLOAT end ) const
	{
		HRESULT hr;

		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGCOLOR, Color );
		if ( FAILED( hr ) )
			return E_FAIL;

		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGSTART, *reinterpret_cast< DWORD * >( &start ) );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGEND, *reinterpret_cast< DWORD * >( &end ) );
		if ( FAILED( hr ) )
			return E_FAIL;

		if ( UseRange )
		{
			hr = g_engine->core->d3dd9->SetRenderState( D3DRS_RANGEFOGENABLE, TRUE );
			if ( FAILED( hr ) )
				return E_FAIL;
		}
		else
		{
			hr = g_engine->core->d3dd9->SetRenderState( D3DRS_RANGEFOGENABLE, FALSE );
			if ( FAILED( hr ) )
				return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT Game::SetupVertexFog( DWORD Color, _D3DFOGMODE Mode, BOOL UseRange, FLOAT Density ) const
	{
		HRESULT hr;

		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGCOLOR, Color );
		if ( FAILED( hr ) )
			return E_FAIL;

		if ( D3DFOG_LINEAR != Mode )
		{
			hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGVERTEXMODE, Mode );
			if ( FAILED( hr ) )
				return E_FAIL;
			hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FOGDENSITY, *reinterpret_cast< DWORD * >( &Density ) );
			if ( FAILED( hr ) )
				return E_FAIL;
		}
		else
			return E_FAIL;

		if ( UseRange )
		{
			hr = g_engine->core->d3dd9->SetRenderState( D3DRS_RANGEFOGENABLE, TRUE );
			if ( FAILED( hr ) )
				return E_FAIL;
		}
		else
		{
			hr = g_engine->core->d3dd9->SetRenderState( D3DRS_RANGEFOGENABLE, FALSE );
			if ( FAILED( hr ) )
				return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT Game::EnableWireframeMode() const
	{
		HRESULT hr;

		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		if ( FAILED( hr ) )
			return E_FAIL;

		return D3D_OK;
	}

	HRESULT Game::DisableWireframeMode() const
	{
		HRESULT hr;

		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		if ( FAILED( hr ) )
			return E_FAIL;
		hr = g_engine->core->d3dd9->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		if ( FAILED( hr ) )
			return E_FAIL;

		return D3D_OK;
	}

	D3DLIGHT9 Game::InitDirectionalLight( D3DXVECTOR3 * direction, D3DXCOLOR * color ) const
	{
		D3DLIGHT9 light;
		::ZeroMemory( &light, sizeof( light ) );

		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = *color * 0.6f;
		light.Diffuse = *color;
		light.Specular = *color * 0.6f;
		light.Direction = *direction;

		return light;
	}

	D3DLIGHT9 Game::InitPointLight( D3DXVECTOR3 * position, D3DXCOLOR * color ) const
	{
		D3DLIGHT9 light;
		::ZeroMemory( &light, sizeof( light ) );

		light.Type = D3DLIGHT_POINT;
		light.Ambient = *color * 0.6f;
		light.Diffuse = *color;
		light.Specular = *color * 0.6f;
		light.Position = *position;
		light.Range = 1000.0f;
		light.Falloff = 1.0f;
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.0f;
		light.Attenuation2 = 0.0f;

		return light;
	}

	D3DLIGHT9 Game::InitSpotLight( D3DXVECTOR3 * position, D3DXVECTOR3 * direction, D3DXCOLOR * color ) const
	{
		D3DLIGHT9 light;
		::ZeroMemory( &light, sizeof( light ) );

		light.Type = D3DLIGHT_SPOT;
		light.Ambient = *color * 0.0f;
		light.Diffuse = *color;
		light.Specular = *color * 0.6f;
		light.Position = *position;
		light.Direction = *direction;
		light.Range = 1000.0f;
		light.Falloff = 1.0f;
		light.Attenuation0 = 1.0f;
		light.Attenuation1 = 0.0f;
		light.Attenuation2 = 0.0f;
		light.Theta = 0.4f;
		light.Phi = 0.9f;

		return light;
	}

	D3DMATERIAL9 Game::InitMtrl( D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p ) const
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient = a;
		mtrl.Diffuse = d;
		mtrl.Specular = s;
		mtrl.Emissive = e;
		mtrl.Power = p;
		return mtrl;
	}
}
