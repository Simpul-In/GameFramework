// File: GameFramework/src/texture.cpp

// Standard Library - BEGIN
#include <iostream>
#include <filesystem>
#include <vector>
#include <utility>
// Standard Library - END

// @third party code - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party code - END OneAPI

// @third party - BEGIN SDL2
#include <SDL.h>
#include <SDL_image.h>
// @third party - END SDL2

// Include Header - BEGIN
#include <GameFramework/include/texture.h>
#include <GameFramework/include/type.h>
// Include Header - END

// QUEUE Will be global
std::vector<GameFramework::CacheImage> CACHE_IMAGE;
std::vector<GameFramework::Image::Texture> TEXTURE_FREE_QUEUE;
std::vector<GameFramework::Image::Surface> SURFACE_FREE_QUEUE;

namespace GameFramework
{
	Texture::Texture(App* app_, std::filesystem::path path_)
		: Path(std::move(path_)), App_(app_) {
		this->Reload();
	}

	void Texture::Reload()
	{
		bool textureIsExist = false;

		// Searching the same path
		// This will be save memory
		SDL_Surface* searchSurface = nullptr;
		SDL_Texture* searchTexture = nullptr;
		std::filesystem::path searchPath = this->Path;

		// Map all chache of image, for search the same path
		oneapi::tbb::parallel_for_each(CACHE_IMAGE.begin(), CACHE_IMAGE.end(),
			[&](GameFramework::CacheImage& cache) -> void {
				if (searchPath == cache.path)
				{
					textureIsExist = true;
					searchSurface = cache.surface;
					searchTexture = cache.texture;
				}
			});

		// If not defined
		if (!textureIsExist)
		{
			TEXTURE_FREE_QUEUE.push_back(nullptr);
			size_t idxTexture = TEXTURE_FREE_QUEUE.size() - 1;
			
			SURFACE_FREE_QUEUE.push_back(nullptr);
			size_t idxSurface = SURFACE_FREE_QUEUE.size() - 1;

			SDL_RWops* rwop;
			rwop = SDL_RWFromFile(
				static_cast<const char*>(this->Path.string().c_str()), "rb");

			SURFACE_FREE_QUEUE[idxSurface] = IMG_LoadPNG_RW(rwop);
			if (!SURFACE_FREE_QUEUE[idxSurface])
			{
				TEXTURE_FREE_QUEUE.erase(TEXTURE_FREE_QUEUE.begin() + idxTexture);
				SURFACE_FREE_QUEUE.erase(SURFACE_FREE_QUEUE.begin() + idxSurface);
			}
			else
			{
				TEXTURE_FREE_QUEUE[idxTexture] = SDL_CreateTextureFromSurface(
					this->App_->renderer, SURFACE_FREE_QUEUE[idxSurface]);

				// set
				this->surface_ = SURFACE_FREE_QUEUE[idxSurface];
				this->texture_ = TEXTURE_FREE_QUEUE[idxTexture];

				// add cache
				CacheImage makeCacheImage;
				makeCacheImage.path = this->Path;
				makeCacheImage.texture = this->texture_;
				makeCacheImage.surface = this->surface_;

				CACHE_IMAGE.push_back(makeCacheImage);
			}
		}
		else
		{
			// set
			this->surface_ = searchSurface;
			this->texture_ = searchTexture;
		}
	}

	Image::Texture Texture::GetTexture()
	{
		return this->texture_;
	}

	Image::Surface Texture::GetSurface()
	{
		return this->surface_;
	}
}