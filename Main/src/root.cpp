#include <iostream>
#include <vector>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

// @system include - BEGIN
#include <system.h>
#include <text.h>
#include <physics.h>
#include <typedef.h>
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

	struct PhysicsBoxGround : public Controller
	{
		SDL_Rect Rect = {};

		PhysicsBoxGround(Physics::Core& world) : Controller()
		{
			// Add Physics World
			PhysicsWorld& world_ = this->AddComponent<PhysicsWorld>(world());

			// Position And Size
			auto& position = this->AddComponent<Component::Physics::Position>();
			auto& size = this->AddComponent<Component::Physics::Size>();

			position.X = 400;
			position.Y = 500;
			size.Width = 200;
			size.Height = 40;

			// Make Ground
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(position.X, position.Y);

			b2Body* groundBody = world_->CreateBody(&groundBodyDef);

			b2PolygonShape groundBox;
			groundBox.SetAsBox(size.Width * 0.5f, size.Height * 0.5f);

			groundBody->CreateFixture(&groundBox, 0.0f);

			// Add Body
			this->AddComponent<b2Body*>(groundBody);
		}

		void Update()
		{
			// Get Component
			auto& position = this->GetComponent<Component::Physics::Position>();
			b2Body* body = this->GetComponent<b2Body*>();

			// Update
			const b2Vec2& positionBody = body->GetPosition();
			position.X = positionBody.x;
			position.Y = positionBody.y;
		}

		void Render()
		{
			// Position And Size
			auto& position = this->GetComponent<Component::Physics::Position>();
			auto& size = this->GetComponent<Component::Physics::Size>();

			Rect = std::move(Physics::Core::GetWorldCenter(
				position, size));

			SDL_SetRenderDrawColor(
				System::Renderer, 0x91, 0xC7, 0x88, 0x00);
			SDL_RenderFillRect(System::Renderer, &Rect);
		}
	};

	struct PhysicsBox : public Controller
	{
		SDL_Rect Rect = {};

		PhysicsBox(Physics::Core& world) : Controller()
		{
			// Add Physics World
			PhysicsWorld& world_ = this->AddComponent<PhysicsWorld>(world());
		
			// Add Ground
			this->AddComponent<PhysicsBoxGround>(PhysicsBoxGround(world));

			// Position And Size
			auto& position = this->AddComponent<Component::Physics::Position>();
			auto& size = this->AddComponent<Component::Physics::Size>();

			position.X = 400;
			position.Y = 100;
			size.Width = 40;
			size.Height = 40;

			// Make Body
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(position.X, position.Y);
			b2Body* body = world_->CreateBody(&bodyDef);

			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(
				size.Width * 0.5f, size.Height * 0.5f);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;

			body->CreateFixture(&fixtureDef);

			// Add Body
			this->AddComponent<b2Body*>(body);
		}

		void Update()
		{
			// Get Component
			auto& position = this->GetComponent<Component::Physics::Position>();
			b2Body* body = this->GetComponent<b2Body*>();

			// Update
			const b2Vec2& positionBody = body->GetPosition();
			position.X = positionBody.x;
			position.Y = positionBody.y;

			this->GetComponent<PhysicsBoxGround>().Update();
		}

		void Render()
		{
			// Position And Size
			auto& position = this->GetComponent<Component::Physics::Position>();
			auto& size = this->GetComponent<Component::Physics::Size>();

			Rect = std::move(Physics::Core::GetWorldCenter(
				position, size));

			SDL_SetRenderDrawColor(
				System::Renderer, 0xFE, 0xFF, 0xDE, 0x00);
			SDL_RenderFillRect(System::Renderer, &Rect);

			// Render Ground
			this->GetComponent<PhysicsBoxGround>().Render();
		}
	};

	void Root::Start()
	{
		// Test
		TestC("Hello, World");
		
		// Setting Window
		System::Config.Background = SDL_Color({ 0xF2, 0xF5, 0xC8 });

		// Add Physics Core
		Physics::Core& PhysicsCore = 
			this->AddComponent<Physics::Core>(Physics::Core());

		// Add Bouncing Box and Physics Box
		this->AddComponent<BouncingBox>(BouncingBox());
		this->AddComponent<PhysicsBox>(PhysicsBox(PhysicsCore));

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
		this->GetComponent<Physics::Core>().Update();
		this->GetComponent<PhysicsBox>().Update();
	}

	void Root::Render()
	{
		// Get text
		auto& text = this->GetComponent<HelperText>();

		this->GetComponent<BouncingBox>().Render();
		this->GetComponent<PhysicsBox>().Render();

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