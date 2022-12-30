#include <utility>
#include <filesystem>

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

// @third party code - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party code - END OneAPI

// @system include - BEGIN
#include "../../include/system.h"
#include "../../include/text.h"
#include "../../include/storage.h"
// @system include - END

#include "../../include/experiment/word.h"

namespace GameFrameWork
{
	Word::Word(std::string fontFamily,
		std::filesystem::path path,
		SDL_Color color,
		size_t size)
		: fontFamily_(std::move(fontFamily)), color_(std::move(color)),
		size_(std::move(size))
	{
		// Add Font Family
		Text::AddFontFamily(this->fontFamily_, std::move(path));
	}

	Component::Default::Size Word::Draw(
		std::string text, SDL_FPoint point,
		size_t spacingText, size_t space)
	{
		Component::Default::Size size = { 0, 0 };
		Component::Default::Size size_ = { 0, 0 };
		size_t heightOfText = 0;

		// Check and get height of text
		for (size_t i = 0; i < text.size(); i++)
		{
			if (text[i] != '\n' && text[i] != ' ')
			{
				if (this->characters.find(text[i]) != this->characters.end())
				{
					if (this->characters[text[i]]->GetSurface()->h > 0)
					{
						heightOfText = static_cast<size_t>(
							this->characters[text[i]]->GetSurface()->h);
					}
				}
				else
				{
					std::string texting = "";
					texting += text[i];

					this->characters[text[i]] = new Text(
						this->fontFamily_, texting, this->size_, this->color_);
					if (this->characters[text[i]]->GetSurface()->h > 0)
					{
						heightOfText = static_cast<size_t>(
							this->characters[text[i]]->GetSurface()->h);
					}

					Storage::AddTrash(this->characters[text[i]]);
				}
			}
		}

		for (size_t i = 0; i < text.size(); i++)
		{
			if (text[i] == '\n')
			{
				size.Height += heightOfText;
				size.Width = 0;
			}
			else if (text[i] == ' ')
			{
				size.Width += space;
			}
			else if (text[i] == '\t')
			{
				for (uint8_t i = 0; i < 4; i++) size.Width += space;
			}
			else
			{
				this->characters[text[i]]->Render(
					static_cast<int>(point.x) + static_cast<int>(size.Width),
					static_cast<int>(point.y) + static_cast<int>(size.Height));

				size.Width += static_cast<size_t>(
					this->characters[text[i]]->GetSurface()->w) + spacingText;
			}

			if (size.Width > size_.Width)
			{
				size_.Width = size.Width;
			}
		}

		size_.Height = size.Height + heightOfText;
		return std::move(size_);
	}
}