#ifndef GAME_FRAMEWORK_COMPONENT_H_
#define GAME_FRAMEWORK_COMPONENT_H_

#include <string>
#include <ctype.h>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

namespace GameFrameWork
{
	namespace Component
	{
		namespace Default
		{
			struct Size
			{
				size_t Width;
				size_t Height;

				/** Intialize Size */
				Size() : Width(0), Height(0) {}
				
				/**
				 * Intialize Size
				 * @param width - Move Width <size_t>
				 * @param height - Move Height <size_t>
				 */
				Size(size_t  width, size_t height)
					: Width(width), Height(height) {}
			};
		}

		namespace Physics
		{
			struct Size
			{
				float Width;
				float Height;

				/** Intialize Size */
				Size() : Width(0), Height(0) {}

				/**
				 * Intialize Size
				 * @param width - Move Width <float>
				 * @param height - Move Height <float>
				 */
				Size(float  width, float height)
					: Width(width), Height(height) {}
			};
		}

		namespace Specific
		{
			struct Color
			{
				uint8_t r;
				uint8_t g;
				uint8_t b;
				uint8_t a;

				/** Intialize Color */
				Color() = default;

				/** Move Color */
				Color(const Color&) = default;

				/**
				 * Intialize Color
				 * @param r - red <uint8_t>
				 * @param g - green <uint8_t>
				 * @param b - blue <uint8_t>
				 * @param a - alpha <uint8_t>
				 */
				Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)
					: r(r_), g(g_), b(b_), a(a_) {}

				/**
				 * Intialize Color
				 * @param color - Move color <SDL_Color>
				 */
				Color(SDL_Color color)
					: r(color.r), g(color.g), b(color.b), a(color.a) {}

				/** Compare color */
				bool operator==(const Color& color)
				{
					return (
						(this->r == color.r) && (this->g == color.g) &&
						(this->b == color.b) && (this->a == color.a));
				}

				/** Get SDL_Color */
				SDL_Color operator()()
				{
					return SDL_Color({
						.r = this->r,
						.g = this->g,
						.b = this->b,
						.a = this->a,
					});
				}
			};
		}

		struct TTF
		{
			Specific::Color Color;
			std::string Family;
			std::string Text;
			size_t Size;
		};

		namespace Trash
		{
			struct Texture
			{
				std::filesystem::path Path;
				size_t IdTexture;
				size_t IdSurface;
			};

			struct Sound
			{
				std::filesystem::path Path;
				size_t IDX;
			};
		}
	}
}

#endif // GAME_FRAMEWORK_COMPONENT_H_