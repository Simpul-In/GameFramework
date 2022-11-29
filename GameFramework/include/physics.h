#ifndef GAME_FRAMEWORK_PHYSICS_H_
#define GAME_FRAMEWORK_PHYSICS_H_

#include <box2d/box2d.h>

#include "controller.h"

namespace GameFrameWork
{
	namespace Physics
	{
		class Core : public Controller
		{
		public:
			Core();

		public:
			b2World* operator()();

		public:
			void Update();
		};
	}
}

#endif // GAME_FRAMEWORK_PHYSICS_H_