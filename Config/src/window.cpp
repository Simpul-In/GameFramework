// File: Config/src/window.cpp

// Standard Library - BEGIN
#include <utility>
// Standard Library - END

// @third party - BEGIN SDL2
#include <SDL.h>
// @third party - END SDL2

// Include Header - BEGIN
#include <Config/include/window.h>
// Include Header - END

namespace GameFramework
{
	namespace Config
	{
		void Window::ChangeBackground(SDL_Color color)
		{
			Window::Background = std::move(color);
		}

		void Window::ChangeBackground(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
		{
			// Call self and give color
			Window::ChangeBackground(SDL_Color({
					.r = red,
					.g = blue,
					.b = blue,
					.a = alpha
				}));
		}
	}
}