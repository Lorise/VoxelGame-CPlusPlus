#pragma once

class cPlayer;
class SelectPanel;
class HealthBar;
class HungerBar;

class FrontPanel
{
public:
	FrontPanel() = delete;
	FrontPanel( std::shared_ptr<cPlayer> player );

	void Render();
	void Update();
	void Event();

private:
	std::shared_ptr<cPlayer> m_autoPtrPlayer;
	std::shared_ptr<SelectPanel> m_autoPtrSelectPanel;
	std::shared_ptr<HealthBar> m_autoPtrHealthBar;
	std::shared_ptr<HungerBar> m_autoPtrHungerBar;
};