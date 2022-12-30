#include <iostream>
#include <utility>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

// @third party code - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party code - END OneAPI

#include "../include/system.h"
#include "../../Main/include/root.h"

namespace GameFrameWork
{
	System::System(Config_ config, char** argv)
	{
		System::Config = std::move(config);
		System::PathExecutable = std::filesystem::path(argv[0])
			.parent_path();
	}

	void System::Initialize()
	{
		SDL_SetMainReady();

		// Intialize SDL2
		if (SDL_Init(
			SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
			std::cout << SDL_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}

		// Initialize SDL2 Image
		if (System::Config.Image.Enable)
		{
			if ((IMG_Init(System::Config.Image.Flags) & System::Config.Image.Flags)
				!= System::Config.Image.Flags)
			{
				std::cout << IMG_GetError() << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		// Initiliaze SDL2 Mixer
		if (System::Config.Sound.Enable)
		{
			if (Mix_OpenAudio(
				System::Config.Sound.Frequency, 
				System::Config.Sound.Format,
				System::Config.Sound.Channels,
				System::Config.Sound.ChunkSize) == -1)
			{
				std::cout << Mix_GetError() << std::endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				Mix_AllocateChannels(32);
			}
		}

		// Initialize SDL2 TTF
		if (System::Config.TTF.Enable)
		{
			if (TTF_Init() == -1) {
				std::cout << TTF_GetError() << std::endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	void System::Exit()
	{
		auto& root_ = System::Registry.get<Root>(System::Entity);
		root_.Delete();

		// Free Surface
		oneapi::tbb::parallel_for(
			oneapi::tbb::blocked_range<size_t>(0, System::SurfaceFree.size()),
			[&](const oneapi::tbb::blocked_range<size_t>& r) -> void
			{
				for (size_t i = r.begin(); i != r.end(); ++i)
				{
					SDL_FreeSurface(System::SurfaceFree[i]);
				}
			});

		// Free Surface
		oneapi::tbb::parallel_for(
			oneapi::tbb::blocked_range<size_t>(0, System::TextureFree.size()),
			[&](const oneapi::tbb::blocked_range<size_t>& r) -> void
			{
				for (size_t i = r.begin(); i != r.end(); ++i)
				{
					SDL_DestroyTexture(System::TextureFree[i]);
				}
			});

		// Free Trash
		oneapi::tbb::parallel_for(
			oneapi::tbb::blocked_range<size_t>(0, System::TrashFree.size()),
			[&](const oneapi::tbb::blocked_range<size_t>& r) -> void
			{
				for (size_t i = r.begin(); i != r.end(); ++i)
				{
					delete System::TrashFree[i];
				}
			});

		// Chunk Wav Trash
		oneapi::tbb::parallel_for(
			oneapi::tbb::blocked_range<size_t>(0, System::ChunkWavFree.size()),
			[&](const oneapi::tbb::blocked_range<size_t>& r) -> void
			{
				for (size_t i = r.begin(); i != r.end(); ++i)
				{
					Mix_FreeChunk(System::ChunkWavFree[i]);
				}
			});

		// Chunk Music Trash
		oneapi::tbb::parallel_for(
			oneapi::tbb::blocked_range<size_t>(0, System::ChunkMusicFree.size()),
			[&](const oneapi::tbb::blocked_range<size_t>& r) -> void
			{
				for (size_t i = r.begin(); i != r.end(); ++i)
				{
					Mix_FreeMusic(System::ChunkMusicFree[i]);
				}
			});

		// Image
		if (System::Config.Image.Enable)
		{
			IMG_Quit();
		}

		// Sound
		if (System::Config.Sound.Enable)
		{
			Mix_Quit();
		}

		// TTF
		if (System::Config.TTF.Enable)
		{
			TTF_Quit();
		}

		// Window and Renderer
		if (this->windowHasCreated_)
		{
			SDL_DestroyWindow(System::Window);
		}

		if (this->rendererHasCreated_)
		{
			SDL_DestroyRenderer(System::Renderer);
		}

		// SDL2
		SDL_Quit();
	}

	void System::CreateWindow_()
	{
		this->windowHasCreated_ = true;
		System::Window = SDL_CreateWindow(System::Config.Title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			static_cast<int>(System::Config.Size.Width), 
			static_cast<int>(System::Config.Size.Height), 0);

		SDL_SetWindowResizable(System::Window, 
			static_cast<SDL_bool>(System::Config.ResizeWindow));
	}

	void System::CreateRenderer()
	{
		this->windowHasCreated_ = false;
		System::Renderer = SDL_CreateRenderer(System::Window, -1,
			SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	bool System::CheckIsGood()
	{
		bool result = true;

		if (!System::Window) {
			result = false;
			this->windowHasCreated_ = false;
		}

		if (!System::Renderer)
		{
			result = false;
			this->rendererHasCreated_ = false;
		}

		return result;
	}

	void System::Clear()
	{
		SDL_RenderClear(System::Renderer);
	}

	void System::Show()
	{
		SDL_RenderPresent(System::Renderer);
	}

	void System::Run()
	{
		System::Entity = System::Registry.create();
		System::Registry.emplace<Root>(System::Entity, Root());

		auto& root_ = System::Registry.get<Root>(System::Entity);
		root_.Start();

		while (!System::HasFinish)
		{
			System::Ticks = SDL_GetTicks();

			this->HandleEvent();

			root_.Update();

			this->HandleRenderer();

			// Proccess frame per seconds
			if (static_cast<float>(1000 / static_cast<Uint32>(System::Config.FPS)) >
				static_cast<float>(SDL_GetTicks() - System::Ticks)) {
				SDL_Delay(1000 / static_cast<Uint32>(System::Config.FPS) -
					(SDL_GetTicks() - System::Ticks));
			}
		}
	}

	void System::HandleRenderer()
	{
		auto& root_ = System::Registry.get<Root>(System::Entity);

		SDL_SetRenderDrawColor(
			/*renderer=*/System::Renderer,
			/*r=*/System::Config.Background.r,
			/*g=*/System::Config.Background.g,
			/*b=*/System::Config.Background.b,
			/*a=*/System::Config.Background.a);

		this->Clear();
		root_.Render();
		this->Show();
	}

	void System::HandleEvent()
	{
		auto& root_ = System::Registry.get<Root>(System::Entity);

		while (SDL_PollEvent(&System::Event))
		{
			switch (System::Event.type)
			{
			case SDL_QUIT: {
				System::HasFinish = true;
			} break;
			case SDL_WINDOWEVENT: {
				this->tempEvent_ = System::Event.window.event;

				if (this->tempEvent_ == SDL_WINDOWEVENT_CLOSE) {
					System::HasFinish = true;
				}

				if (this->tempEvent_ == SDL_WINDOWEVENT_SIZE_CHANGED) {
					int w, h;
					SDL_GetWindowSize(System::Window, &w, &h);

					System::Config.Size.Width = w;
					System::Config.Size.Height = h;
				}
			} break;
			}

			root_.Events();
		}
	}
}