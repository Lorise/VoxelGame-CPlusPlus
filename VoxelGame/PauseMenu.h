#pragma once
#include "Headers.h"

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	HRESULT Init() const;
	void Event() const;
	void Update() const;
	void Render() const;
};