#ifndef GAME_FRAMEWORK_CONFIG_H_
#define GAME_FRAMEWORK_CONFIG_H_

#include <filesystem>
#include <string>

// @third party code - BEGIN SDL2
#include <SDL_image.h>
#include <SDL_mixer.h>
// @third party code - End SDL2

// @third party code - BEGIN Box2D
#include <box2d/box2d.h>
// @third party code - END Box2D

#include "component.h"

namespace GameFrameWork
{
	struct TextureConfig
	{
		std::filesystem::path Path;
		size_t IdTexture;
		size_t IdSurface;
	};

	struct SoundProccessing
	{
		bool Enable = true;
		int Frequency = MIX_DEFAULT_FREQUENCY;
		int Format = MIX_DEFAULT_FORMAT;
		int Channels = 2;
		int ChunkSize = 4096;
	};

	struct ImageProccessing
	{
		bool Enable = true;
		int Flags = /*IMG_INIT_JPG |*/ IMG_INIT_PNG;
	};

	struct PhysicsConfig
	{
		float Gravity = 9.8f;
		float TimeSteps = 1.0f / 60.0f;
		float VelocityIterations = 6.0f;
		float PositionIterations = 2.0f;
	};

	struct TTFConfig
	{
		bool Enable = true;
	};

	struct Config_
	{
		std::string Title = "Game Framework";
		bool ResizeWindow = true;
		
		size_t FPS = 60;
		SDL_Color Background = {
			/*red=*/255, 
			/*green=*/255, 
			/*blue=*/255, 
			/*alpha=*/0 };
		
		PhysicsConfig Physics;
		SoundProccessing Sound;
		TTFConfig TTF;

		ImageProccessing Image;
		Component::Default::Size Size = Component::Default::Size(
			/* Width= */800, /* Height= */600);
	};
}

#endif // GAME_FRAMEWORK_CONFIG_H_