#include <iostream>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

#include "../include/config.h"
#include "../include/system.h"

#ifdef NDEBUG
#include <Windows.h>
#endif

int main(int argc, char** argv)
{
	bool isGood = true;
	GameFrameWork::Config_ config;
	GameFrameWork::System system = GameFrameWork::System(
		/* config= */config, /* argv= */argv);

	system.Initialize();

	// Create window and renderer
	system.CreateWindow_();
	system.CreateRenderer();

	// Check is ok
	if (!system.CheckIsGood())
	{
		std::cout << "Error: " << SDL_GetError() << std::endl;
		isGood = false;
	}

	// Run code
	if (isGood)
	{
		system.Run();
	}

	system.Exit();
	{
		(void)argc;
		(void)argv;
	}
	return 0;
}

#ifdef NDEBUG
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	return main(__argc, __argv);
}
#endif