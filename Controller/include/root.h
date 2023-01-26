#ifndef GAME_FRAMEWORK_CONTROLLER_ROOT_H_
#define GAME_FRAMEWORK_CONTROLLER_ROOT_H_

// File: Controller/include/root.h
// !IMPORTANT: Dont delete "root"

// Include Header - BEGIN
#include <Controller/include/root.h>
#include <GameFramework/include/app.h>
#include <GameFramework/include/controller.h>
// Include Header - END

namespace GameFramework
{
	class Root : public App, Controller
	{
	public:
		// Constructor
		Root() : App(), Controller(this) {}

	public:
		void Start();
		void Event();
		void Update();
		void Render();
		void Close();
	};
}

#endif // GAME_FRAMEWORK_CONTROLLER_ROOT_H_