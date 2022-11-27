#include <box2d/box2d.h>

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

		b2World* Core::operator()()
		{
			return this->GetComponent<b2World*>();
		}
	}
}