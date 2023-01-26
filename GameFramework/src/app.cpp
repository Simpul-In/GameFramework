// File: GameFramework/src/app.cpp

// Standard Library - BEGIN
#include <iostream>
#include <vector>
#include <string>
// Standard Library - END

// @third party - BEGIN SDL2
#include <SDL.h>
// @third party - END SDL2

// Include Header - BEGIN
#include <GameFramework/include/app.h>
#include <Config/include/window.h>
#include <Config/include/sdl.h>
// Include Header - END

// QUEUE Will be global
std::vector<GameFramework::Window> WINDOWS_FREE_QUEUE;
std::vector<GameFramework::Renderer> RENDERER_FREE_QUEUE;

namespace GameFramework
{
	App::App()
	{
		// First Create window
		this->CreateWindowApp(
			Config::Window::Title, /* Title <String> */
			Config::Window::XPosition, /* X Position <int> */
			Config::Window::YPosition, /* Y Position <int> */
			Config::Window::Width, /* Width <int> */
			Config::Window::Height, /* Height <int> */
			Config::Window::Resizeble /* Resize <bool> */
		);

		// Check error window
		if (!this->CheckErrorSDL(this->window))
		{
			exit(EXIT_FAILURE);
		}

		// Create renderer
		App::CreateRenderApp(Config::SDL::FlagsRenderer);

		// Check error renderer
		if (!App::CheckErrorSDL(this->renderer))
		{
			exit(EXIT_FAILURE);
		}
	}

	App::App(std::string title, int x, int y, int width,
		int height, bool resize, Uint32 flags, int index)
	{
		// First Create window
		this->CreateWindowApp(
			title, /* Title <String> */
			x, /* X Position <int> */
			y, /* Y Position <int> */
			width, /* Width <int> */
			height, /* Height <int> */
			resize /* Resize <bool> */
		);

		// Check error window
		if (!this->CheckErrorSDL(this->window))
		{
			exit(EXIT_FAILURE);
		}

		// Create renderer
		App::CreateRenderApp(flags, index);

		// Check error renderer
		if (!App::CheckErrorSDL(this->renderer))
		{
			exit(EXIT_FAILURE);
		}
	}

	void App::CreateWindowApp(std::string title,
		int x, int y, int width, int height, bool resize)
	{
		// Create window
		this->window = SDL_CreateWindow(title.c_str(), x, y, width, height, 0);
		
		// If resizeble, set window into resizeble mode
		if (resize)
		{
			SDL_SetWindowResizable(this->window, SDL_TRUE);
		}
	}

	void App::CreateRenderApp(Uint32 flags, int index)
	{
		// Create renderer
		this->renderer = SDL_CreateRenderer(this->window, index, flags);
	}

	bool App::CheckErrorSDL(void* data)
	{
		// If data is null
		if (!data)
		{
			std::cout << SDL_GetError() << std::endl;
			return false;
		}
		return true;
	}

	int App::GetEvents(Events& events)
	{
		return SDL_PollEvent(&events);
	}

	void App::Show()
	{
		SDL_RenderPresent(this->renderer);
	}

	void App::Clear()
	{
		SDL_RenderClear(this->renderer);
	}

	void App::SetRenderColor(SDL_Color color)
	{
		SDL_SetRenderDrawColor(this->renderer,
			color.r, color.g, color.b, color.a);
	}
}