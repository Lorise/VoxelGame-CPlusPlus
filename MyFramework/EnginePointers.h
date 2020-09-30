#pragma once
#include "IInputMouse.h"
#include "IInputKeyboard.h"
#include "cCamera.h"

class Core
{
public:
	Core();
	~Core();

	LPDIRECT3D9 lpd3d9;
	LPDIRECT3DDEVICE9 lpd3dd9;

	mf::cCamera *camera;
};

class InputSystem
{
public:
	mf::IInputMouse *mouse;
	mf::IInputKeyboard *keyboard;
};

class SoundSystem
{};

class Engine
{
public:
	Engine();
	~Engine();

	Core  *core;
	InputSystem *input;
	SoundSystem *sound;
};

extern Engine *g_pEngine;