#ifndef GAME_FRAMEWORK_ANIMATION_H_
#define GAME_FRAMEWORK_ANIMATION_H_

#include <filesystem>
#include <vector>
#include <map>
#include <string>

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
	namespace Animation
	{
		class AnimationCore
		{
		public:
			std::string KeyFrame;
			size_t Frame = 0;
			size_t DelayAnimation = 100;
			bool Repeat = true;

		protected:
			std::string keyFrameNow_;
			Uint32 ticks_ = SDL_GetTicks();
		};

		struct MapID
		{
			std::string ID;
			std::vector<SDL_Rect> Frames;
		};

		class Map : public AnimationCore
		{
		public:
			Map() = default;
			Map(std::filesystem::path path);

		public:
			void Create(std::string key);
			void Push(std::string key, SDL_Rect frame);
			void Push(std::string key, std::vector<SDL_Rect> frames);

		public:
			void MakeIntoFile(std::filesystem::path path);

		public:
			void Update();

		public:
			SDL_Rect& operator()();

		public:
			std::map<std::string, std::vector<SDL_Rect>> Animation;
		};

		class Textures : public AnimationCore
		{
		public:
			Textures() = default;

		public:
			void Create(std::string key);
			void Push(std::string key, Texture frame);
			void Push(std::string key, std::vector<Texture> frames);

		public:
			void Update();

		public:
			std::map<std::string, std::vector<Texture>> Animation;
		};
	}
}

#endif // GAME_FRAMEWORK_ANIMATION_H_