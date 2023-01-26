#ifndef GAME_FRAMEWORK_SHAPE_H_
#define GAME_FRAMEWORK_SHAPE_H_

// File: Controller/include/shape.h

// Standard Library - BEGIN
#include <vector>
#include <functional>
// Standard Library - END

// @third party - BEGIN SDL2
#include <SDL.h>
// @third party - END SDL2

// Include Header - BEGIN
#include <GameFramework/include/app.h>
#include <GameFramework/include/type.h>
// Include Header - END

namespace GameFramework
{
	typedef std::function<void(App*, float, float, float, float, SDL_Color)> FunctionRender;

	struct Shape
	{
		/**
		 * Points
		 * Use this to add point to draw line
		 */
		std::vector<Point> points;

		/* Color */
		SDL_Color color;

		/* Position */
		SDL_FPoint position;

		/* Angle of shape */
		float angle = 0;

		/* App */
		App* app = nullptr;

		/**
		 * Intialize shape
		 * @param app - app <App*>.
		 * @param color - color of shape.
		 * @param position - where shape position.
		 * @param angl - rotation of shape (Theta).
		 */
		Shape(App* app_, Color color_, Point position_, float angle_ = 0);
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
		static void DrawLine(App* app_, float x1, float y1, float x2, 
			float y2, SDL_Color color);

		/**
		 * To Draw Line
		 * @param x1 - x position to start.
		 * @param y1 - x position to start.
		 * @param x2 - x position end to draw.
		 * @param y2 - y position end to draw.
		 */
		static void DrawLineWithAntialiased(App* app_, float x1,
			float y1, float x2, float y2, SDL_Color color_);

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
		 * @param toolRender - Function Render (DrawLine | DrawLineWithAntialiased)
		 */
		void Render( FunctionRender toolRender = Shape::DrawLine);

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
		 * @param toolRender - Function Render (DrawLine | DrawLineWithAntialiased)
		 */
		void RenderReflection(FunctionRender toolRender = Shape::DrawLine);
	};
}

#endif // GAME_FRAMEWORK_SHAPE_H_