#include <utility>

#include <oneapi/tbb.h>

#include "../include/text.h"
#include "../include/component.h"
#include "../include/storage.h"
#include "../include/system.h"

namespace GameFrameWork
{
	Text::Text(std::string font, std::string text, size_t size, SDL_Color color)
	{
		Component::TTF component;
		component.Color = std::move(color);
		component.Family = std::move(font);
		component.Text = std::move(text);
		component.Size = std::move(size);

		this->AddComponent<Component::TTF>(component);
		this->AddComponent<Component::Default::Size>();

		Storage::AddTexture(this->texture_);
		Storage::AddSurface(this->surface_);
		
		this->Load();
	}

	void Text::Load()
	{
		auto& sizeText = this->GetComponent<Component::Default::Size>();
		auto& component = this->GetComponent<Component::TTF>();
		auto& fontFamily = Text::FontFamily[component.Family];

		// Free
		if (this->texture_) SDL_DestroyTexture(this->texture_);
		if (this->surface_) SDL_FreeSurface(this->surface_);

		bool status = false;
		size_t idx = 0;

		// Search
		oneapi::tbb::parallel_for(
			oneapi::tbb::blocked_range<size_t>(0, fontFamily.Stores.size()),
			[&](const oneapi::tbb::blocked_range<size_t>& r) -> void
			{
				if (status) return;
				for (size_t i = r.begin(); i != r.end(); ++i)
				{
					if (component.Size == fontFamily.Stores[i].Size)
					{
						status = true;
						idx = i;
						return;
					}
				}
			});

		if (!status)
		{
			StoreValueFont store;

			size_t idxTTF = Storage::AddTTF(
				TTF_OpenFont(fontFamily.Path.string().c_str(),
					static_cast<int>(component.Size)));
			store.Size = component.Size;
			store.Font = Storage::GetTTF(idxTTF);

			fontFamily.Stores.push_back(store);
			idx = fontFamily.Stores.size() - 1;
		}

		this->surface_ = TTF_RenderText_Blended(
			fontFamily.Stores[idx].Font, component.Text.c_str(),
			SDL_Color({
				.r = component.Color.r, 
				.g = component.Color.g,
				.b = component.Color.b, 
				.a = component.Color.a
			}));
		this->texture_ = SDL_CreateTextureFromSurface(System::Renderer, this->surface_);

		sizeText.Width = static_cast<size_t>(this->surface_->w);
		sizeText.Height = static_cast<size_t>(this->surface_->h);
	}

	void Text::Render(int x, int y, bool center)
	{
		auto& sizeText = this->GetComponent<Component::Default::Size>();

		rect_.x = x;
		rect_.y = y;
		rect_.w = static_cast<int>(sizeText.Width);
		rect_.h = static_cast<int>(sizeText.Height);

		if (center)
		{
			rect_.x -= rect_.w / 2;
			rect_.y -= rect_.h / 2;
		}

		SDL_RenderCopy(System::Renderer, this->texture_, NULL, &rect_);
	}

	SDL_Texture* Text::GetTexture()
	{
		return this->texture_;
	}

	SDL_Surface* Text::GetSurface()
	{
		return this->surface_;
	}

	void Text::AddFontFamily(std::string key, std::filesystem::path path)
	{
		Text::FontFamily[key].Path = std::move(path);
	}
}