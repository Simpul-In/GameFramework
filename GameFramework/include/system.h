#ifndef GAME_FRAMEWORK_SYSTEM_H_
#define GAME_FRAMEWORK_SYSTEM_H_

// File: GameFramework/src/system.h

// Include Header - BEGIN
#include <Controller/include/root.h>
// Include Header - END

namespace GameFramework
{
	/**
	 * System used in core, And Not Use to another things
	 */
	class System
	{
	public:
		// Initialize constructor <System>
		System(const char** argv);

	private:
		// Exit
		void Exit();

		// Intialize dependencies
		void Initialize();

		// Deinitialize dependencies
		void Deinitialize();

	public:
		void Events();
		void Update();
		void Render();

	private:
		Root* root_ = nullptr;
		bool good_ = true;
	};
}

#endif // GAME_FRAMEWORK_SYSTEM_H_