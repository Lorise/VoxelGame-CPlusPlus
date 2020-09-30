#pragma once
#include "GameState.h"

class cGameEngine;

class MainMenu: public GameState
{
public:
	explicit MainMenu( cGameEngine *gameEngine );
	~MainMenu();

	void Init() override;
	void Event() override;
	void Update() override;
	void Render( const float &interpolation ) override;
	void Cleanup() override;


private:
	std::shared_ptr<mf::ui::Button> m_autoPtrButtonPlay;
	std::shared_ptr<mf::ui::Button> m_autoPtrButtonOption;
	std::shared_ptr<mf::ui::Button> m_autoPtrButtonExit;
};