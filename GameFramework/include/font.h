#ifndef GAME_FRAMEWORK_FONT_H_
#define GAME_FRAMEWORK_FONT_H_

// File: Controller/include/font.h

// @third party code - BEGIN SDL2
#include <SDL_ttf.h>
// @third party code - END SDL2

// Standard Library - BEGIN
#include <map>
#include <vector>
#include <string>
#include <filesystem>
// Standard Library - END

// Include Header - BEGIN
#include <GameFramework/include/type.h>
#include <GameFramework/include/app.h>
// Include Header - END

namespace GameFramework
{
	struct CharacterStore
	{
		char character;
		std::string font;
		SDL_Color color;
		size_t size = 0;

		Size sizeOfCharacter = Size(0, 0);
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;
	};

	struct FontCache
	{
		TTF_Font* font;
		size_t size;
	};

	struct FontFamily
	{
		std::filesystem::path path;
		std::vector<FontCache> storeFont;

		FontFamily() = default;
	};

	class Font
	{
	public:
		/**
		 * Add font
		 * @param font - Name font <std::string>
		 * @param path - Path of font <std::filesystem::path>
		 */
		static void AddFontFamily(std::string font, std::filesystem::path path);

		/**
		 * Add font
		 * @param app - App <App*>
		 * @param character - character <char>
		 * @param size - size of character <size_t>
		 * @param color - color of character <SDL_Color>
		 * @return Format <CharacterStore>
		 */
		static CharacterStore* AddCharacter(
			App* app, std::string font, char character, size_t size, SDL_Color color);

	private:
		/**
		 * Make font
		 * @param font - Name of font <std::string>
		 * @param size - size of font
		 */
		static TTF_Font* MakeFont(std::string font, size_t size);

	public:
		/* Storing all font */
		inline static std::map<std::string, FontFamily> FontFamily;

		/* Storing all character */
		inline static std::vector<CharacterStore*> StoreCharacter;
	};
}

#endif // GAME_FRAMEWORK_FONT_H_