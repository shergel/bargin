#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

bgn::GameObject::~GameObject() = default;

void bgn::GameObject::Update(){}

void bgn::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void bgn::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void bgn::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
