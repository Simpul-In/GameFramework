#include <utility>
#include <string>
#include <mutex>
#include <fstream>
#include <filesystem>
#include <future>

#include <nlohmann/json.hpp>

#include "../include/animation.h"

namespace GameFrameWork
{
	namespace Animation
	{
		Map::Map(std::filesystem::path path)
		{
			std::mutex mutex;
			std::ifstream inFile;
			inFile.open(path);

			if (inFile.is_open())
			{
				nlohmann::json json;
				inFile >> json;

				auto data = json["Animation"].items();
				oneapi::tbb::parallel_for_each(data.begin(), data.end(),
					[&, this](auto& data) -> void
					{
						std::lock_guard<std::mutex> lock(mutex);
						this->Create(data.key());

						for (auto& frame : data.value().items())
						{
							auto& rect = frame.value();
							SDL_Rect rect_;
							rect_.x = rect["x"].get<int>();
							rect_.y = rect["y"].get<int>();
							rect_.w = rect["w"].get<int>();
							rect_.h = rect["h"].get<int>();

							this->Push(data.key(), rect_);
						}
					});
			}

			inFile.close();
		}

		void Map::Create(std::string key)
		{
			MapID map;
			map.ID = std::move(key);
			this->Animation[map.ID] = map.Frames;
		}

		void Map::Push(std::string key, SDL_Rect frame)
		{
			this->Animation[key].push_back(frame);
		}

		void Map::Push(std::string key, std::vector<SDL_Rect> frames)
		{
			// Can't using parallel cause should be specific
			for (auto& frame : frames)
			{
				this->Push(key, frame);
			}
		}

		SDL_Rect& Map::operator()()
		{
			return this->Animation[this->KeyFrame][this->Frame];
		}

		void Map::MakeIntoFile(std::filesystem::path path)
		{
			std::mutex mutex;
			std::vector<std::future<void>> worker;

			nlohmann::json main;
			nlohmann::json json;

			for (const auto& [key, value] : this->Animation)
			{
				worker.push_back(std::async(
					std::launch::async,
					[&]() -> void
					{
						std::lock_guard<std::mutex> lock(mutex);
						for (size_t idx = 0; idx < value.size(); idx++)
						{
							json[key][idx]["x"] = value[idx].x;
							json[key][idx]["y"] = value[idx].y;
							json[key][idx]["w"] = value[idx].w;
							json[key][idx]["h"] = value[idx].h;
						}
					}));
			}

			for (auto& function : worker)
			{
				function.wait();
			}

			main["Animation"] = json;

			std::ofstream file;
			file.open(path, std::ios::trunc);

			file << main.dump();
			file.close();
		}

		void Map::Update()
		{
			if (this->keyFrameNow_ != this->KeyFrame)
			{
				this->keyFrameNow_ = this->KeyFrame;
				this->Frame = 0;
			}

			if (SDL_GetTicks() - this->ticks_ > this->DelayAnimation)
			{
				this->ticks_ = SDL_GetTicks();
				this->Frame += 1;
			}

			if (this->Frame >= this->Animation[this->KeyFrame].size())
			{
				if (this->Repeat)
				{
					this->Frame = 0;
				}

				else {
					this->Frame = this->Animation[this->KeyFrame].size() - 1;
				}
			}
		}

		void Textures::Create(std::string key)
		{
			this->Animation[key] = std::vector<Texture>();
		}

		void Textures::Push(std::string key, Texture frame)
		{
			this->Animation[key].push_back(std::move(frame));
		}

		void Textures::Push(std::string key, std::vector<Texture> frames)
		{
			// Can't using parallel cause should be specific
			for (auto& frame : frames)
			{
				this->Push(key, frame);
			}
		}

		void Textures::Update()
		{
			if (this->keyFrameNow_ != this->KeyFrame)
			{
				this->keyFrameNow_ = this->KeyFrame;
				this->Frame = 0;
			}

			if (SDL_GetTicks() - this->ticks_ > this->DelayAnimation)
			{
				this->ticks_ = SDL_GetTicks();
				this->Frame += 1;
			}

			if (this->Frame >= this->Animation[this->KeyFrame].size())
			{
				if (this->Repeat)
				{
					this->Frame = 0;
				}

				else {
					this->Frame = this->Animation[this->KeyFrame].size() - 1;
				}
			}
		}
	}
}