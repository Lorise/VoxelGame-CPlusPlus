#include "MainMenuScene.h"

HRESULT MainMenuScene::Init()
{
	_play = new lib::Button( D3DXVECTOR2( 0, 0 ), "Play" );
	_exit = new lib::Button( D3DXVECTOR2( 100, 100 ), "Exit" );

	return S_OK;
}

void MainMenuScene::Event()
{
}

void MainMenuScene::Update()
{
	_play->Update();
	_exit->Update();
}

void MainMenuScene::FixedUpdate()
{
}

void MainMenuScene::PreRender()
{
}

void MainMenuScene::Render()
{
	_play->Render();
	_exit->Render();
}

void MainMenuScene::Cleanup()
{
}
