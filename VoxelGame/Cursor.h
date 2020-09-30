#pragma once

class Cursor
{
public:
	Cursor();
	Cursor( Cursor & ) = delete;

	void Render();
	void Update();

private:
	std::shared_ptr< cSprite > m_spriteCursor;
};