#ifndef GAME_FRAMEWORK_COMPONENT_H_
#define GAME_FRAMEWORK_COMPONENT_H_

#include <ctype.h>
#include <SDL.h>

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

				Size() : Width(0), Height(0) {}
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

				Size() : Width(0), Height(0) {}
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

				Color() = default;
				Color(const Color&) = default;
				Color(uint8_t r_, uint8_t g_, uint8_t b_, uint8_t a_)
					: r(r_), g(g_), b(b_), a(a_) {}
				Color(SDL_Color color)
					: r(color.r), g(color.g), b(color.b), a(color.a) {}
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