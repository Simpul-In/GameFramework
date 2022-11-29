#include <iostream>

#include <SDL.h>

#include <system.h>
#include <texture.h>
#include <animation.h>
#include <sound.h>
#include <text.h>

#include <box2d/box2d.h>

#include "../include/root.h"

namespace GameFrameWork
{
	struct Transform
	{
		struct
		{
			float Width;
			float Height;
		} Size;
		struct
		{
			float x;
			float y;
		} Position;

		SDL_Rect operator()()
		{
			SDL_Rect rect;
			rect.x = static_cast<int>(this->Position.x);
			rect.y = static_cast<int>(this->Position.y);
			rect.w = static_cast<int>(this->Size.Width);
			rect.h = static_cast<int>(this->Size.Height);

			return rect;
		}
	};

	void Root::Start()
	{
		TestC("Hello, World");

		Sound::Wav sound = Sound::Wav(
			this->PathExecutable("re-stretched.wav"), 128, true);
		sound.Play();

		Text::AddFontFamily("Inter", this->PathExecutable("OpenSans.ttf"));
		this->AddComponent<Text>(Text(
			"Inter", "Hello, World", 40, { 255, 255, 0, 0 }));

		auto& texture = this->AddComponent<Texture>(
			Texture(this->PathExecutable("test.png")));
		auto& transform = this->AddComponent<Transform>();
		auto& animation = this->AddComponent<Animation::Map>();

		int nAnimation = 8;
		animation.Create("default");
		animation.KeyFrame = "default";

		auto& texSize = texture.GetComponent<Component::Default::Size>();
		transform.Size.Width = static_cast<float>(texSize.Width / nAnimation);
		transform.Size.Height = static_cast<float>(texSize.Height);
		transform.Position.x = 0;
		transform.Position.y = 0;

		for (size_t i = 0; i != static_cast<size_t>(nAnimation); i++)
		{
			SDL_Rect textureID;

			// Size
			textureID.w = static_cast<int>(transform.Size.Width);
			textureID.h = static_cast<int>(transform.Size.Height);

			// Position
			textureID.x = static_cast<int>(
				i * static_cast<size_t>(transform.Size.Width));
			textureID.y = 0;

			animation.Push("default", std::move(textureID));
		}
	}

	void Root::Events()
	{

	}

	void Root::Update()
	{
		auto& animation = this->GetComponent<Animation::Map>();
		animation.Update();
	}

	void Root::Render()
	{
		auto& texture = this->GetComponent<Texture>();
		auto& transform = this->GetComponent<Transform>();
		auto& animation = this->GetComponent<Animation::Map>();

		this->GetComponent<Text>().Render(400, 300 ,true);

		SDL_Rect rect = transform();
		SDL_RenderCopy(
			System::Renderer, texture.GetTexture(),
			&animation(), &rect);
	}

	void Root::Delete()
	{

	}
}