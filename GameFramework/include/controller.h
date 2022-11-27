#ifndef GAME_FRAMEWORK_CONTROLLER_H_
#define GAME_FRAMEWORK_CONTROLLER_H_

#include <filesystem>

#include <entt/entt.hpp>

namespace GameFrameWork
{
	class Controller
	{
	public:
		Controller();

	public:
		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return this->registry_->emplace<T>(this->entity_, 
				std::forward<Args>(args)...);
		}

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

		template<typename T>
		T& GetComponent()
		{
			return this->registry_->get<T>(this->entity_);
		}

		template<typename T>
		void RemoveComponent()
		{
			this->registry_.remove<T>(this->entity_);
		}

	public:
		operator bool() const { return this->entity_ != entt::null; }
		operator entt::entity() const { return this->entity_; }

	protected:
		std::filesystem::path PathExecutable(std::filesystem::path path);

	private:
		entt::registry* registry_;
		entt::entity entity_;
	};
}

#endif // GAME_FRAMEWORK_CONTROLLER_H_