#include "stdafx.h"
#include "cApp.h"
#include "Input.h"
#include "functional.h"
#include "EnginePointers.h"
#include "Game.h"
#include "cCamera.h"
#include "cAllignedQuad.h"

namespace mf
{
	cApp::cApp( Game *const game, const int &appWidth, const int &appHeight, const std::string &appCaption )
	{
		m_nAppWidth = appWidth;
		m_nAppHeight = appHeight;
		m_strCaption = appCaption;

		m_allignedQuad = new cAllignedQuad();

		m_pGame = game;
		m_input = new Input();
	}

	cApp::~cApp()
	{}

	int cApp::OnExecute()
	{
		HRESULT hr;

		hr = OnInit();
		if( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init application", "Error", MB_OK | MB_ICONERROR );
			OnCleanup();
			return 1;
		}

		MSG uMsg;
		ZeroMemory( &uMsg, sizeof( MSG ) );
		while( true )
		{
			if( PeekMessage( &uMsg, nullptr, NULL, NULL, PM_REMOVE ) )
			{
				if( uMsg.message == WM_QUIT )
					break;

				TranslateMessage( &uMsg );
				DispatchMessage( &uMsg );
			}
			else
			{
				static int lastUpdate = timeGetTime();
				static const int ups = 1000 / 60.F;

				if( timeGetTime() - lastUpdate > ups )
				{
					OnEvent();
					OnUpdate();

					lastUpdate = timeGetTime();
				}

				float interpolation = ( timeGetTime() - lastUpdate ) / static_cast< float >( ups );

				OnRender( interpolation );
			}
		}

		OnCleanup();
		SafeDeletePtr( g_pEngine );

		return static_cast< int >( uMsg.wParam );
	}

	HRESULT cApp::OnInit()
	{
		HRESULT hr;

		hr = m_window.Init( ( GetSystemMetrics( SM_CXSCREEN ) - m_nAppWidth ) / 2, ( GetSystemMetrics( SM_CYSCREEN ) - m_nAppHeight ) / 2, m_nAppWidth, m_nAppHeight, m_strCaption );
		if( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init window", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		hr = InitD3D( true );
		if( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init D3D", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		m_allignedQuad->Init();

		hr = m_input->Init( m_window.GetHwnd() );
		if( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init input", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		g_pEngine->input->mouse = m_input;
		g_pEngine->input->keyboard = m_input;
		g_pEngine->core->camera = new cCamera( FPS );

		hr = m_pGame->Init();
		if( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init game", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		return D3D_OK;
	}

	void cApp::OnEvent()
	{
		m_input->Grab();
		m_pGame->Event();
	}

	void cApp::OnUpdate() { m_pGame->Update(); }

	void cApp::OnRender( const float &interpolation )
	{
		m_allignedQuad->Render( m_pGame, interpolation );
	}

	void cApp::OnCleanup()
	{
		SafeDeletePtr( m_input );

		m_allignedQuad->Cleanup();
		SafeDeletePtr( m_allignedQuad );

		m_pGame->Cleanup();
		SafeDeletePtr( m_pGame );
	}

	HRESULT cApp::InitD3D( const bool &windowed )
	{
		HRESULT hr;

	#pragma region CreateD3D9
		g_pEngine->core->lpd3d9 = Direct3DCreate9( D3D_SDK_VERSION );

		if( g_pEngine->core->lpd3d9 == nullptr )
		{
			MessageBox( nullptr, "Error Direct3DCreate9", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}
	#pragma endregion 

	#pragma region CreateD3DDevice9
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory( &d3dpp, sizeof( d3dpp ) );
		d3dpp.BackBufferCount = 1;
		//if( fullscreen )
		//d3dpp.FullScreen_RefreshRateInHz = displayMode.RefreshRate;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = windowed;

		//hr = g_pEngine->core->lpd3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_window.GetHwnd(), D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE, &d3dpp, &g_pEngine->core->lpd3dd9 );
		hr = g_pEngine->core->lpd3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_window.GetHwnd(), D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &g_pEngine->core->lpd3dd9 );

		if( FAILED( hr ) )
		{
			hr = g_pEngine->core->lpd3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_window.GetHwnd(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pEngine->core->lpd3dd9 );

			if( FAILED( hr ) || g_pEngine->core->lpd3dd9 == nullptr )
			{
				SafeRelease( g_pEngine->core->lpd3dd9 );
				MessageBox( nullptr, "Error CreateDevice", "Error", MB_OK | MB_ICONERROR );
				return E_FAIL;
			}
		}
	#pragma endregion 

		return D3D_OK;
	}
}