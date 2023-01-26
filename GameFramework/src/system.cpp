// File: GameFramework/src/system.cpp

// Standard Library - BEGIN
#include <iostream>
#include <vector>
#include <functional>
// Standard Library - END

// @third party - BEGIN SDL2
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
// @third party - END SDL2

// @third party - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party - END OneAPI

// Include Header - BEGIN
#include <GameFramework/include/system.h>
#include <GameFramework/include/app.h>
#include <GameFramework/include/texture.h>
#include <Controller/include/root.h>
#include <Config/include/sdl.h>
#include <Config/include/window.h>
#include <Config/include/ttf.h>
// Include Header - END

// QUEUE
std::vector<std::function<void()>> DEPS_QUIT_FUNCTION;

// FONT
extern std::vector<TTF_Font*> FONT_FREE_QUEUE;

// WINDOW And RENDERER
extern std::vector<GameFramework::Window> WINDOWS_FREE_QUEUE;
extern std::vector<GameFramework::Renderer> RENDERER_FREE_QUEUE;

// TEXTURE And SURFACE
extern std::vector<GameFramework::Image::Texture> TEXTURE_FREE_QUEUE;
extern std::vector<GameFramework::Image::Surface> SURFACE_FREE_QUEUE;

namespace GameFramework
{
	System::System(const char** argv)
	{
		// Start
		this->Initialize();

		// If all good
		if (this->good_)
		{
			// Create root from controller
			Root _start = Root();
			Config::Window::PathExecutable = std::filesystem::path(
				std::filesystem::absolute(argv[0])).parent_path();

			this->root_ = &_start;

			// Call start
			this->root_->Start();

			// Start looping
			while (!root_->hasFinish)
			{
				// Get ticks
				this->root_->ticks = SDL_GetTicks();

				// Call
				this->Events();
				this->Update();
				this->Render();

				// Proccess frame per seconds
				if (static_cast<float>(1000 / static_cast<Uint32>(Config::Window::FPS)) >
					static_cast<float>(SDL_GetTicks() - this->root_->ticks)) {
					SDL_Delay(1000 / static_cast<Uint32>(Config::Window::FPS) -
						(SDL_GetTicks() - this->root_->ticks));
				}
			}

			// End
			// Call close
			this->root_->Close();
		}

		// Do deintialize
		this->Deinitialize();
	}

	void System::Exit()
	{
		// Exit and deintialize
		good_ = false;
		this->Deinitialize();
	}

	void System::Initialize()
	{
		// Intialize SDL2
		if (SDL_Init(Config::SDL::Flags) != 0) {
			std::cout << SDL_GetError() << std::endl;
			this->Exit();
		}
		
		// Add Function to quit from SDL2
		DEPS_QUIT_FUNCTION.push_back(SDL_Quit);

		// If using image
		if (Config::SDL::UsingImage)
		{
			if ((IMG_Init(Config::SDL::FlagsImage) & Config::SDL::FlagsImage)
				!= Config::SDL::FlagsImage)
			{
				std::cout << IMG_GetError() << std::endl;
				this->Exit();
			}

			// Add Function to quit from SDL2 image
			DEPS_QUIT_FUNCTION.push_back(IMG_Quit);
		}

		// If using ttf
		if (Config::TTF::Enable)
		{
			if (TTF_Init() == -1)
			{
				std::cout << TTF_GetError() << std::endl;
				this->Exit();
			}

			// Add Function to quit from SDL2 ttf
			DEPS_QUIT_FUNCTION.push_back(TTF_Quit);
		}
	}

	void System::Deinitialize()
	{
		// Free All QUEUE
		// Renderer
		oneapi::tbb::parallel_for_each(RENDERER_FREE_QUEUE.begin(), RENDERER_FREE_QUEUE.end(),
			[&](auto& data) -> void {
				SDL_DestroyRenderer(data);
			});

		// Window
		oneapi::tbb::parallel_for_each(WINDOWS_FREE_QUEUE.begin(), WINDOWS_FREE_QUEUE.end(),
			[&](auto& data) -> void {
				SDL_DestroyWindow(data);
			});

		// Surface
		oneapi::tbb::parallel_for_each(SURFACE_FREE_QUEUE.begin(), SURFACE_FREE_QUEUE.end(),
			[&](auto& data) -> void {
				SDL_FreeSurface(data);
			});

		// Texture
		oneapi::tbb::parallel_for_each(TEXTURE_FREE_QUEUE.begin(), TEXTURE_FREE_QUEUE.end(),
			[&](auto& data) -> void {
				SDL_DestroyTexture(data);
			});

		// Font
		oneapi::tbb::parallel_for_each(FONT_FREE_QUEUE.begin(), FONT_FREE_QUEUE.end(),
			[&](auto& data) -> void {
				TTF_CloseFont(data);
			});

		// Quit
		for (auto& QuitFunction : DEPS_QUIT_FUNCTION)
		{
			QuitFunction();
		}
	}

	void System::Events()
	{
		while (App::GetEvents(this->root_->events))
		{
			switch (this->root_->events.type)
			{
			case SDL_QUIT: {
				this->root_->hasFinish = true;
			} break;
			case SDL_WINDOWEVENT: {
				this->root_->tempEvent = this->root_->events.window.event;

				if (this->root_->tempEvent == SDL_WINDOWEVENT_CLOSE) {
					this->root_->hasFinish = true;
				}

				if (this->root_->tempEvent == SDL_WINDOWEVENT_SIZE_CHANGED) {
					int w, h;
					SDL_GetWindowSize(this->root_->window, &w, &h);

					Config::Window::Width = w;
					Config::Window::Height = h;
				}
			} break;
			}

			// Call event
			this->root_->Event();
		}
	}

	void System::Update()
	{
		// Call update
		this->root_->Update();
	}

	void System::Render()
	{
		// Set background
		this->root_->SetRenderColor(Config::Window::Background);

		// Clear
		this->root_->Clear();

		// Call render
		this->root_->Render();

		// Show
		this->root_->Show();
	}
}