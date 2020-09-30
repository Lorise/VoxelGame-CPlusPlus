#pragma once
#include "Headers.h"
#include "ChunkManager.h"

class Player : public lib::GameObject
{
public:
	Player( ChunkManager* chunkManager );
	~Player();

	virtual void Init();

	virtual void Event();

	virtual void Update();
	virtual void FixedUpdate();

	virtual void PreRender();
	virtual void Render();

	virtual void Cleanup();

	void JumpFromCollision() const;

	int GetHealth() const;
	int GetHunger() const;

private:
	ChunkManager* _chunkManager;

	const float _playerHeight = 1.8;
	float _speed;

	int _health;
	int _hunger;

	bool m_bJump;
	bool _fall;
	int _startTimeFall;
};

