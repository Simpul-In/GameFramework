#ifndef GAME_FRAMEWORK_CONFIG_SDL_H_
#define GAME_FRAMEWORK_CONFIG_SDL_H_

// File: Config/include/sdl.h

// Standard Library - BEGIN
#include <cstdint>
// Standard Library - END

// @third party - BEGIN SDL2
#include <SDL.h>
#include <SDL_image.h>
// @third party - END SDL2

namespace GameFramework
{
	namespace Config
	{
		/**
		 * Config SDL2 (Edit Default SDL2 Config In Here):
		 * - Flags: Number <Unsigned Int 32>
		 * - FlagsRenderer: Number <Unsigned Int 32>
		 * - UsingImage: boolean
		 * - FlagsImage: Number <Int>
		 */
		struct SDL
		{
			inline static Uint32 Flags = SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS;
			inline static Uint32 FlagsRenderer = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;
			
			// Extension SDL2
			// Image
			inline static bool UsingImage = true; // SDL2_Image
			inline static int FlagsImage = /*IMG_INIT_JPG |*/ IMG_INIT_PNG;

			// Constructor <Dont use>
			SDL() = delete;
		};
	}
}

#endif // GAME_FRAMEWORK_CONFIG_SDL_H_