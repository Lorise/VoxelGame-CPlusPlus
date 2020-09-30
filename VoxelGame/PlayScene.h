#pragma once
#include "Headers.h"
#include "Player.h"
#include "ChunkManager.h"
#include "GameEngine.h"
#include "PauseMenu.h"
#include "DebugScreen.h"

class GameEngine;

class PlayScene : public lib::GameScene
{
public:
	PlayScene( GameEngine* gameEngine );
	~PlayScene();

	HRESULT Init();

	void Event();

	void Update();
	void FixedUpdate();

	void PreRender();
	void Render();

	void Cleanup();

	bool isPause() const;
	void SetPause(bool isPause );

private:
	bool _run;
	GameEngine* _gameEngine;
	bool _pause;
	bool _debug;

	PauseMenu* _pauseMenu;
	DebugScreen* _debugScreen;

	Player* _player;
	ChunkManager* _chunkManager;
};