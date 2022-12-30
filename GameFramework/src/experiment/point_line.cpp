#include <utility>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

// @system include - BEGIN
#include "../../include/system.h"
// @system include - END

#include "../../include/experiment/point_line.h"
#include "../../include/experiment/shape.h"

namespace GameFrameWork
{
	PointLine::PointLine(SDL_Color color_, SDL_FPoint point_, float angle_)
		: color(std::move(color_)), point(std::move(point_)),
		angle(std::move(angle_))
	{
	}

	// Formula:
	// x' = (x cos 0 - a cos 0) + (-y sin 0 + b sin 0) + a
	// y' = (x sin 0 - a sin 0) + (y cos 0 - b cos 0) + b

	float PointLine::GetRotX(float x, float y)
	{
		float nCos = cosf(Shape::Degrees(angle));
		float nSin = sinf(Shape::Degrees(angle));

		return ((x * nCos - point.x * nCos) + (-y * nSin + point.y * nSin)) + point.x;
	}

	float PointLine::GetRotY(float x, float y)
	{
		float nCos = cosf(Shape::Degrees(angle));
		float nSin = sinf(Shape::Degrees(angle));

		return ((x * nSin - point.x * nSin) + (y * nCos - point.y * nCos)) + point.y;
	}

	void PointLine::Render()
	{
		const auto& size = System::Config.Size;

		Shape::DrawLine(
			GetRotX(point.x, 0), GetRotY(point.x, 0),
			GetRotX(point.x, static_cast<float>(size.Height)),
			GetRotY(point.x, static_cast<float>(size.Height)),
			color);

		Shape::DrawLine(
			GetRotX(0, point.y), GetRotY(0, point.y),
			GetRotX(static_cast<float>(size.Width), point.y),
			GetRotY(static_cast<float>(size.Width), point.y),
			color);
	}
}