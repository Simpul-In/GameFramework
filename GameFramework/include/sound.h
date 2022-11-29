#ifndef GAME_FRAMEWORK_PHYSICS_H_
#define GAME_FRAMEWORK_PHYSICS_H_

#include <filesystem>
#include <vector>

#include <SDL_mixer.h>

#include "controller.h"
#include "component.h"

namespace GameFrameWork
{
	namespace Sound
	{
		class Wav : public Controller
		{
		public:
			Wav(
				std::filesystem::path path,
				const int volume = 128, bool global = false);

		public:
			void Play(const size_t repeat = 1);

		public:
			bool Condition = true;

		private:
			bool isCopy_ = false;

		public:
			inline static std::vector<Component::Trash::Sound> Store;
		};

		class Music : public Controller
		{
		public:
			Music(std::filesystem::path path, const int volume = 128);

		public:
			void Play(const size_t repeat = 1);

		public:
			bool Condition = true;
		};
	}
}

#endif // GAME_FRAMEWORK_PHYSICS_H_