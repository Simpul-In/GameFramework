#ifndef GAME_FRAMEWORK_STORAGE_H_
#define GAME_FRAMEWORK_STORAGE_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace GameFrameWork
{
	class Storage
	{
	public:
		static size_t AddTexture(SDL_Texture* texture);
		static size_t AddSurface(SDL_Surface* texture);
		static size_t AddTrash(void* texture);
		static size_t AddChunkWav(Mix_Chunk* chunk);
		static size_t AddChunkMusic(Mix_Music* chunk);
		static size_t AddTTF(TTF_Font* chunk);

		static void PopTexture();
		static void PopSurface();
		static void PopTrash();
		static void PopChunkWav();
		static void PopChunkMusic();
		static void PopTTF();

		static SDL_Texture* GetTexture(size_t idx);
		static SDL_Surface* GetSurface(size_t idx);
		static void* GetTrash(size_t idx);
		static Mix_Chunk* GetChunkWav(size_t idx);
		static Mix_Music* GetChunkMusic(size_t idx);
		static TTF_Font* GetTTF(size_t idx);
	};
}

#endif // GAME_FRAMEWORK_STORAGE_H_