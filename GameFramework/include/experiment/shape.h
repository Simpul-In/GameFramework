#ifndef PLUGIN_EXPERIMENT_SHAPE_H_
#define PLUGIN_EXPERIMENT_SHAPE_H_

#include <vector>
#include <functional>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

namespace GameFrameWork
{
	struct Shape
	{
		/**
		 * Points
		 * Use this to add point to draw line
		 */
		std::vector<SDL_FRect> points;

		/* Color */
		SDL_Color color;

		/* Position */
		SDL_FRect position;

		/* Angle of shape */
		float angle = 0;

		/**
		 * Intialize shape
		 * @param color - color of shape .
		 * @param position - where shape position.
		 * @param angl - rotation of shape (Theta).
		 */
		Shape(SDL_Color color_, SDL_FRect position_, float angle_ = 0);
		Shape(const Shape&) = default;
		Shape() = default;

		/**
		 * To Get Degrees
		 * @param angl - Angle (Theta).
		 */
		static float Degrees(float angl);

		/**
		 * To Get Degrees From Radian
		 * @param rad - rad (Radian).
		 */
		static float FromRadianToDegrees(float rad);

		/**
		 * To Draw Line
		 * @param x1 - x position to start.
		 * @param y1 - x position to start.
		 * @param x2 - x position end to draw.
		 * @param y2 - y position end to draw.
		 */
		static void DrawLine(float x1, float y1, float x2, float y2, SDL_Color color);

		/**
		 * To Draw Line
		 * @param x1 - x position to start.
		 * @param y1 - x position to start.
		 * @param x2 - x position end to draw.
		 * @param y2 - y position end to draw.
		 */
		static void DrawLineWithAntialiased(float x1, float y1, float x2, float y2,
			SDL_Color color_);

		/**
		 * x' = (x cos 0 - a cos 0) + (-y sin 0 + b sin 0) + a
		 * @param x - x position.
		 * @param y - y position.
		 * @warning Not to use in external
		 */
		float GetRotX(float x, float y);

		/**
		 * y' = (x sin 0 - a sin 0) + (y cos 0 - b cos 0) + b
		 * @param x - x position.
		 * @param y - y position.
		 * @warning Not to use in external
		 */
		float GetRotY(float x, float y);

		/**
		 * Render Shape
		 * @param acceleration - use multithread to render (default = false).
		 * @warning acceleration maybe can make weird render
		 */
		void Render(bool acceleration = false,
			std::function<void(float, float, float, float, SDL_Color)> toolRender = Shape::DrawLine);

		/**
		 * x' = (x cos 0 - a cos 0) + (y sin 0 - b sin 0) + a
		 * @param x - x position.
		 * @param y - y position.
		 * @warning Not to use in external
		 */
		float GetRefX(float x, float y);

		/**
		 * y' = (x sin 0 - a sin 0) + (-y cos 0 + b cos 0) + b
		 * @param x - x position.
		 * @param y - y position.
		 * @warning Not to use in external
		 */
		float GetRefY(float x, float y);

		/**
		 * Render Shape but in reflection mode
		 * @param acceleration - use multithread to render (default = false).
		 * @warning acceleration maybe can make weird render
		 */
		void RenderReflection(bool acceleration = false,
			std::function<void(float, float, float, float, SDL_Color)> toolRender = Shape::DrawLine);
	};
}

#endif // PLUGIN_EXPERIMENT_SHAPE_H_