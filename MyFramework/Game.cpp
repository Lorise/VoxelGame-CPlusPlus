#include "stdafx.h"
#include "Game.h"
#include "EnginePointers.h"

namespace mf
{
	Game::Game()
	{}

	Game::~Game()
	{}

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

	void Game::Render( const float &interpolation )
	{
		g_pEngine->core->lpd3dd9->Clear( NULL, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x1a8cff, 1.f, 0 );

		g_pEngine->core->lpd3dd9->BeginScene();

		g_pEngine->core->lpd3dd9->EndScene();

		g_pEngine->core->lpd3dd9->Present( nullptr, nullptr, nullptr, nullptr );
	}

	void Game::Cleanup()
	{

	}

	HRESULT Game::SetupPixelFog( DWORD Color, FLOAT start, FLOAT end )
	{
		HRESULT hr;

		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGCOLOR, Color );
		if( FAILED( hr ) )
			return E_FAIL;

		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGTABLEMODE, D3DFOG_LINEAR );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGSTART, *reinterpret_cast< DWORD * >( &start ) );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGEND, *reinterpret_cast< DWORD * >( &end ) );
		if( FAILED( hr ) )
			return E_FAIL;

		return D3D_OK;
	}

	HRESULT Game::SetupPixelFog( DWORD Color, _D3DFOGMODE Mode, FLOAT density )
	{
		HRESULT hr;

		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGCOLOR, Color );
		if( FAILED( hr ) )
			return E_FAIL;

		if( Mode != D3DFOG_LINEAR )
		{
			hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGTABLEMODE, Mode );
			if( FAILED( hr ) )
				return E_FAIL;
			hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGDENSITY, *reinterpret_cast< DWORD * >( &density ) );
			if( FAILED( hr ) )
				return E_FAIL;
		}
		else
			return E_FAIL;

		return D3D_OK;
	}

	HRESULT Game::SetupVertexFog( DWORD Color, BOOL UseRange, FLOAT start, FLOAT end )
	{
		HRESULT hr;

		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGCOLOR, Color );
		if( FAILED( hr ) )
			return E_FAIL;

		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGSTART, *reinterpret_cast< DWORD * >( &start ) );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGEND, *reinterpret_cast< DWORD * >( &end ) );
		if( FAILED( hr ) )
			return E_FAIL;

		if( UseRange )
		{
			hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_RANGEFOGENABLE, TRUE );
			if( FAILED( hr ) )
				return E_FAIL;
		}
		else
		{
			hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_RANGEFOGENABLE, FALSE );
			if( FAILED( hr ) )
				return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT Game::SetupVertexFog( DWORD Color, _D3DFOGMODE Mode, BOOL UseRange, FLOAT Density )
	{
		HRESULT hr;

		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGENABLE, TRUE );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGCOLOR, Color );
		if( FAILED( hr ) )
			return E_FAIL;

		if( D3DFOG_LINEAR != Mode )
		{
			hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGVERTEXMODE, Mode );
			if( FAILED( hr ) )
				return E_FAIL;
			hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FOGDENSITY, *reinterpret_cast< DWORD * >( &Density ) );
			if( FAILED( hr ) )
				return E_FAIL;
		}
		else
			return E_FAIL;

		if( UseRange )
		{
			hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_RANGEFOGENABLE, TRUE );
			if( FAILED( hr ) )
				return E_FAIL;
		}
		else
		{
			hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_RANGEFOGENABLE, FALSE );
			if( FAILED( hr ) )
				return E_FAIL;
		}

		return D3D_OK;
	}

	HRESULT Game::EnableWireframeMode()
	{
		HRESULT hr;

		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
		if( FAILED( hr ) )
			return E_FAIL;

		return D3D_OK;
	}

	HRESULT Game::DisableWireframeMode()
	{
		HRESULT hr;

		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		if( FAILED( hr ) )
			return E_FAIL;
		hr = g_pEngine->core->lpd3dd9->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		if( FAILED( hr ) )
			return E_FAIL;

		return D3D_OK;
	}
}