#include <iostream>
#include <vector>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

// @system include - BEGIN
#include <system.h>
#include <text.h>
// @system include - END

#include "../include/root.h"
#include "../include/controller.h"

namespace GameFrameWork
{
	/** Help Render Text */
	struct HelperText
	{
		std::vector<Text> Texts;
		std::vector<SDL_Point> Points;
	};

	struct BouncingBox : public Controller
	{
		int velX_ = 1;
		int velY_ = 1;
		int speed_ = 1;

		SDL_Rect shadow_;
		int offsetShadow_ = 3;

		BouncingBox() : Controller()
		{
			auto& rect = this->AddComponent<SDL_Rect>();
			
			// settings
			rect.x = 1;
			rect.y = 1;
			rect.w = 40;
			rect.h = 40;

			shadow_ = rect;
		}

		/** Logic */
		void Update()
		{
			auto& rect = this->GetComponent<SDL_Rect>();

			if (rect.y + rect.h >= System::Config.Size.Height ||
				rect.y <= 0)
			{
				velY_ *= -1;
			}

			if (rect.x + rect.w >= System::Config.Size.Width ||
				rect.x <= 0)
			{
				velX_ *= -1;
			}

			rect.x += speed_ * velX_;
			rect.y += speed_ * velY_;

			shadow_.x = rect.x + (offsetShadow_ * velX_ * -1);
			shadow_.y = rect.y + (offsetShadow_ * velY_ * -1);
		}

		/** Render box */
		void Render()
		{
			// Shadow
			SDL_SetRenderDrawColor(
				System::Renderer, 0xDD, 0xFF, 0xBC, 0x00);
			SDL_RenderFillRect(System::Renderer, &shadow_);

			// Main Layer
			SDL_SetRenderDrawColor(
				System::Renderer, 0xFE, 0xFF, 0xDE, 0x00);
			SDL_RenderFillRect(
				System::Renderer, 
				&this->GetComponent<SDL_Rect>());
		}
	};

	void Root::Start()
	{
		// Test
		TestC("Hello, World");
		
		// Setting Window
		System::Config.Background = SDL_Color({ 0xF2, 0xF5, 0xC8 });

		// Add Bouncing Box
		this->AddComponent<BouncingBox>(BouncingBox());

		// Add Font Family
		Text::AddFontFamily(
			/*NameFontFamily=*/"OpenSans",
			/*Path=*/this->PathExecutable("OpenSans.ttf"));

		// Add Texts
		auto& text = this->AddComponent<HelperText>();

		// Add Title
		text.Texts.push_back(Text(
			/*FontFamily=*/"OpenSans",
			/*Text=*/"Welcome In GameFrameWork",
			/*Size=*/32,
			/*Color=*/{ 0x52, 0x73, 0x4D }));
		text.Points.push_back({/*x=*/400, /*y=*/270 });

		// Add Main Text
		text.Texts.push_back(Text(
			/*FontFamily=*/"OpenSans",
			/*Text=*/"Edit At File \"Main/src/root.cpp\"",
			/*Size=*/20,
			/*Color=*/{ 0x91, 0xC7, 0x88 }));
		text.Points.push_back({/*x=*/400, /*y=*/300 });
	}

	void Root::Events()
	{

	}

	void Root::Update()
	{
		this->GetComponent<BouncingBox>().Update();
	}

	void Root::Render()
	{
		// Get text
		auto& text = this->GetComponent<HelperText>();

		this->GetComponent<BouncingBox>().Render();

		// Render all texts
		for (size_t idx = 0; idx < text.Texts.size(); idx++)
		{
			auto& point = text.Points[idx];
			text.Texts[idx].Render(point.x, point.y, true);
		}
	}

	void Root::Delete()
	{

	}
}