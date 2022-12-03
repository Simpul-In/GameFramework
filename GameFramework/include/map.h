#ifndef GAME_FRAMEWORK_MAP_H_
#define GAME_FRAMEWORK_MAP_H_

#include <filesystem>
#include <vector>
#include <map>

// @third party code - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party code - END OneAPI

#include <SDL.h>

namespace GameFrameWork
{
	namespace Map
	{
		/** To Store Data */
		struct TextureMapID
		{
			size_t ID;
			SDL_Rect Rect;
		};

		/** To Mapping the Texture */
		class Texture
		{
		public:
			/** Intialize Map Texture */
			Texture() = default;
			
			/**
			 * Intialize with load data from file
			 * @param path - path file data map (.json)
			 */
			Texture(std::filesystem::path path);

		public:
			/**
			 * Add Rect Map 
			 * @param map - data { id, rect }
			 */
			void Push(TextureMapID map);

			/**
			 * Add Rect Maps
			 * @param maps - data [{ id, rect }]
			 */
			void Push(std::vector<TextureMapID> maps);

		public:
			/**
			 * Make Rect Map
			 * @param rect - { x, y, w, h }
			 * @return Map { id, rect }
			 */
			TextureMapID Make(SDL_Rect rect);

			/**
			 * Get Maps
			 * @param ids - [id]
			 * @return rects [{ x, y, w, h }]
			 */
			std::vector<SDL_Rect> Select(std::vector<size_t> IDS);

		public:
			/**
			 * Write all data into a file
			 * @param path - where the file will make
			 */
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