#ifndef GAME_FRAMEWORK_COMPONENT_H_
#define GAME_FRAMEWORK_COMPONENT_H_

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