#include "../include/storage.h"
#include "../include/system.h"

namespace GameFrameWork
{
	size_t Storage::AddTexture(SDL_Texture* texture)
	{
		System::TextureFree.push_back(texture);
		return System::TextureFree.size() - 1;
	}

	size_t Storage::AddSurface(SDL_Surface* texture)
	{
		System::SurfaceFree.push_back(texture);
		return System::SurfaceFree.size() - 1;
	}
	
	size_t Storage::AddTrash(void* texture)
	{
		System::TrashFree.push_back(texture);
		return System::TextureFree.size() - 1;
	}

	size_t Storage::AddChunkMusic(Mix_Music* chunk)
	{
		System::ChunkMusicFree.push_back(chunk);
		return System::ChunkMusicFree.size() - 1;
	}

	size_t Storage::AddChunkWav(Mix_Chunk* chunk)
	{
		System::ChunkWavFree.push_back(chunk);
		return System::ChunkWavFree.size() - 1;
	}

	size_t Storage::AddTTF(TTF_Font* chunk)
	{
		System::TTFFree.push_back(chunk);
		return System::TTFFree.size() - 1;
	}

	void Storage::PopTexture()
	{
		System::TextureFree.pop_back();
	}
	
	void Storage::PopSurface()
	{
		System::SurfaceFree.pop_back();
	}
	
	void Storage::PopTrash()
	{
		System::TrashFree.pop_back();
	}

	void Storage::PopChunkMusic()
	{
		System::ChunkMusicFree.pop_back();
	}

	void Storage::PopChunkWav()
	{
		System::ChunkWavFree.pop_back();
	}

	void Storage::PopTTF()
	{
		System::TTFFree.pop_back();
	}

	SDL_Texture* Storage::GetTexture(size_t idx)
	{
		return System::TextureFree[idx];
	}

	SDL_Surface* Storage::GetSurface(size_t idx)
	{
		return System::SurfaceFree[idx];
	}

	void* Storage::GetTrash(size_t idx)
	{
		return System::TrashFree[idx];
	}

	Mix_Music* Storage::GetChunkMusic(size_t idx)
	{
		return System::ChunkMusicFree[idx];
	}

	Mix_Chunk* Storage::GetChunkWav(size_t idx)
	{
		return System::ChunkWavFree[idx];
	}

	TTF_Font* Storage::GetTTF(size_t idx)
	{
		return System::TTFFree[idx];
	}
}