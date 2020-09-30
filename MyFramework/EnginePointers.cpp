#include "stdafx.h"
#include "EnginePointers.h"
#include "functional.h"

Engine *g_pEngine = new Engine();

Core::Core()
{
	lpd3d9 = nullptr;
	lpd3dd9 = nullptr;

	camera = nullptr;
}

Core::~Core()
{
	SafeRelease( lpd3dd9 );
	SafeRelease( lpd3d9 );

	delete camera;
}


Engine::Engine()
{
	core = new Core();
	input = new InputSystem();
	sound = new SoundSystem();
}

Engine::~Engine()
{
	SafeDeletePtr( core );
	SafeDeletePtr( input );
	SafeDeletePtr( sound );
}