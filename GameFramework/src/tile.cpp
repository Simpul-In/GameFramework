#include <mutex>
#include <filesystem>
#include <fstream>

// @third party code - BEGIN NLOHMANN/JSON
#include <nlohmann/json.hpp>
// @third party code - END NLOHMANN/JSON

// @third party code - BEGIN SDL2
#include <SDL.h>
// @third party code - END SDL2

#include "../include/tile.h"
#include "../include/system.h"

namespace GameFrameWork
{
	namespace Tile
	{
		namespace Map
		{
			Rect::Rect(
				GameFrameWork::Map::Texture& mapTexture,
				GameFrameWork::Texture& texture,
				std::filesystem::path path)
				: map_(&mapTexture), texture_(&texture),
				  Width(0), Height(0)
			{
				std::ifstream inFile;
				inFile.open(path);

				if (inFile.is_open())
				{
					nlohmann::json json;
					inFile >> json;

					this->Width = static_cast<size_t>(json["Width"].get<int>());
					this->Height = static_cast<size_t>(json["Height"].get<int>());

					for (auto data1 : json["Tile"].items())
					{
						std::mutex mutex;
						auto data = data1.value().items();
;						size_t idx = this->Create();

						oneapi::tbb::parallel_for_each(data.begin(), data.end(),
							[&, this](auto& data_) -> void
							{
								std::lock_guard<std::mutex> lock(mutex);
								size_t ID = static_cast<size_t>(data_.value()["ID"].get<int>());
								size_t x = static_cast<size_t>(data_.value()["x"].get<int>());
								size_t y = static_cast<size_t>(data_.value()["y"].get<int>());

								this->Push(idx, ID, x, y);
							});
					}
				}

				inFile.close();
			}

			size_t Rect::Create()
			{
				this->Tiles.push_back(std::vector<TileMap>());
				return this->Tiles.size() - 1;
			}

			void Rect::Push(size_t layer, size_t ID, size_t x, size_t y)
			{
				TileMap tile;

				tile.Position_.x = static_cast<int>(x);
				tile.Position_.y = static_cast<int>(y);
				tile.Source = &this->map_->Map[ID];
				tile.ID = ID;

				tile.Destination.x = static_cast<int>(this->Width) * static_cast<int>(x);
				tile.Destination.y = static_cast<int>(this->Height) * static_cast<int>(y);
				tile.Destination.w = static_cast<int>(this->Width);
				tile.Destination.h = static_cast<int>(this->Height);

				this->Tiles[layer].push_back(tile);
			}

			void Rect::Render()
			{
				GameFrameWork::Texture* dTexture = this->texture_;

				for (auto& layer : this->Tiles)
				{
					oneapi::tbb::parallel_for_each(
						layer.begin(), layer.end(),
						[&, this](TileMap& block) -> void
						{
							SDL_RenderCopy(
								System::Renderer,
								dTexture->GetTexture(),
								block.Source,
								&block.Destination
							);
						});
				}
			}

			void Rect::MakeIntoFile(std::filesystem::path path)
			{
				std::mutex mutex;

				nlohmann::json main;
				nlohmann::json json;

				for (size_t x = 0; x < this->Tiles.size(); x++)
				{
					oneapi::tbb::parallel_for(
						oneapi::tbb::blocked_range<size_t>(0, this->Tiles[x].size()),
						[&](const oneapi::tbb::blocked_range<size_t>& yR) -> void
						{
							std::lock_guard<std::mutex> lock(mutex);
							for (size_t y = yR.begin(); y != yR.end(); ++y)
							{
								json[x][y]["x"] = this->Tiles[x][y].Position_.x;
								json[x][y]["y"] = this->Tiles[x][y].Position_.y;
								json[x][y]["ID"] = this->Tiles[x][y].ID;
							}
						});
				}

				main["Tile"] = json;
				main["Width"] = this->Width;
				main["Height"] = this->Height;

				std::ofstream file;
				file.open(path, std::ios::trunc);

				file << main.dump();
				file.close();
			}
		}
	}
}