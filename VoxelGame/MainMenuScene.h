#pragma once
#include "Headers.h"

class MainMenuScene: public lib::GameScene
{
private:
	lib::Button* _play;
	lib::Button* _exit;
	
public:
	HRESULT Init();

	void Event();

	void Update();
	void FixedUpdate();

	void PreRender();
	void Render();

	void Cleanup();
};