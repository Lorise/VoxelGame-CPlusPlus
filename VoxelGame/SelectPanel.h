#pragma once

class SelectPanel
{
public:
	SelectPanel();

	void Render();
	void Update();
	void Event();

private:
	std::shared_ptr< cSprite > m_autoPtrSpriteSelectPanel;
	std::shared_ptr< cSprite > m_autoPtrSpriteSelectItem;
	D3DXVECTOR2 m_realTextureSizeSelectPanel;
	D3DXVECTOR2 m_realTextureSizeSelectItem;

	int m_select;
};