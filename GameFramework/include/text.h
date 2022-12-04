#ifndef GAME_FRAMEWORK_TEXT_H_
#define GAME_FRAMEWORK_TEXT_H_

#include <vector>
#include <filesystem>
#include <map>

// @third party code - BEGIN SDL2
#include <SDL.h>
#include <SDL_ttf.h>
// @third party code - END SDL2

#include "controller.h"
#include "component.h"
#include "typedef.h"

namespace GameFrameWork
{
	// Font
	struct StoreValueFont
	{
		TTF_Font* Font;
		size_t Size;
	};

	// Font Family
	struct StoreFontFamily
	{
		std::filesystem::path Path;
		std::vector<StoreValueFont> Stores;
	};

	/** To Manage Text */
	class Text : public Controller
	{
	public:
		/**
		 * Intialize Text
		 * @param font - Font Family will used
		 * @param text - text will show
		 * @param size - size of text
		 * @param color - color of text
		 */
		Text(std::string font, std::string text, size_t size, SDL_Color color);

	public:
		/**
		 * Rebuild text or load text
		 */
		void Load();

		/**
		 * Render text into a display
		 * @param x - x position
		 * @param y - y position
		 * @param center - make to center
		 */
		void Render(int x, int y, bool center = false);

		/**
		 * Get Texture
		 * @return TextureImage <SDL_Texture*>
		 */
		TextureImage GetTexture();

		/**
		 * Get Texture
		 * @return Surface <SDL_Surface*>
		 */
		Surface GetSurface();

	public:
		/**
		 * Add font family
		 * @param key - Name of font family
		 * @param path - What path will used (.ttf)
		 */
		static void AddFontFamily(std::string key, std::filesystem::path path);

	private:
		SDL_Texture* texture_ = nullptr;
		SDL_Surface* surface_ = nullptr;
		SDL_Rect rect_;

	public:
		inline static std::map<std::string, StoreFontFamily> FontFamily;
	};
}

#endif // GAME_FRAMEWORK_TEXT_H_