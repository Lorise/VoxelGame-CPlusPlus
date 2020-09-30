#include "PlayScene.h"

PlayScene::PlayScene( GameEngine* gameEngine ) :
	_run( true ),
	_pause( false ),
	_debug( false ),
	_gameEngine( gameEngine )
{

}

PlayScene::~PlayScene()
{
	_run = false;
}

HRESULT PlayScene::Init()
{
	_pauseMenu = new PauseMenu();
	_debugScreen = new DebugScreen();

	_chunkManager = new ChunkManager();
	_player = new Player( _chunkManager );

	return S_OK;
}

void PlayScene::Event()
{
	if ( _pause )
		_pauseMenu->Event();

	if ( _debug )
		_debugScreen->Event();

	_player->Event();

	static int lastTime = timeGetTime();
	if ( timeGetTime() - lastTime > 200 )
	{
		if ( lib::g_engine->input->keyboard->isKeyPress( DIK_ESCAPE ) )
		{
			_pause = !_pause;
			lastTime = timeGetTime();
		}
	}
}

void PlayScene::Update()
{
	if ( _pause )
		_pauseMenu->Update();

	if ( _debug )
		_debugScreen->Update();

	_chunkManager->Update();
	_player->Update();

	D3DXVECTOR3 dir( 1.0f, -0.0f, 0.25f );
	D3DXCOLOR c = WHITE;
	D3DLIGHT9 dirLight = InitDirectionalLight( &dir, &c );
	lib::g_engine->core->d3dd9->SetLight( 0, &dirLight );
	lib::g_engine->core->d3dd9->LightEnable( 0, true );
}

void PlayScene::FixedUpdate()
{
	_player->FixedUpdate();
}

void PlayScene::PreRender()
{
	_player->PreRender();
}

void PlayScene::Render()
{
	if ( _pause )
		_pauseMenu->Render();

	if ( _debug )
		_debugScreen->Render();

	_chunkManager->Render();
	_player->Render();
}

void PlayScene::Cleanup()
{
	lib::SafeDeletePtr( _pauseMenu );
	lib::SafeDeletePtr( _debugScreen );

	lib::SafeDeletePtr( _chunkManager );
	SafeDeletePtr( _player );
}

bool PlayScene::isPause() const
{
	return _pause;
}

void PlayScene::SetPause( const bool isPause )
{
	_pause = isPause;
}
