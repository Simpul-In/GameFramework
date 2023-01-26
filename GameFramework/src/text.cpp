// File: GameFramework/src/text.cpp

// Standard Library - BEGIN
#include <utility>
#include <iostream>
// Standard Library - END

// @third party code - BEGIN SDL2
#include <SDL_ttf.h>
// @third party code - END SDL2

// @third party - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party - END OneAPI

// Include Header - BEGIN
#include <GameFramework/include/text.h>
#include <GameFramework/include/font.h>
// Include Header - END

namespace GameFramework
{
	Text::Text(App* app, SDL_Color colorFont_, std::string fontFamily_,
		std::string text_, float sizeFont_)
		: app_(app), colorFont(std::move(colorFont_)), fontFamily(std::move(fontFamily_)),
		text(std::move(text_)), sizeFont(std::move(sizeFont_))
	{
		this->Make();
	}

	void Text::Make()
	{
		// Reset average
		this->storeCharacter_.clear();
		
		this->sizeText.width = 0;
		this->sizeText.height = 0;

		this->averageOfEachText_[0] = 0;
		this->averageOfEachText_[1] = 0;

		// Length
		float length = 0;

		// Get character
		for (auto& character : this->text)
		{
			// If not enter and space
			if (!(character == '\n' || character == ' '))
			{
				// Check if character doesn't exist
				if (!(this->storeCharacter_.find(character) != this->storeCharacter_.end()))
				{
					// Add font
					this->storeCharacter_[character] = Font::AddCharacter(this->app_, 
						this->fontFamily, character, static_cast<size_t>(this->sizeFont), 
						this->colorFont);

					// Increment
					length += 1;

					// Sum into store
					this->averageOfEachText_[0] += this->storeCharacter_
						[character]->sizeOfCharacter.width;
					this->averageOfEachText_[1] += this->storeCharacter_
						[character]->sizeOfCharacter.height;
				}
			}
		}

		// average character
		this->averageOfEachText_[0] /= length;
		this->averageOfEachText_[1] /= length;

		// Get size text
		float lengthHorizontal = 0;

		for (size_t i = 0; i < this->text.size(); i++)
		{
			if (this->text[i] == '\n')
			{
				lengthHorizontal = 0;
				this->sizeText.height += this->averageOfEachText_[1];
			}
			else
			{
				lengthHorizontal += this->averageOfEachText_[0];
			}

			if (lengthHorizontal > this->sizeText.width)
			{
				this->sizeText.width = lengthHorizontal;
			}
		}

		this->sizeText.width -= this->averageOfEachText_[0];
		this->sizeText.height += this->averageOfEachText_[1];
	}

	void Text::Render(float x, float y, bool center)
	{
		if (center)
		{
			x -= (this->sizeText.width / 2.0f);
			y -= (this->sizeText.height / 2.0f);
		}

		this->rectCharacter_.x = x;
		this->rectCharacter_.y = y;

		for (auto& character : this->text)
		{
			// Enter
			if (character == '\n')
			{
				this->rectCharacter_.y += static_cast<int>(
					this->averageOfEachText_[1]);
				this->rectCharacter_.x = x;
			}

			// Space
			else if (character == ' ')
			{
				this->rectCharacter_.x += static_cast<int>(
					this->averageOfEachText_[0]);
			}

			// Tab
			else if (character == '\t')
			{
				for (int i = 0; i < 3; i++)
				{
					this->rectCharacter_.x += static_cast<int>(
						this->averageOfEachText_[0]);
				}
			}

			// Character
			else
			{
				// Check if character doesn't exist
				if (!(this->storeCharacter_.find(character) != this->storeCharacter_.end()))
				{
					// Add font
					this->storeCharacter_[character] = Font::AddCharacter(this->app_,
						this->fontFamily, character, static_cast<size_t>(this->sizeFont),
						this->colorFont);
				}

				// Render
				auto& size = this->storeCharacter_[character]->sizeOfCharacter;
				this->rectCharacter_.w = size.width;
				this->rectCharacter_.h = size.height;

				SDL_RenderCopyF(this->app_->renderer,
					this->storeCharacter_[character]->texture, NULL,
					&this->rectCharacter_);

				this->rectCharacter_.x += static_cast<int>(size.width);
			}
		}
	}
}