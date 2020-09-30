#pragma once

class HealthBar
{
public:
	HealthBar();

	void Render();
	void Update();

	void SetHealth( const int &health );

private:
	std::shared_ptr<cSprite> m_autoPtrSpriteHealth;
	D3DXVECTOR2 m_realSizeTextureHealth;

	int m_health;
};

inline void HealthBar::SetHealth( const int &health ) { m_health = health; }