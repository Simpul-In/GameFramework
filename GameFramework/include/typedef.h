#ifndef GAME_FRAMEWORK_TYPEDEF_H_
#define GAME_FRAMEWORK_TYPEDEF_H_

// @third party code - BEGIN SDL2
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
// @third party code - END SDL2

// @third party code - BEGIN Box2D
#include <box2d/box2d.h>
// @third party code - END Box2D

namespace GameFrameWork
{
	typedef SDL_Surface* Surface;
	typedef SDL_Texture* TextureImage;
	typedef void* Data;
	typedef TTF_Font* TextFont;
	typedef Mix_Chunk* ChunkWAV;
	typedef Mix_Music* ChunkMusic;
	typedef b2World* PhysicsWorld;
}

#endif // GAME_FRAMEWORK_TYPEDEF_H_