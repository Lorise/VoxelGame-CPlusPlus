#pragma once
#include "Headers.h"

class GameEngine : public lib::Game
{
public:
	GameEngine();
	~GameEngine();

	HRESULT Init() override;

	void Event() override;

	void Update() override;
	void FixedUpdate() override;

	void PreRender() override;
	void Render() override;

	void Cleanup() override;

private:
	lib::GameScene* _gameState;
};