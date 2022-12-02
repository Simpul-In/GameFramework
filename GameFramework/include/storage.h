#ifndef GAME_FRAMEWORK_STORAGE_H_
#define GAME_FRAMEWORK_STORAGE_H_

// @third party code - BEGIN SDL2
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
// @third party code - END SDL2

#include "typedef.h"

namespace GameFrameWork
{
	class Storage
	{
	public:
		/**
		 * To Add Texture To Trash
		 * @param texture - Texture Will Added Into Trash.
		 */
		static size_t AddTexture(TextureImage texture);
		
		/**
		 * To Add Surface To Trash
		 * @param texture - Surface Will Added Into Trash.
		 */
		static size_t AddSurface(Surface surface);
		
		/**
		 * To Add Data To Trash
		 * @param data - Data Will Added Into Trash.
		 */
		static size_t AddTrash(Data data);
		
		/**
		 * To Add Texture To Trash
		 * @param chunk - Texture Will Added Into Trash.
		 */
		static size_t AddChunkWav(ChunkWAV chunk);
		
		/**
		 * To Add Music To Trash
		 * @param music - Music Will Added Into Trash.
		 */
		static size_t AddChunkMusic(ChunkMusic music);
		
		/**
		 * To Add Font To Trash
		 * @param font - Font Will Added Into Trash.
		 */
		static size_t AddTTF(TextFont font);

		/** Remove Tile (Back Element) Element */
		static void PopTexture();
		
		/** Remove Tile (Back Element) Element */
		static void PopSurface();

		/** Remove Tile (Back Element) Element */
		static void PopTrash();

		/** Remove Tile (Back Element) Element */
		static void PopChunkWav();

		/** Remove Tile (Back Element) Element */
		static void PopChunkMusic();

		/** Remove Tile (Back Element) Element */
		static void PopTTF();

		/**
		 * To Get Texture
		 * @param idx - Index On Trash.
		 */
		static TextureImage GetTexture(size_t idx);
		
		/**
		 * To Get Surface
		 * @param idx - Index On Trash.
		 */
		static Surface GetSurface(size_t idx);
		
		/**
		 * To Get Data
		 * @param idx - Index On Trash.
		 */
		static Data GetTrash(size_t idx);
		
		/**
		 * To Get WAV
		 * @param idx - Index On Trash.
		 */
		static Mix_Chunk* GetChunkWav(size_t idx);
		
		/**
		 * To Get Music
		 * @param idx - Index On Trash.
		 */
		static ChunkMusic GetChunkMusic(size_t idx);
		
		/**
		 * To Get Font
		 * @param idx - Index On Trash.
		 */
		static TextFont GetTTF(size_t idx);
	};
}

#endif // GAME_FRAMEWORK_STORAGE_H_