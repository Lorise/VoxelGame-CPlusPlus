#include "stdafx.h"
#include "PlayState.h"
#include "config.h"
#include "cChunkManager.h"
#include "cEntityManager.h"
#include "FrontPanel.h"
#include "PauseMenu.h"
#include "cGhostCube.h"
#include "cPlayer.h"

void PlayState::LoadChunk()
{
	for (int x = 1000; x < 1003; x++)
	{
		for (int z = 1000; z < 1003; z++)
		{
			m_autoPtrChunkManager->GenerateChunk(x, 0, z);
			m_autoPtrChunkManager->SetLoadChunk(x, 0, z, true);

			m_autoPtrChunkManager->GenerateChunkMesh(x, 0, z);
			m_autoPtrChunkManager->SetReadyChunk(x, 0, z, true);
		}
	}

}

PlayState::PlayState(cGameEngine *gameEngine)
{
	m_bRun = true;
	m_bPause = false;
	m_pGameEngine = gameEngine;
}

PlayState::~PlayState()
{
	m_bRun = false;
}

void PlayState::Init()
{
	m_autoPtrChunkManager = std::make_shared<cChunkManager>();
	m_autoPtrGhostCube = std::make_shared<cGhostCube>();
	m_autoPtrPlayer = std::make_shared<cPlayer>();
	m_autoPtrEntityManager = std::make_shared<cEntityManager>();
	m_autoPtrFrontPanel = std::make_shared<FrontPanel>(m_autoPtrPlayer);
	m_autoPtrPauseMenu = std::make_shared<PauseMenu>();

	LoadChunk();
}

void PlayState::Event()
{
	m_autoPtrFrontPanel->Event();
	if (m_bPause)
		m_autoPtrPauseMenu->Event();

	static int lastTime = timeGetTime();
	if (timeGetTime() - lastTime > 200)
	{
		if (g_pEngine->input->keyboard->isKeyPress(DIK_ESCAPE))
		{
			m_bPause = !m_bPause;
			lastTime = timeGetTime();
		}
	}
}

void PlayState::Update()
{
	m_autoPtrChunkManager->Update();
	m_autoPtrGhostCube->Update(m_autoPtrChunkManager.get(), m_autoPtrEntityManager.get());
	m_autoPtrPlayer->Update(m_autoPtrChunkManager.get(), m_bPause);
	m_autoPtrEntityManager->Update(m_autoPtrChunkManager.get());
	m_autoPtrFrontPanel->Update();

	if (m_bPause)
		m_autoPtrPauseMenu->Update();
}

void PlayState::Render(const float &interpolation)
{
	m_autoPtrChunkManager->Render();

	m_autoPtrGhostCube->Render();
	m_autoPtrPlayer->Render();
	m_autoPtrEntityManager->Render();
	m_autoPtrFrontPanel->Render();
	if (m_bPause)
		m_autoPtrPauseMenu->Render(interpolation);
}

void PlayState::Cleanup()
{
}