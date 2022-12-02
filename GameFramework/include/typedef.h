#ifndef GAME_FRAMEWORK_TYPEDEF_H_
#define GAME_FRAMEWORK_TYPEDEF_H_

// @third party code - BEGIN SDL2
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
// @third party code - END SDL2

namespace GameFrameWork
{
	typedef SDL_Surface* Surface;
	typedef SDL_Texture* TextureImage;
	typedef void* Data;
	typedef TTF_Font* TextFont;
	typedef Mix_Chunk* ChunkWAV;
	typedef Mix_Music* ChunkMusic;
}

#endif // GAME_FRAMEWORK_TYPEDEF_H_