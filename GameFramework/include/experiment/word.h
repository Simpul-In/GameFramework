#ifndef PLUGIN_EXPERIMENT_WORD_H_
#define PLUGIN_EXPERIMENT_WORD_H_

#include <map>
#include <filesystem>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

// @system include - BEGIN
#include "../text.h"
// @system include - END

namespace GameFrameWork
{
	class Word
	{
	public:
		/**
		 * Intialize Word
		 * @param fontFamily - name of font
		 * @param path - path to file (.ttf)
		 * @param color - text color
		 * @param size - size of text
		 */
		Word(std::string fontFamily, 
			std::filesystem::path path,
			SDL_Color color,
			size_t size);

	public:
		/**
		 * Write / Draw Text
		 * @param text - content
		 * @param point - position of text (not center)
		 * @param spacingText - space of between text
		 * @param space - space size
		 */
		Component::Default::Size Draw(
			std::string text, SDL_FPoint point, 
			size_t spacingText = 0, size_t space = 4);

	private:
		std::string fontFamily_;
		SDL_Color color_;
		size_t size_;

	public:
		std::map<char, Text*> characters;
	};
}

#endif // PLUGIN_EXPERIMENT_WORD_H_