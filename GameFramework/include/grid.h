#ifndef GAME_FRAMEWORK_GRID_H_
#define GAME_FRAMEWORK_GRID_H_

// File: Controller/include/grid.h

// Standard Library - BEGIN
#include <vector>
#include <functional>
// Standard Library - END

// Include Header - BEGIN
#include <GameFramework/include/type.h>
// Include Header - END

namespace GameFramework
{
	struct GridData
	{
		Position positionOnInput;
		Position positionOnOutput;
		Data data = nullptr;
	};

	class Grid
	{
	public:
		/**
		 * Intialize grid
		 * @param size - size of one column in grid <Size>
		 * @param offset - offset grid <Position>
		 */
		Grid(Size size, Position offset = Position(0, 0));

		/**
		 * Intialize grid
		 * @param size - size of one column in grid <Size>
		 * @param offset - offset grid <Position>
		 */
		Grid(float width, float height, float offsetX = 0, float offsetY = 0);

	public:
		/**
		 * Intialize grid
		 * @param x - x position
		 * @param y - y position
		 */
		void Add(float x, float y);

	public:
		/* Reload size of columns */
		void Reload();

	public:
		/* Get vector of grid */
		const std::vector<GridData>& Get();

		/**
		 * Get data from vector
		 * @tparam returnType - return type callback function
		 * @param callback - callback function <std::function<Type(GridData&)>>
		 */
		template <typename ReturnType>
		void Get(std::function<ReturnType(GridData&)> callback)
		{
			for (auto& column : this->grid_)
			{
				callback(column);
			}
		}

	private:
		Position offset_;
		Size size_;

		std::vector<GridData> grid_;
	};
}

#endif // GAME_FRAMEWORK_GRID_H_