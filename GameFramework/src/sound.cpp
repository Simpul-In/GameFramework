#include <iostream>

#include "../include/sound.h"
#include "../include/storage.h"
#include "../include/system.h"

namespace GameFrameWork
{
	namespace Sound
	{
		Wav::Wav(
			std::filesystem::path path, 
			const int volume,
			bool global)
			: Controller()
		{
			Mix_Chunk* chunk = nullptr;
			if (global)
			{
				oneapi::tbb::parallel_for(
					oneapi::tbb::blocked_range<size_t>(0, Wav::Store.size()),
					[&](const oneapi::tbb::blocked_range<size_t>& r) -> void
					{
						if (this->isCopy_) return;
						for (size_t i = r.begin(); i != r.end(); ++i)
						{
							if (Wav::Store[i].Path == path)
							{
								this->isCopy_ = true;
								chunk = Storage::GetChunkWav(Wav::Store[i].IDX);
								return;
							}
						}
					});
			}

			if (!this->isCopy_)
			{
				chunk = Mix_LoadWAV(
					static_cast<const char*>(path.string().c_str()));

				size_t idx = Storage::AddChunkWav(chunk);

				if (global)
				{
					Component::Trash::Sound trash;
					trash.Path = path;
					trash.IDX = idx;

					Wav::Store.push_back(trash);
				}
			}

			this->AddComponent<Mix_Chunk*>(chunk);

			if (!chunk)
			{
				Mix_VolumeChunk(chunk, (volume > 128) ? 128 : volume);
			}
			else
			{
				this->Condition = false;
			}
		}

		void Wav::Play(const size_t repeat)
		{
			Mix_Chunk* chunk = this->GetComponent<Mix_Chunk*>();
			Mix_PlayChannel(-1, chunk, static_cast<int>(repeat) - 1);
		}

		Music::Music(std::filesystem::path path, const int volume)
		{
			Mix_Music* chunk = this->AddComponent<Mix_Music*>(
				Mix_LoadMUS(static_cast<const char*>(
				path.string().c_str())));
			Storage::AddChunkMusic(chunk);

			if (!chunk)
			{
				Mix_VolumeMusic((volume > 128) ? 128 : volume);
			}
			else
			{
				this->Condition = false;
			}
		}

		void Music::Play(const size_t repeat)
		{
			Mix_Music* chunk = this->GetComponent<Mix_Music*>();
			Mix_PlayMusic(chunk, static_cast<int>(repeat) - 1);
		}
	}
}