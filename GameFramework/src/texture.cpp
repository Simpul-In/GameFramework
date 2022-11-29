#include <filesystem>
#include <utility>

#include <oneapi/tbb.h>

#include "../include/system.h"
#include "../include/texture.h"
#include "../include/config.h"
#include "../include/component.h"
#include "../include/storage.h"

namespace GameFrameWork
{
	Texture::Texture(std::filesystem::path path)
		: Controller()
	{
		this->Initialize(path);

		auto& config = this->GetComponent<TextureConfig>();
		config.Path = std::move(path);

		if (!this->isCopy_)
		{
			// Setup
			SDL_RWops* rwop;

			// Get image
			rwop = SDL_RWFromFile(
				static_cast<const char*>(config.Path.string().c_str()),
				"rb");
			System::SurfaceFree[config.IdSurface] = IMG_LoadPNG_RW(rwop);
			if (!System::SurfaceFree[config.IdSurface]) this->Condition = false;

			if (!this->Condition)
			{
				Storage::PopSurface();
				Storage::PopTexture();
				return;
			}

			System::TextureFree[config.IdTexture] = SDL_CreateTextureFromSurface(
				System::Renderer, System::SurfaceFree[config.IdSurface]);
		}

		// Get size of image
		Component::Default::Size size = Component::Default::Size(
			this->GetSurface()->w,
			this->GetSurface()->h);

		this->AddComponent<Component::Default::Size>(size);
	}

	void Texture::Initialize(std::filesystem::path& path)
	{
		auto& config = this->AddComponent<TextureConfig>();

		this->isCopy_ = false;
		oneapi::tbb::parallel_for(
			oneapi::tbb::blocked_range<size_t>(0, Texture::Store.size()),
			[&](const oneapi::tbb::blocked_range<size_t>& r) -> void
			{
				if (this->isCopy_) return;
				for (size_t i = r.begin(); i != r.end(); ++i)
				{
					if (Texture::Store[i].Path == path)
					{
						this->isCopy_ = true;
						config.IdSurface = Texture::Store[i].IdSurface;
						config.IdTexture = Texture::Store[i].IdTexture;
						return;
					}
				}
			});

		if (!this->isCopy_)
		{
			config.IdTexture = Storage::AddTexture(nullptr);
			config.IdSurface = Storage::AddSurface(nullptr);
		
			Component::Trash::Texture trash;
			trash.Path = path;
			trash.IdSurface = config.IdSurface;
			trash.IdTexture = config.IdTexture;

			Texture::Store.push_back(trash);
		}
	}

	SDL_Surface* Texture::GetSurface()
	{
		auto& config = this->GetComponent<TextureConfig>();
		return Storage::GetSurface(config.IdSurface);
	}

	SDL_Texture* Texture::GetTexture()
	{
		auto& config = this->GetComponent<TextureConfig>();
		return Storage::GetTexture(config.IdTexture);
	}
}