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
				/**
				 * Intialize Tile::Map::Rect
				 * @param mapTexture - Map Texture
				 * @param texture - texture will used
				 * @param width - width of tile
				 * @param height - height of tile
				 */
				Rect(
					GameFrameWork::Map::Texture& mapTexture,
					GameFrameWork::Texture& texture,
					size_t width, size_t height)
					: map_(&mapTexture), texture_(&texture),
					  Width(width), Height(height) {}

				/**
				 * Intialize Tile::Map::Rect
				 * @param mapTexture - Map Texture
				 * @param texture - texture will used
				 * @param path - Load data from file (.json)
				 */
				Rect(
					GameFrameWork::Map::Texture& mapTexture,
					GameFrameWork::Texture& texture,
					std::filesystem::path path);

			public:
				/** Create layer */
				size_t Create();

				/**
				 * Add Tile
				 * @param layer - index layer from (function Tile::Map::Rect::Create())
				 * @param ID - ID Map Texture
				 * @param x - x tile
				 * @param y - y tile
				 */
				void Push(size_t layer, size_t ID, size_t x, size_t y);

			public:
				/** Render tiles */
				void Render();

			public:
				/**
				  * Make into file
				  * @param path - where file will write
				  */
				void MakeIntoFile(std::filesystem::path path);

			public:
				// Width of tile
				size_t Width;

				// Height of tile
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