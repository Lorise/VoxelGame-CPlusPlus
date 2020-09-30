#pragma once

class HungerBar
{
public:
	HungerBar();

	void Render();
	void Update();

	void SetHunger( const int &hunger );

private:
	std::shared_ptr< cSprite > m_autoPtrSpriteHunger;
	D3DXVECTOR2 m_realTextureSizeHunger;

	int m_hunger;
};

inline void HungerBar::SetHunger( const int &hunger ) { m_hunger = hunger; }