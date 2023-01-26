// File: GameFramework/src/shape.cpp

// Standard Library - BEGIN
#include <vector>
#include <utility>
#include <numeric>
#include <cmath>
#include <algorithm>
// Standard Library - END

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

// Include Header - BEGIN
#include <GameFramework/include/app.h>
#include <GameFramework/include/shape.h>
// Include Header - END

namespace GameFramework
{
	Shape::Shape(App* app_, Color color_, Point position_, float angle_)
		: app(app_), color(std::move(color_)), position(std::move(position_)),
		angle(std::move(angle_)) {}

	float Shape::Degrees(float angl)
	{
		return (angl * (static_cast<float>(M_PI) / 180.0f));
	}

	float Shape::FromRadianToDegrees(float rad)
	{
		return ((180.0f / static_cast<float>(M_PI)) * rad);
	}

	void Shape::DrawLine(App* app_, float x1, float y1, float x2, float y2, SDL_Color color_)
	{
		SDL_SetRenderDrawColor(app_->renderer,
			color_.r, color_.g, color_.b, color_.a);

		float dx = x2 - x1;
		float dy = y2 - y1;

		float length = std::sqrt(dx * dx + dy * dy);
		float angle = std::atan2(dy, dx);

		for (float i = 0; i < length; i++)
		{
			SDL_RenderDrawPointF(app_->renderer,
				x1 + std::cos(angle) * i,
				y1 + std::sin(angle) * i);
		}
	}

	// Formula:
	// x' = (x cos 0 - a cos 0) + (-y sin 0 + b sin 0) + a
	// y' = (x sin 0 - a sin 0) + (y cos 0 - b cos 0) + b

	float Shape::GetRotX(float x, float y)
	{
		float nCos = cosf(Shape::Degrees(angle));
		float nSin = sinf(Shape::Degrees(angle));

		return ((x * nCos - position.x * nCos) + (-y * nSin + position.y * nSin)) + position.x;
	}

	float Shape::GetRotY(float x, float y)
	{
		float nCos = cosf(Shape::Degrees(angle));
		float nSin = sinf(Shape::Degrees(angle));

		return ((x * nSin - position.x * nSin) + (y * nCos - position.y * nCos)) + position.y;
	}

	void Shape::Render(FunctionRender toolRender)
	{
		size_t idx = 0;

		for (size_t i = 0; i < points.size(); ++i)
		{
			idx = (i >= points.size() - 1) ? 0 : i + 1;
			toolRender(
				app,
				GetRotX(position.x + points[i].x, position.y + points[i].y),
				GetRotY(position.x + points[i].x, position.y + points[i].y),
				GetRotX(position.x + points[idx].x, position.y + points[idx].y),
				GetRotY(position.x + points[idx].x, position.y + points[idx].y),
				color
			);
		}
	}

	// Formula:
	// x' = (x cos 0 - a cos 0) + (y sin 0 - b sin 0) + a
	// y' = (x sin 0 - a sin 0) + (-y cos 0 + b cos 0) + b

	float Shape::GetRefX(float x, float y)
	{
		float nCos = cosf(Shape::Degrees(angle));
		float nSin = sinf(Shape::Degrees(angle));

		return ((x * nCos - position.x * nCos) + (y * nSin - position.y * nSin)) + position.x;
	}

	float Shape::GetRefY(float x, float y)
	{
		float nCos = cosf(Shape::Degrees(angle));
		float nSin = sinf(Shape::Degrees(angle));

		return ((x * nSin - position.x * nSin) + (-y * nCos + position.y * nCos)) + position.y;
	}

	void Shape::RenderReflection(FunctionRender toolRender)
	{
		size_t idx = 0;

		for (size_t i = 0; i < points.size(); ++i)
		{
			idx = (i >= points.size() - 1) ? 0 : i + 1;
			toolRender(
				app,
				GetRefX(position.x + points[i].x, position.y + points[i].y),
				GetRefY(position.x + points[i].x, position.y + points[i].y),
				GetRefX(position.x + points[idx].x, position.y + points[idx].y),
				GetRefY(position.x + points[idx].x, position.y + points[idx].y),
				color
			);
		}
	}

	// ! IMPORTANT: parameter should be => n + 1, Not same as on header
	void Shape::DrawLineWithAntialiased(App* app_, float x0, float y0, float x1, float y1,
		SDL_Color color_) {
		auto ipart = [](float x) -> int {return int(std::floor(x)); };
		auto round = [](float x) -> float {return std::round(x); };
		auto fpart = [](float x) -> float {return x - std::floor(x); };
		auto rfpart = [=](float x) -> float {return 1 - fpart(x); };
		auto plot = [&](int x, int y, float brightess) -> void {
			SDL_SetRenderDrawColor(app_->renderer,
				static_cast<int>(static_cast<float>(color_.r) * brightess),
				static_cast<int>(static_cast<float>(color_.g) * brightess),
				static_cast<int>(static_cast<float>(color_.a) * brightess),
				0
			);
			SDL_RenderDrawPoint(app_->renderer, x, y);
		};

		const bool steep = abs(y1 - y0) > abs(x1 - x0);
		if (steep)
		{
			std::swap(x0, y0);
			std::swap(x1, y1);
		}
		if (x0 > x1)
		{
			std::swap(x0, x1);
			std::swap(y0, y1);
		}

		const float dx = x1 - x0;
		const float dy = y1 - y0;
		const float gradient = (dx == 0) ? 1 : dy / dx;

		int xpx11;
		float intery;
		{
			const float xend = round(x0);
			const float yend = y0 + gradient * (xend - x0);
			const float xgap = rfpart(x0 + 0.5f);
			xpx11 = int(xend);
			const int ypx11 = ipart(yend);
			if (steep)
			{
				plot(ypx11, xpx11, rfpart(yend) * xgap);
				plot(ypx11 + 1, xpx11, fpart(yend) * xgap);
			}
			else
			{
				plot(xpx11, ypx11, rfpart(yend) * xgap);
				plot(xpx11, ypx11 + 1, fpart(yend) * xgap);
			}
			intery = yend + gradient;
		}

		int xpx12;
		{
			const float xend = round(x1);
			const float yend = y1 + gradient * (xend - x1);
			const float xgap = rfpart(x1 + 0.5f);
			xpx12 = int(xend);
			const int ypx12 = ipart(yend);
			if (steep)
			{
				plot(ypx12, xpx12, rfpart(yend) * xgap);
				plot(ypx12 + 1, xpx12, fpart(yend) * xgap);
			}
			else
			{
				plot(xpx12, ypx12, rfpart(yend) * xgap);
				plot(xpx12, ypx12 + 1, fpart(yend) * xgap);
			}
		}

		if (steep)
		{
			for (int x = xpx11 + 1; x < xpx12; x++)
			{
				plot(ipart(intery), x, rfpart(intery));
				plot(ipart(intery) + 1, x, fpart(intery));
				intery += gradient;
			}
		}
		else
		{
			for (int x = xpx11 + 1; x < xpx12; x++)
			{
				plot(x, ipart(intery), rfpart(intery));
				plot(x, ipart(intery) + 1, fpart(intery));
				intery += gradient;
			}
		}
	}
}