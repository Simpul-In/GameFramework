// File: GameFramework/src/main.cpp

// @System API - BEGIN WIN32
#ifdef NDEBUG
#include <Windows.h>
#endif
// @System API - END WIN32

// Include Header - BEGIN
#include <GameFramework/include/system.h>
// Include Header - END

// First gate, where the first function will be exec
int main(int argc, const char* argv[])
{
	// Start
	GameFramework::System system = GameFramework::System(argv);
	
	// End
	return 0;
}

// If compile with "Release" mode
#ifdef NDEBUG
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	return main(__argc, __argv);
}
#endif