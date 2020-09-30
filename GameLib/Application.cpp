#include "Application.h"
#include "../VoxelGame/GameEngine.h"

namespace lib
{
	cApp::cApp( Game* game, const int width, const int height, const std::string& caption )
	{
		_appWidth = width;
		_appHeight = height;
		_caption = caption;

		_game = game;
		_input = new input();
	}

	cApp::~cApp() = default;

	int cApp::OnExecute()
	{
		HRESULT hr;

		hr = OnInit();
		if ( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init application", "Error", MB_OK | MB_ICONERROR );
			OnCleanup();
			return 1;
		}

		MSG uMsg;
		ZeroMemory( &uMsg, sizeof( MSG ) );
		while ( true )
		{
			if ( PeekMessage( &uMsg, nullptr, NULL, NULL, PM_REMOVE ) )
			{
				if ( uMsg.message == WM_QUIT )
					break;

				TranslateMessage( &uMsg );
				DispatchMessage( &uMsg );
			}
			else
			{
				static int lastUpdate = timeGetTime();

				if ( timeGetTime() - lastUpdate > 1000 / 60 )
				{
					OnEvent();
					OnUpdate();

					lastUpdate = timeGetTime();
				}

				if ( timeGetTime() - lastUpdate < 1000 / 60 )
					OnRender();
			}
		}

		OnCleanup();
		SafeDeletePtr( g_engine );

		return static_cast< int >( uMsg.wParam );
	}

	HRESULT cApp::OnInit() const
	{
		HRESULT hr;

		hr = Window::Init( ( GetSystemMetrics( SM_CXSCREEN ) - _appWidth ) / 2, ( GetSystemMetrics( SM_CYSCREEN ) - _appHeight ) / 2, _appWidth, _appHeight, _caption );
		if ( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init window", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		hr = InitD3D( true );
		if ( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init D3D", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		hr = _input->Init(Window::get_hwnd() );
		if ( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init input", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		g_engine->input->mouse = _input;
		g_engine->input->keyboard = _input;
		g_engine->core->camera = new camera( desk_camera::fps );

		hr = _game->Init();
		if ( FAILED( hr ) )
		{
			MessageBox( nullptr, "Error Init game", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		return D3D_OK;
	}

	void cApp::OnEvent() const
	{
		_input->Grab();
		_game->Event();
	}

	void cApp::OnUpdate() const
	{
		_game->Update();
	}

	void cApp::OnRender() const
	{
		_game->Render();
	}

	void cApp::OnCleanup() const
	{
		SafeDeletePtr( _input );

		_game->Cleanup();
		SafeDeletePtr( _game );
	}

	HRESULT cApp::InitD3D( const bool windowed ) const
	{
		HRESULT hr;

		g_engine->core->d3d9 = Direct3DCreate9( D3D_SDK_VERSION );

		if ( g_engine->core->d3d9 == nullptr )
		{
			MessageBox( nullptr, "Error Direct3DCreate9", "Error", MB_OK | MB_ICONERROR );
			return E_FAIL;
		}

		D3DCAPS9 caps;
		g_engine->core->d3d9->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );

		int vertexProcessing;
		if ( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
			vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		else
			vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory( &d3dpp, sizeof( d3dpp ) );
		d3dpp.BackBufferWidth = 1920;
		d3dpp.BackBufferHeight = 1080;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = Window::get_hwnd();
		d3dpp.Windowed = windowed;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		hr = g_engine->core->d3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window::get_hwnd(), vertexProcessing | D3DCREATE_PUREDEVICE, &d3dpp, &g_engine->core->d3dd9 );
		//hr = g_pEngine->core->d3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _window.GetHwnd(), vertexProcessing, &d3dpp, &g_pEngine->core->d3dd9 );

		if ( FAILED( hr ) )
		{
			hr = g_engine->core->d3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window::get_hwnd(), vertexProcessing, &d3dpp, &g_engine->core->d3dd9 );

			if ( FAILED( hr ) || g_engine->core->d3dd9 == nullptr )
			{
				SafeRelease( g_engine->core->d3dd9 );
				MessageBox( nullptr, "Error CreateDevice", "Error", MB_OK | MB_ICONERROR );
				return E_FAIL;
			}
		}

		return D3D_OK;
	}
}
