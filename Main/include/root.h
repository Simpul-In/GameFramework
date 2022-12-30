#ifndef MAIN_ROOT_H_
#define MAIN_ROOT_H_

// IMPORTANT: Don't Change This
#include "../../GameFramework/include/controller.h"

#include "debug.h"

namespace GameFrameWork
{
	/** Root of program */
	class Root : public GameFrameWork::Controller
	{
	public:
		Root() : Controller() {}

	public:
		/** First Program Launch */
		void Start();
		
		/** For Handle Events */
		void Events();

		/** Do something */
		void Update();

		/** Show into a display */
		void Render();

		/** Exit Program */
		void Delete();
	};
}

#endif // MAIN_ROOT_H_