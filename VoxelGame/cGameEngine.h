#pragma once

class Cursor;
class GameState;

class cGameEngine: public mf::Game
{
public:
	cGameEngine();
	~cGameEngine() override;

	HRESULT Init() override;
	void Event() override;
	void Update() override;
	void Render( const float &interpolation ) override;
	void Cleanup() override;

private:
	std::shared_ptr< Cursor> m_autoPtrCursor;

	Environment *m_environment;

	GameState *m_gameState;
};