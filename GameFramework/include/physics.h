#ifndef GAME_FRAMEWORK_PHYSICS_H_
#define GAME_FRAMEWORK_PHYSICS_H_

// @third party code - BEGIN Box2D
#include <box2d/box2d.h>
// @third party code - END Box2D

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