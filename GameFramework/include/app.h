#ifndef GAME_FRAMEWORK_APP_H_
#define GAME_FRAMEWORK_APP_H_

// File: GameFramework/src/app.h

// Standard Library - BEGIN
#include <string>
#include <filesystem>
// Standard Library - END

// @third party - BEGIN SDL2
#include <SDL.h>
// @third party - END SDL2

// @third party - BEGIN ENTT
#include <entt/entt.hpp>
// @third party - END ENTT

// Include Header - BEGIN
#include <GameFramework/include/type.h>
// Include Header - END

namespace GameFramework
{
	class App
	{
	public:
		// This Constructor Will Use Config
		App();

		/**
		 * @param title - title of window
		 * @param x - position X of window
		 * @param y - position Y of window
		 * @param width - width of window
		 * @param height - height of window
		 * @param resize - resizble window (False)
		 * @param flags - flags renderer (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)
		 * @param index - index renderer (-1)
		 */
		App(std::string title, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, 
			int width = 800, int height = 600, bool resize = false, 
			Uint32 flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED, 
			int index = -1);

		// Refrench
		App(const App&) = default;

	public:
		/**
		 * Create window
		 * @param window - window <Window | SDL_Window*>
		 * @param title - title of window <std::string>
		 * @param x - position x axis of window <int>
		 * @param y - position y axis of window <int>
		 * @param width - Width of window <int>
		 * @param height - Height of window <int>
		 * @param resize - make resizeble of window <bool>
		 */
		void CreateWindowApp(std::string title,
			int x, int y, int width, int height, bool resize);

		/**
		 * Create renderer
		 * @param window - window <Window | SDL_Window*>
		 * @param renderer - renderer <Renderer | SDL_Renderer*>
		 * @param flags - flags of renderer
		 * @param index - index of renderer
		 */
		void CreateRenderApp(Uint32 flags, int index = -1);

	public:
		/**
		 * Get error and print
		 * @param data - data will check <Should be pointer>
		 * @return status <bool> (False <Error> | True <Good>)
		 */
		static bool CheckErrorSDL(void* data);

	public:
		/**
		 * Get events
		 * @param events - events <Events | SDL_Event>
		 * @return (0 | None) or (1 | Exist)
		 */
		static int GetEvents(Events& events);

	public:
		// To show all render
		void Show();

		// Clear window
		void Clear();

		/**
		 * Set render color
		 * @param color - Color will set <SDL_Color>
		 */
		void SetRenderColor(SDL_Color color);

	public:
		// Window component
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDL_Event events = SDL_Event();

		// For proccessing
		bool hasFinish = false;
		Uint32 ticks = SDL_GetTicks();
		Uint8 tempEvent = 0;

		// Entity
		Registry registry;
	};
}

#endif // GAME_FRAMEWORK_APP_H_