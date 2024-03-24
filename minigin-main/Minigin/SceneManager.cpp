#include "SceneManager.h"
#include "Scene.h"

void bgn::SceneManager::Update(const float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void bgn::SceneManager::FixedUpdate(const float fixedTime)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTime);
	}
}

void bgn::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

bgn::Scene& bgn::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void bgn::SceneManager::CleanUp()
{
	//todo -> find active scene -> cleanup
	for (auto scene : m_scenes)
	{
		scene->CleanUp();
	}
	//load new file if necessary?
}