#ifndef GAME_FRAMEWORK_PHYSICS_H_
#define GAME_FRAMEWORK_PHYSICS_H_

#include <filesystem>
#include <vector>

// @third party code - BEGIN SDL2
#include <SDL_mixer.h>
// @third party code - END SDL2

#include "controller.h"
#include "component.h"

namespace GameFrameWork
{
	namespace Sound
	{
		/** For manage sound <file (.wav)> */
		class Wav : public Controller
		{
		public:
			/**
			 * Intialize wav
			 * @param path - path file (.wav)
			 * @param volume - max volume (128)
			 * @param global - save to global
			 * @warning global if(True) : "this will save memory but will affect the same path volume"
			 */
			Wav(
				std::filesystem::path path,
				const int volume = 128, bool global = false);

		public:
			/**
			 * Play wav
			 * @param repeat - default (1)
			 */
			void Play(const size_t repeat = 1);

		public:
			/** Conition of wav */
			bool Condition = true;

		private:
			bool isCopy_ = false;

		public:
			inline static std::vector<Component::Trash::Sound> Store;
		};

		/** For manage sound <file (.mp3)> */
		class Music : public Controller
		{
		public:
			/**
			 * Intialize music
			 * @param path - path file (.mp3)
			 * @param volume - max volume (128)
			 */
			Music(std::filesystem::path path, const int volume = 128);

		public:
			/**
			 * Play music
			 * @param repeat - default (1)
			 */
			void Play(const size_t repeat = 1);

		public:
			/** Conition of music */
			bool Condition = true;
		};
	}
}

#endif // GAME_FRAMEWORK_PHYSICS_H_