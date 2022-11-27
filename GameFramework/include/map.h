#ifndef GAME_FRAMEWORK_MAP_H_
#define GAME_FRAMEWORK_MAP_H_

#include <filesystem>
#include <vector>
#include <map>

#include <oneapi/tbb.h>

#include <SDL.h>

namespace GameFrameWork
{
	namespace Map
	{
		struct TextureMapID
		{
			size_t ID;
			SDL_Rect Rect;
		};

		class Texture
		{
		public:
			Texture() = default;
			Texture(std::filesystem::path path);

		public:
			void Push(TextureMapID map);
			void Push(std::vector<TextureMapID> map);

		public:
			TextureMapID Make(SDL_Rect rect);
			std::vector<SDL_Rect> Select(std::vector<size_t> IDS);

		public:
			void MakeIntoFile(std::filesystem::path path);

		public:
			std::vector<
				TextureMapID,
				oneapi::tbb::tbb_allocator<TextureMapID>> MapSource;
			std::map<size_t, SDL_Rect> Map;
		};
	}
}

#endif // GAME_FRAMEWORK_MAP_H_