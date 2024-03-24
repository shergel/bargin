#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace bgn
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(const float deltaTime);
		void FixedUpdate(const float fixedTime);
		void Render();
		void CleanUp();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}
