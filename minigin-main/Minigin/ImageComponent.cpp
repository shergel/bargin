#include "ImageComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"

namespace bgn
{

	void bgn::ImageComponent::Render() const
	{
		glm::vec3 pos{};

		if (m_parent != nullptr) 
		{
			pos = m_parent->GetPosition();
		}

		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}

	void bgn::ImageComponent::SetTexture(const std::string& filename)
	{
		m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

}