#ifndef GAME_FRAMEWORK_TEXTURE_H_
#define GAME_FRAMEWORK_TEXTURE_H_

// File: GameFramework/include/texture.h

// Standard Library - BEGIN
#include <filesystem>
// Standard Library - END

// @third party - BEGIN SDL2
#include <SDL.h>
// @third party - END SDL2

// Include Header - BEGIN
#include <GameFramework/include/app.h>
#include <GameFramework/include/type.h>
// Include Header - END

namespace GameFramework
{
	struct CacheImage
	{
		std::filesystem::path path;
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;
	};

	class Texture
	{
	public:
		/**
		 * Load texture from file
		 * @param path - where the path of file <std::filesystem::path <C++2a>>
		 */
		Texture(App* app_, std::filesystem::path path_);
		Texture(const Texture&) = default;

	public:
		/**
		 * Reload texture
		 * @warning this work if you change the path of texture
		 */
		void Reload();

	public:
		/**
		 * Get texture <Image::Texture | SDL_Texture*>
		 * @return Image::Texture
		 */
		Image::Texture GetTexture();

		/**
		 * Get surface <Image::Surface | SDL_Surface*>
		 * @return Image::Texture
		 */
		Image::Surface GetSurface();

	public:
		/* Path to texture */
		std::filesystem::path Path;

		/* App */
		App* App_ = nullptr;

	private:
		SDL_Surface* surface_;
		SDL_Texture* texture_;
	};
}

#endif // GAME_FRAMEWORK_TEXTURE_H_