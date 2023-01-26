// File: GameFramework/src/font.cpp

// Standard Library - BEGIN
#include <iostream>
#include <utility>
#include <vector>
// Standard Library - END

// @third party code - BEGIN SDL2
#include <SDL_ttf.h>
// @third party code - END SDL2

// @third party - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party - END OneAPI

// Include Header - BEGIN
#include <GameFramework/include/font.h>
#include <GameFramework/include/type.h>
#include <GameFramework/include/app.h>
// Include Header - END

// FONT
std::vector<TTF_Font*> FONT_FREE_QUEUE;

// TEXTURE And SURFACE
extern std::vector<GameFramework::Image::Texture> TEXTURE_FREE_QUEUE;
extern std::vector<GameFramework::Image::Surface> SURFACE_FREE_QUEUE;

namespace GameFramework
{
	void Font::AddFontFamily(std::string font, std::filesystem::path path)
	{
		Font::FontFamily[font].path = std::move(path);
	}

	TTF_Font* Font::MakeFont(std::string font, size_t size)
	{
		TTF_Font* dataFont = nullptr;

		if (Font::FontFamily.find(font) != Font::FontFamily.end())
		{
			// Check is exist
			bool isExist = false;
			oneapi::tbb::parallel_for_each(
				Font::FontFamily[font].storeFont.begin(), Font::FontFamily[font].storeFont.end(),
				[&](FontCache& data) -> void {
					if (isExist) return;
					if (data.size == size)
					{
						isExist = true;
						dataFont = data.font;
					}
				});

			if (isExist) return dataFont;

			// If not exist
			FontCache fontData;
			fontData.size = std::move(size);
			fontData.font = TTF_OpenFont(Font::FontFamily[font].path.string().c_str(),
				static_cast<int>(fontData.size));
			dataFont = fontData.font;

			// Add queue
			FONT_FREE_QUEUE.push_back(fontData.font);

			// Add into store
			Font::FontFamily[font].storeFont.push_back(fontData);
		}
		else
		{
			// print error
			std::cout << "Font doesn't exist '" << font << "'" << std::endl;
		}

		return dataFont;
	}

	CharacterStore* Font::AddCharacter(
		App* app, std::string font, char character, size_t size, SDL_Color color)
	{
		bool isExist = false;
		CharacterStore* Data = nullptr;

		// Check if there exist character
		oneapi::tbb::parallel_for(
			oneapi::tbb::blocked_range<size_t>(0, Font::StoreCharacter.size()),
			[&](const oneapi::tbb::blocked_range<size_t>& r) -> void {
				if (isExist) return;
				for (size_t i = r.begin(); i != r.end(); ++i)
				{
					if (Font::StoreCharacter[i]->character == character &&
						Font::StoreCharacter[i]->size == size &&
						Font::StoreCharacter[i]->font == font &&

						/* Color */
						Font::StoreCharacter[i]->color.r == color.r &&
						Font::StoreCharacter[i]->color.g == color.g &&
						Font::StoreCharacter[i]->color.b == color.b &&
						Font::StoreCharacter[i]->color.a == color.a)
					{
						isExist = true;
						Data = Font::StoreCharacter[i];
					}
				}
			});

		// If exist, return data
		if (isExist)
		{
			return Data;
		}

		// if not
		Data = new CharacterStore();

		// Fill data
		Data->size = std::move(size);
		Data->color = std::move(color);
		Data->font = std::move(font);
		Data->character = std::move(character);

		// Get font
		TTF_Font* fontText = Font::MakeFont(Data->font, Data->size);

		// Make character
		std::string textData = "";
		textData += Data->character;

		Data->surface = TTF_RenderText_Blended(fontText, textData.c_str(), Data->color);
		if (!Data->surface)
		{
			std::cout << TTF_GetError() << std::endl;
		}
		else
		{
			Data->texture = SDL_CreateTextureFromSurface(app->renderer, Data->surface);

			// Set sizw
			Data->sizeOfCharacter.width = static_cast<float>(Data->surface->w);
			Data->sizeOfCharacter.height = static_cast<float>(Data->surface->h);

			// Add to queue
			SURFACE_FREE_QUEUE.push_back(Data->surface);
			TEXTURE_FREE_QUEUE.push_back(Data->texture);

			// Add to storage
			Font::StoreCharacter.push_back(Data);
		}

		return Data;
	}
}