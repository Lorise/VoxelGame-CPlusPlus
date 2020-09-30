#include "GameEngine.h"
#include "Resource.h"
#include "PlayScene.h"

GameEngine::GameEngine()
{
	_gameState = new PlayScene( this );
	//_gameState = new MainMenuScene();
}

GameEngine::~GameEngine()
{
}

HRESULT GameEngine::Init()
{
	this->SetupPixelFog( D3DCOLOR_XRGB( 191, 195, 196 ), D3DFOG_EXP2, 0.005f );

	HRESULT hr = Resource::Load();
	if ( FAILED( hr ) )
		return E_FAIL;

	_gameState->Init();

	return S_OK;
}

void GameEngine::Event()
{
	_gameState->Event();

	static bool wireframemode = false;
	if ( lib::g_engine->input->keyboard->isKeyDown( DIK_NUMPAD1 ) )
	{
		if ( !wireframemode )
			this->EnableWireframeMode();
		else
			this->DisableWireframeMode();

		wireframemode = !wireframemode;
	}
}

void GameEngine::Update()
{
	lib::Frustum::Update( 1000, lib::g_engine->core->camera->get_matrix_projection(), lib::g_engine->core->camera->get_matrix_view() );

	_gameState->Update();
}

void GameEngine::FixedUpdate()
{
}

void GameEngine::PreRender()
{
}

void GameEngine::Render()
{
	lib::g_engine->core->d3dd9->Clear( NULL, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0x1a8cff, 1.f, 0 );

	lib::g_engine->core->d3dd9->BeginScene();

	_gameState->Render();

	lib::g_engine->core->d3dd9->EndScene();

	lib::g_engine->core->d3dd9->Present( nullptr, nullptr, nullptr, nullptr );

}

void GameEngine::Cleanup()
{
	_gameState->Cleanup();
	SafeDeletePtr( _gameState );
}