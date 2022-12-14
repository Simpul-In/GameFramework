#ifndef GAME_FRAMEWORK_CONTROLLER_H_
#define GAME_FRAMEWORK_CONTROLLER_H_

#include <filesystem>

// @third party code - BEGIN ENTT
#include <entt/entt.hpp>
// @third party code - END ENTT

namespace GameFrameWork
{
	class Controller
	{
	public:
		Controller();

	public:
		/**
		 * Add Component
		 * @tparam Component - Component will add
		 * @tparam Args - paramaeters
		 */
		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return this->registry_->emplace<T>(this->entity_, 
				std::forward<Args>(args)...);
		}

		/**
		 * Check the component is exist
		 * @tparam Component - Component will check
		 * @return (True <Exist>) or (False <Not Exist>)
		 */
		template <typename T>
		bool Has()
		{
			for (auto& entity : this->registry_->view<T>())
			{
				if (entity_ == entity)
				{
					return true;
				}
			}
			return false;
		}

		/**
		 * Get Component
		 * @tparam Component - Component will get
		 */
		template<typename T>
		T& GetComponent()
		{
			return this->registry_->get<T>(this->entity_);
		}

		/**
		 * Remove Component
		 * @tparam Component - Component will remove
		 */
		template<typename T>
		void RemoveComponent()
		{
			this->registry_.remove<T>(this->entity_);
		}

	public:
		/**
		 * Check entity is not null
		 * @return (True) or (False)
		 */
		operator bool() const { return this->entity_ != entt::null; }

		/**
		 * Get entity
		 * @return Entity
		 */
		operator entt::entity() const { return this->entity_; }

	protected:
		/**
		 * Join Target Path With Path Executable
		 * @param path - Target Path will join with Path Executable
		 * @return path had joined
		 */
		std::filesystem::path PathExecutable(std::filesystem::path path);

	private:
		entt::registry* registry_;
		entt::entity entity_;
	};
}

#endif // GAME_FRAMEWORK_CONTROLLER_H_