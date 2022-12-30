#ifndef PLUGIN_EXPERIMENT_POINT_LINE_H_
#define PLUGIN_EXPERIMENT_POINT_LINE_H_

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

namespace GameFrameWork
{
	struct PointLine
	{
		/* Color */
		SDL_Color color;

		/* Position */
		SDL_FPoint point;

		/* Angle of shape */
		float angle = 0;

		/**
		 * Intialize PointLine
		 * @param color - color of line.
		 * @param point - where the position.
		 * @param angle - angle (Not Recomended) (Default = 0).
		 */
		PointLine(SDL_Color color_, SDL_FPoint point_, float angle_ = 0);

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

		/** To Render Line */
		void Render();
	};
}

#endif // PLUGIN_EXPERIMENT_POINT_LINE_H_