#pragma once

class cChunkManager;

class cPlayer
{
public:
	cPlayer();
	~cPlayer();

	void Render();
	void Update( cChunkManager *chunkManager, const bool &pause );

	const int& GetHealth() const;
	const int& GetHunger() const;

private:
	LPD3DXMESH m_meshPlayerBody;

	float m_fSpeed;
	bool m_bJump;
	bool m_bFall;
	int m_nStartFall;

	int m_nHealth;
	int m_nHunger;
};

inline const int& cPlayer::GetHealth() const { return m_nHealth; }
inline const int& cPlayer::GetHunger() const { return m_nHunger; }