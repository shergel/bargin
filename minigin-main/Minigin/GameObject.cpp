#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <typeinfo>
#include "ImageComponent.h"
#include "TextComponent.h"

bgn::GameObject::~GameObject() = default;

void bgn::GameObject::Update([[maybe_unused]] const float deltaTime)
{
	for (const auto& comp : m_components)
	{
		comp->Update(deltaTime);
	}
}

void bgn::GameObject::FixedUpdate([[maybe_unused]] const float fixedTime)
{
}

void bgn::GameObject::Render() const
{
	//todo change if is imagecomp / if is textcomp to if is renderablecomp
	for (const auto& comp : m_components)
	{
		if (auto imageComp = dynamic_cast<const bgn::ImageComponent*>(comp.get()))
		{
			imageComp->Render();
		}
		else if (auto textComp = dynamic_cast<const bgn::TextComponent*>(comp.get()))
		{
			textComp->Render();
		}
	}
}

void bgn::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
