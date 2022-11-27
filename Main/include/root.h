#ifndef MAIN_ROOT_H_
#define MAIN_ROOT_H_

// IMPORTANT: Don't Change This
#include "../../GameFramework/include/controller.h"

#include "debug.h"

namespace GameFrameWork
{
	class Root : public GameFrameWork::Controller
	{
	public:
		Root() : Controller() {}

	public:
		void Start();
		void Events();
		void Update();
		void Render();
		void Delete();
	};
}

#endif // MAIN_ROOT_H_