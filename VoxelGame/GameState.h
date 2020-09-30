#pragma once

class GameState
{
public:
	virtual ~GameState(){}

	virtual void Init() = 0;
	virtual void Event() = 0;
	virtual void Update() = 0;
	virtual void Render( const float &interpolation ) = 0;
	virtual void Cleanup() = 0;
};