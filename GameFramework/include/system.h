#ifndef GAME_FRAMEWORK_SYSTEM_H_
#define GAME_FRAMEWORK_SYSTEM_H_

#include <filesystem>
#include <vector>

#include <entt/entt.hpp>

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <oneapi/tbb.h>

#include <box2d/box2d.h>

#include "./config.h"

namespace GameFrameWork
{
	class System
	{
	public:
		System(Config_ config, char** argv);

	public:
		void Initialize();
		void Exit();

	public:
		void CreateWindow_();
		void CreateRenderer();
		bool CheckIsGood();

	private:
		inline void Clear();
		inline void Show();

	private:
		void HandleEvent();
		void HandleRenderer();

	public:
		void Run();

	public:
		inline static std::filesystem::path PathExecutable;

		inline static entt::registry Registry;
		inline static entt::entity Entity;
		inline static Config_ Config;

		inline static SDL_Window* Window = nullptr;
		inline static SDL_Renderer* Renderer = nullptr;
		inline static SDL_Event Event = SDL_Event();
		inline static Uint32 Ticks = SDL_GetTicks();
		inline static bool HasFinish = false;

		/**
		* This Variable below is used to store
		* Surface and Texture, or trash
		*/
		inline static std::vector<
			SDL_Surface*,
			oneapi::tbb::tbb_allocator<SDL_Surface*>> SurfaceFree;
		inline static std::vector<
			SDL_Texture*,
			oneapi::tbb::tbb_allocator<SDL_Texture*>> TextureFree;
		inline static std::vector<void*,
			oneapi::tbb::tbb_allocator<void*>> TrashFree;
		inline static std::vector<Mix_Music*,
			oneapi::tbb::tbb_allocator<Mix_Music*>> ChunkMusicFree;
		inline static std::vector<Mix_Chunk*,
			oneapi::tbb::tbb_allocator<Mix_Chunk*>> ChunkWavFree;
		inline static std::vector<TTF_Font*,
			oneapi::tbb::tbb_allocator<TTF_Font*>> TTFFree;
	private:
		bool windowHasCreated_ = false;
		bool rendererHasCreated_ = false;
		Uint8 tempEvent_ = 0;
	};
}

#endif // GAME_FRAMEWORK_SYSTEM_H_