#ifndef GAME_FRAMEWORK_PHYSICS_H_
#define GAME_FRAMEWORK_PHYSICS_H_

// @third party code - BEGIN Box2D
#include <box2d/box2d.h>
// @third party code - END Box2D

#include "controller.h"
#include "component.h"
#include "typedef.h"

namespace GameFrameWork
{
	namespace Physics
	{
		class Core : public Controller
		{
		public:
			/** Intialize Core */
			Core();

		public:
			/**
			 * Get World Center
			 * @param position - position of object
			 * @param size - size of object
			 * @return <SDL_Rect> Just make easy
			 */
			static SDL_Rect GetWorldCenter(
				Component::Physics::Position position,
				Component::Physics::Size size);

		public:
			/**
			 * Get World
			 * @return PhysicsWorld <b2World*>
			 */
			PhysicsWorld operator()();

		public:
			/** Update physics */
			void Update();
		};
	}
}

#endif // GAME_FRAMEWORK_PHYSICS_H_