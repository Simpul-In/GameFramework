#ifndef GAME_FRAMEWORK_TILE_H_
#define GAME_FRAMEWORK_TILE_H_

#include <filesystem>
#include <vector>

// @third party code - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party code - END OneAPI

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

#include "map.h"
#include "texture.h"

namespace GameFrameWork
{
	namespace Tile
	{
		namespace Map
		{
			struct Position
			{
				size_t x;
				size_t y;
			};

			struct TileMap
			{
				SDL_Rect* Source = nullptr;
				SDL_Rect Destination;

				size_t ID;
				Position Position_;
			};

			class Rect
			{
			public:
				Rect(
					GameFrameWork::Map::Texture& mapTexture,
					GameFrameWork::Texture& texture,
					size_t width, size_t height)
					: map_(&mapTexture), texture_(&texture),
					  Width(width), Height(height) {}
				Rect(
					GameFrameWork::Map::Texture& mapTexture,
					GameFrameWork::Texture& texture,
					std::filesystem::path path);

			public:
				size_t Create();
				void Push(size_t layer, size_t ID, size_t x, size_t y);

			public:
				void Render();

			public:
				void MakeIntoFile(std::filesystem::path path);

			public:
				size_t Width;
				size_t Height;

				std::vector<std::vector<TileMap>,
					oneapi::tbb::tbb_allocator<std::vector<TileMap>>> Tiles;

			private:
				GameFrameWork::Map::Texture* map_ = nullptr;
				GameFrameWork::Texture* texture_ = nullptr;
			};
		}
	}
}

#endif // GAME_FRAMEWORK_TILE_H_