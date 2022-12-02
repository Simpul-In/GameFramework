#include <utility>
#include <mutex>
#include <filesystem>
#include <fstream>

// @third party code - BEGIN NLOHMANN/JSON
#include <nlohmann/json.hpp>
// @third party code - END NLOHMANN/JSON

// @third party code - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party code - END OneAPI

#include "../include/map.h"

namespace GameFrameWork
{
	namespace Map
	{
		Texture::Texture(std::filesystem::path path)
		{
			std::mutex mutex;
			std::ifstream inFile;
			inFile.open(path);

			if (inFile.is_open())
			{
				nlohmann::json json;
				inFile >> json;

				auto data = json["Data"].items();
				oneapi::tbb::parallel_for_each(data.begin(), data.end(),
					[&, this](auto& data) -> void
					{
						std::lock_guard<std::mutex> lock(mutex);
						auto& dJson = data.value();

						TextureMapID info;
						info.ID = static_cast<size_t>(dJson["ID"].get<int>());
						info.Rect.x = dJson["Rect"]["x"].get<int>();
						info.Rect.y = dJson["Rect"]["y"].get<int>();
						info.Rect.w = dJson["Rect"]["w"].get<int>();
						info.Rect.h = dJson["Rect"]["h"].get<int>();

						this->Push(info);
					});
			}

			inFile.close();
		}

		void Texture::Push(TextureMapID map)
		{
			this->MapSource.push_back(map);
			this->Map[map.ID] = map.Rect;
		}

		void Texture::Push(std::vector<TextureMapID> map)
		{
			std::mutex mutex;
			oneapi::tbb::parallel_for(
				oneapi::tbb::blocked_range<size_t>(0, map.size()),
				[&, this](const oneapi::tbb::blocked_range<size_t>& r) -> void {
					std::lock_guard<std::mutex> lock(mutex);

					for (size_t i = r.begin(); i != r.end(); ++i)
					{
						this->Push(map[i]);
					}
				});
		}

		void Texture::MakeIntoFile(std::filesystem::path path)
		{
			std::mutex mutex;
			nlohmann::json main;
			nlohmann::json json;

			oneapi::tbb::parallel_for(
				oneapi::tbb::blocked_range<size_t>(0, this->MapSource.size()),
				[&](const oneapi::tbb::blocked_range<size_t>& r) -> void
				{
					std::lock_guard<std::mutex> lock(mutex);
					for (size_t i = r.begin(); i != r.end(); ++i)
					{
						json[i]["ID"] = this->MapSource[i].ID;
						json[i]["Rect"]["x"] = this->MapSource[i].Rect.x;
						json[i]["Rect"]["y"] = this->MapSource[i].Rect.y;
						json[i]["Rect"]["w"] = this->MapSource[i].Rect.w;
						json[i]["Rect"]["h"] = this->MapSource[i].Rect.h;
					}
				});

			main["Data"] = json;

			std::ofstream file;
			file.open(path, std::ios::trunc);

			file << main.dump();
			file.close();
		}

		TextureMapID Texture::Make(SDL_Rect rect)
		{
			TextureMapID info;
			info.Rect = std::move(rect);
			info.ID = this->Map.size();

			return info;
		}

		std::vector<SDL_Rect> Texture::Select(std::vector<size_t> IDS)
		{
			std::vector<SDL_Rect> result;

			// Can't using parallel cause this should specific
			for (auto& id : IDS)
			{
				result.push_back(this->Map[id]);
			}
			
			return result;
		}
	}
}