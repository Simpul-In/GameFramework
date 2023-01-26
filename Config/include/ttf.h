#ifndef GAME_FRAMEWORK_CONFIG_TTF_H_
#define GAME_FRAMEWORK_CONFIG_TTF_H_

// File: Config/include/window.h

// Standard Library - BEGIN
#include <filesystem>
#include <string>
#include <cstdint>
// Standard Library - END

// @third party - BEGIN SDL2
#include <SDL.h>
#include <SDL_ttf.h>
// @third party - END SDL2

namespace GameFramework
{
	namespace Config
	{
		/**
		 * Config Sound (Edit Default Sound Config In Here):
		 * - Enable: Boolean
		 */
		struct TTF
		{
			inline static bool Enable = true;

			// Section Not For You Edit
			// Constructor <Dont use>
			TTF() = delete;
		};
	}
}

#endif // GAME_FRAMEWORK_CONFIG_TTF_H_