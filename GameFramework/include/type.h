#ifndef GAME_FRAMEWORK_TYPE_H_
#define GAME_FRAMEWORK_TYPE_H_

// Standard Library - BEGIN
#include <utility>
// Standard Library - END

// @third party - BEGIN ENTT
#include <entt/entt.hpp>
// @third party - END ENTT

// @third party - BEGIN SDL2
#include <SDL.h>
// @third party - END SDL2

namespace GameFramework
{
	// App
	typedef SDL_Window* Window;
	typedef SDL_Renderer* Renderer;
	typedef SDL_Event Events;

	// Data
	typedef void* Data;

	// Position
	struct Position
	{
		float x;
		float y;

		/**
		 * Intialize Position
		 * @param width - width
		 * @param height - height
		 */
		Position(float x_, float y_)
			: x(std::move(x_)), y(std::move(y_)) {}
		Position(const Position&) = default;
		Position() = default;
	};

	// Size
	struct Size
	{
		float width;
		float height;

		/**
		 * Intialize size
		 * @param width - width
		 * @param height - height
		 */
		Size(float width_, float height_)
			: width(std::move(width_)), height(std::move(height_)) {}
		Size(const Size&) = default;
		Size() = default;
	};

	// Image
	namespace Image
	{
		typedef SDL_Surface* Surface;
		typedef SDL_Texture* Texture;
	}

	// Entt
	typedef entt::registry Registry;
	typedef entt::entity Entity;

	// Define
	typedef SDL_FPoint Point;
	typedef SDL_Color Color;
}

#endif // GAME_FRAMEWORK_TYPE_H_