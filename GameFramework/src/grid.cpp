// File: Controller/src/grid.h

// Standard Library - BEGIN
#include <vector>
#include <mutex>
// Standard Library - END

// @third party - BEGIN OneAPI
#include <oneapi/tbb.h>
// @third party - END OneAPI

// Include Header - BEGIN
#include <GameFramework/include/grid.h>
// Include Header - END

namespace GameFramework
{
	Grid::Grid(Size size, Position offset)
		: size_(std::move(size)), offset_(std::move(offset)) {}

	Grid::Grid(float width, float height, float offsetX, float offsetY)
	{
		this->offset_ = Position(offsetX, offsetY);
		this->size_ = Size(width, height);
	}

	void Grid::Add(float x, float y)
	{
		GridData data;
		data.positionOnInput = Position(x, y);
		data.positionOnOutput = Position(
			(x * this->size_.width) + this->offset_.x, 
			(y * this->size_.height) + this->offset_.y
		);

		this->grid_.push_back(std::move(data));
	}

	void Grid::Reload()
	{
		std::mutex mutex;

		oneapi::tbb::parallel_for(
			oneapi::tbb::blocked_range<size_t>(0, this->grid_.size()),
			[&, this](const oneapi::tbb::blocked_range<size_t>& r) -> void {
				std::lock_guard <std::mutex> lock(mutex);

				for (size_t i = r.begin(); i != r.end(); ++i)
				{
					Position& position = grid_[i].positionOnInput;
					grid_[i].positionOnOutput.x = (position.x * size_.width) + offset_.x;
					grid_[i].positionOnOutput.y = (position.y * size_.height) + offset_.y;
				}
			});
	}

	const std::vector<GridData>& Grid::Get()
	{
		return this->grid_;
	}
}