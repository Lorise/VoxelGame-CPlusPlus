#include "Headers.h"
#include "GameEngine.h"

//#ifdef _DEBUG
int main(int argc, char *argv[])
//#else
//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
//#endif
{
	//gl::Game* game = new gl::Game();
	lib::Game* game = new GameEngine();
	lib::cApp* app = new lib::cApp(game, 1280, 720, "Voxel game");
	return app->OnExecute();
}