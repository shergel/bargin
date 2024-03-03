#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <typeinfo>
#include "ImageComponent.h"

bgn::GameObject::~GameObject() = default;

void bgn::GameObject::Update([[maybe_unused]] const float deltaTime)
{
}

void bgn::GameObject::FixedUpdate([[maybe_unused]] const float fixedTime)
{
}

void bgn::GameObject::Render() const
{
    for (const auto& comp : m_components)
    {
        if (auto imageComp = dynamic_cast<const bgn::ImageComponent*>(comp.get()))
        {
            imageComp->Render();
        }
    }
}

void bgn::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
