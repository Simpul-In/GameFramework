#ifndef GAME_FRAMEWORK_CONFIG_WINDOW_H_
#define GAME_FRAMEWORK_CONFIG_WINDOW_H_

// File: Config/include/window.h

// Standard Library - BEGIN
#include <filesystem>
#include <string>
#include <cstdint>
// Standard Library - END

// @third party - BEGIN SDL2
#include <SDL.h>
// @third party - END SDL2

namespace GameFramework
{
	namespace Config
	{
		/**
		 * Config Window (Edit Default Window Config In Here):
		 * - Title: String
		 * - Width: Number <Int>
		 * - Height: Number <Int>
		 */
		struct Window
		{
			inline static std::string Title = "Window Framework";
			inline static bool Resizeble = true;
			inline static Uint16 FPS = 60;
			
			// Size
			inline static int Width = 800;
			inline static int Height = 600;

			// System
			inline static std::filesystem::path PathExecutable;
			
			// Position
			inline static int XPosition = SDL_WINDOWPOS_CENTERED;
			inline static int YPosition = SDL_WINDOWPOS_CENTERED;

			inline static SDL_Color Background = {
				.r = 255, // red
				.g = 255, // green
				.b = 255, // blue
				.a = 0 // alpha
			};

			// Section Not For You Edit
			// Constructor <Dont use>
			Window() = delete;

			/**
			 * Set background color window
			 * @param Color - Color Background <SDL_Color>
			 */
			static void ChangeBackground(SDL_Color color);

			/**
			 * Set background color window
			 * @param Red - Red Color (0 - 255) <uint8_t>
			 * @param Green - Green Color (0 - 255) <uint8_t>
			 * @param Blue - Blue Color (0 - 255) <uint8_t>
			 * @param Alpha - Alpha Color (0 - 255) <uint8_t>
			 */
			static void ChangeBackground(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
		};
	}
}

#endif // GAME_FRAMEWORK_CONFIG_WINDOW_H_