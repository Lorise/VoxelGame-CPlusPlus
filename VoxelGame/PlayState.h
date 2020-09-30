#pragma once
#include "GameState.h"

class GameState;
class cGameEngine;
class cPlayer;
class cChunkManager;
class cGhostCube;
class cEntityManager;
class FrontPanel;
class PauseMenu;

class PlayState: public GameState
{
public:
	PlayState() = delete;
	PlayState( PlayState& ) = delete;
	explicit PlayState( cGameEngine *gameEngine );
	~PlayState();

	void Init() override;
	void Event() override;
	void Update() override;
	void Render( const float &interpolation ) override;
	void Cleanup() override;

	bool& isPause();
	void SetPause( const bool &pause );

private:
	void LoadChunk();
	std::deque < D3DXVECTOR3 > queue;
	bool m_bRun;
	cGameEngine *m_pGameEngine;
	bool m_bPause;

	std::shared_ptr<cPlayer> m_autoPtrPlayer;
	std::shared_ptr<cChunkManager> m_autoPtrChunkManager;
	std::shared_ptr<cGhostCube> m_autoPtrGhostCube;
	std::shared_ptr<cEntityManager> m_autoPtrEntityManager;
	std::shared_ptr<FrontPanel> m_autoPtrFrontPanel;
	std::shared_ptr<PauseMenu> m_autoPtrPauseMenu;
};

inline bool& PlayState::isPause() { return m_bPause; }
inline void PlayState::SetPause( const bool &pause ) { m_bPause = pause; }