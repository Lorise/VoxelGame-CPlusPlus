#pragma once
#include "Headers.h"

class DebugScreen
{
public:
	DebugScreen();
	~DebugScreen();

	HRESULT Init() const;
	void Event() const;
	void Update() const;
	void Render() const;
};