#include "../include/system.h"
#include "../include/controller.h"

namespace GameFrameWork
{
	Controller::Controller()
		: entity_(System::Registry.create())
	{
		this->registry_ = &System::Registry;
	}

	std::filesystem::path Controller::PathExecutable(std::filesystem::path path)
	{
		return (System::PathExecutable / path);
	}
}