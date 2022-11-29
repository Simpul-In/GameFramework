#ifndef GAME_FRAMEWORK_TEXT_H_
#define GAME_FRAMEWORK_TEXT_H_

#include <vector>
#include <filesystem>
#include <map>

#include <SDL.h>
#include <SDL_ttf.h>

#include "controller.h"
#include "component.h"

namespace GameFrameWork
{
	struct StoreValueFont
	{
		TTF_Font* Font;
		size_t Size;
	};

	struct StoreFontFamily
	{
		std::filesystem::path Path;
		std::vector<StoreValueFont> Stores;
	};

	class Text : public Controller
	{
	public:
		Text(std::string font, std::string text, size_t size, SDL_Color color);

	public:
		void Load();
		void Render(int x, int y, bool center = false);
		SDL_Texture* GetTexture();
		SDL_Surface* GetSurface();

	public:
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