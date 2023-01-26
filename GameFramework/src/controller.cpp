// File: GameFramework/src/controller.cpp

// @third party - BEGIN ENTT
#include <entt/entt.hpp>
// @third party - END ENTT

// Include Header - BEGIN
#include <GameFramework/include/controller.h>
// Include Header - END

namespace GameFramework
{
	Controller::Controller(App* app)
	{
		this->registry_ = &app->registry;
		this->entity_ = this->registry_->create();
	}
}