#ifndef GAME_FRAMEWORK_TEXT_H_
#define GAME_FRAMEWORK_TEXT_H_

// File: Controller/include/text.h

// Standard Library - BEGIN
#include <map>
// Standard Library - END

// Include Header - BEGIN
#include <GameFramework/include/app.h>
#include <GameFramework/include/font.h>
// Include Header - END

namespace GameFramework
{
	class Text
	{
	public:
		/**
		 * Create text
		 * @param app - App <App>
		 * @param colorFont - Color of Font <SDL_Color>
		 * @param fontFamily - Font Family <std::string>
		 * @param text - text <std::string>
		 * @param sizeFont - Size of Font
		 */
		Text(App* app, SDL_Color colorFont_, std::string fontFamily_,
			std::string text_, float sizeFont_);

	public:
		/* Making text */
		void Make();

		/**
		 * Render Text
		 * @param x - x position <float>
		 * @param y - y position <float>
		 * @param center - make center (Default = False) <Bool>
		 */
		void Render(float x, float y, bool center = false);

	public:
		std::string text;
		std::string fontFamily;
		SDL_Color colorFont;
		float sizeFont;

	public:
		Size sizeText;

	private:
		App* app_;
		float averageOfEachText_[2] = { 
			0, // Horizontal 
			0 // Vertical
		};

		SDL_FRect rectCharacter_;
		std::map<char, CharacterStore*> storeCharacter_;
	};
}

#endif // GAME_FRAMEWORK_TEXT_H_