#ifndef GAME_FRAMEWORK_TEXTURE_H_
#define GAME_FRAMEWORK_TEXTURE_H_

#include <filesystem>
#include <vector>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

// @third party code - BEGIN ENTT
#include <entt/entt.hpp>
// @third party code - END ENTT

#include "controller.h"
#include "component.h"
#include "typedef.h"

namespace GameFrameWork
{
	class Texture : public Controller
	{
	public:
		/**
		 * Texture to load an image
		 * @param path - Where the path of image file.
		 */
		Texture(std::filesystem::path path);

	private:
		/**
		 * To Check There A Same Texture Are Using
		 * And Add Some Components
		 * @param path - Where the path of image file.
		 */
		inline void Initialize(std::filesystem::path& path);

	public:
		/**
		 * To Get A Surface <GameFrameWork::Surface> 
		 * @return Surface <SDL_Surface*>
		 */
		Surface GetSurface();
		
		/**
		 * To Get A Texture <GameFrameWork::TextureImage>
		 * * @return TextureImage <SDL_Texture*>
		 */
		TextureImage GetTexture();

	public:
		/** Condition Of Texture (True <Good> | False <Bad>) */
		bool Condition = true;
		
	private:
		/** Check Is Copy Texture */
		bool isCopy_ = false;

	public:
		/** Store Some Trash of Texture */
		inline static std::vector<Component::Trash::Texture> Store;
	};
}

#endif // GAME_FRAMEWORK_TEXTURE_H_