#include "../include/storage.h"
#include "../include/system.h"

namespace GameFrameWork
{
	size_t Storage::AddTexture(TextureImage texture)
	{
		System::TextureFree.push_back(texture);
		return System::TextureFree.size() - 1;
	}

	size_t Storage::AddSurface(Surface surface)
	{
		System::SurfaceFree.push_back(surface);
		return System::SurfaceFree.size() - 1;
	}
	
	size_t Storage::AddTrash(Data data)
	{
		System::TrashFree.push_back(data);
		return System::TrashFree.size() - 1;
	}

	size_t Storage::AddChunkMusic(ChunkMusic music)
	{
		System::ChunkMusicFree.push_back(music);
		return System::ChunkMusicFree.size() - 1;
	}

	size_t Storage::AddChunkWav(ChunkWAV chunk)
	{
		System::ChunkWavFree.push_back(chunk);
		return System::ChunkWavFree.size() - 1;
	}

	size_t Storage::AddTTF(TextFont font)
	{
		System::TTFFree.push_back(font);
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

	TextureImage Storage::GetTexture(size_t idx)
	{
		return System::TextureFree[idx];
	}

	Surface Storage::GetSurface(size_t idx)
	{
		return System::SurfaceFree[idx];
	}

	Data Storage::GetTrash(size_t idx)
	{
		return System::TrashFree[idx];
	}

	ChunkMusic Storage::GetChunkMusic(size_t idx)
	{
		return System::ChunkMusicFree[idx];
	}

	ChunkWAV Storage::GetChunkWav(size_t idx)
	{
		return System::ChunkWavFree[idx];
	}

	TextFont Storage::GetTTF(size_t idx)
	{
		return System::TTFFree[idx];
	}
}