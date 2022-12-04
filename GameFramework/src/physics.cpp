// @third party code - BEGIN Box2D
#include <box2d/box2d.h>
// @third party code - END Box2D

#include "../include/system.h"
#include "../include/controller.h"
#include "../include/component.h"
#include "../include/physics.h"
#include "../include/storage.h"

namespace GameFrameWork
{
	namespace Physics
	{
		Core::Core() : Controller()
		{
			b2World* world = this->AddComponent<b2World*>(new b2World(
				b2Vec2(0.0f, System::Config.Physics.Gravity)));
			Storage::AddTrash(world);
		}

		void Core::Update()
		{
			this->GetComponent<b2World*>()->Step(
				System::Config.Physics.TimeSteps,
				static_cast<int32>(System::Config.Physics.VelocityIterations),
				static_cast<int32>(System::Config.Physics.PositionIterations));
		}

		PhysicsWorld Core::operator()()
		{
			return this->GetComponent<b2World*>();
		}

		SDL_Rect Core::GetWorldCenter(
			Component::Physics::Position position,
			Component::Physics::Size size)
		{
			SDL_Rect rect;
			
			// Settings position
			rect.x = static_cast<int>(position.X - (size.Width * 0.5f));
			rect.y = static_cast<int>(position.Y - (size.Height * 0.5f));

			// Settings size
			rect.w = static_cast<int>(size.Width);
			rect.h = static_cast<int>(size.Height);

			return rect;
		}
	}
}