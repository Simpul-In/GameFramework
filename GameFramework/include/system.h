#ifndef GAME_FRAMEWORK_SYSTEM_H_
#define GAME_FRAMEWORK_SYSTEM_H_

#include <filesystem>
#include <vector>

// @third party code - BEGIN ENTT
#include <entt/entt.hpp>
// @third party code - END ENTT

// @third party code - BEGIN SDL2
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
// @third party code - END SDL2

// @third party code - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party code - END OneAPI

// @third party code - BEGIN Box2D
#include <box2d/box2d.h>
// @third party code - END Box2D

#include "./config.h"

namespace GameFrameWork
{
	class System
	{
	public:
		/**
		 * Texture to load an image
		 * @param config - Config of game at <config.h>
		 * @param argv - Argv of command line
		 */
		System(Config_ config, char** argv);

	public:
		/** Intialize dependencies */
		void Initialize();

		/** Application is end */
		void Exit();

	public:
		/** Create Window <SDL_Window*> */
		void CreateWindow_();
		
		/** Create Renderer <SDL_Renderer*> */
		void CreateRenderer();

		/** 
		 * Checking window and renderer is good 
		 * @return if give (True) or bad (False)
		 */
		bool CheckIsGood();

	private:
		/** Clear display */
		inline void Clear();

		/** Render or show into a display */
		inline void Show();

	private:
		/** Just prototype to handle event */
		void HandleEvent();
		
		/** Just prototype to handle renderer */
		void HandleRenderer();

	public:
		/** Run program */
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