#ifndef GAME_FRAMEWORK_TEXTURE_H_
#define GAME_FRAMEWORK_TEXTURE_H_

#include <filesystem>
#include <vector>

#include <SDL.h>

#include <entt/entt.hpp>

#include "controller.h"
#include "component.h"

namespace GameFrameWork
{
	class Texture : public Controller
	{
	public:
		Texture(std::filesystem::path path);

	private:
		inline void Initialize(std::filesystem::path& path);

	public:
		SDL_Surface* GetSurface();
		SDL_Texture* GetTexture();

	public:
		bool Condition = true;
		
	private:
		bool isCopy_ = false;

	public:
		inline static std::vector<Component::Trash::Texture> Store;
	};
}

#endif // GAME_FRAMEWORK_TEXTURE_H_