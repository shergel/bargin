#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <typeinfo>
#include "ImageComponent.h"
#include "TextComponent.h"

namespace bgn
{

	GameObject::~GameObject()
	{
		m_observers.clear();
	}

	void GameObject::Update(const float deltaTime)
	{
		for (const auto& comp : m_components)
		{
			comp->Update(deltaTime);
		}

		if (m_positionIsDirty)
		{
			SetLocalPosition(m_parent->GetWorldPosition());
			m_positionIsDirty = false;
		}
	}

	void GameObject::FixedUpdate([[maybe_unused]] const float fixedTime)
	{
	}

	void GameObject::Render() const
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

	const glm::vec3 GameObject::GetWorldPosition()
	{
		glm::vec3 result{};

		result = (m_pivotPosition.GetPosition() + m_localPosition.GetPosition());

		return result;
	}

	void GameObject::SetPivotPosition(const float x, const float y)
	{
		m_pivotPosition.SetPosition(x, y, 0.0f);
		SetPositionDirty();
	}

	void GameObject::SetLocalPosition(const float x, const float y)
	{
		m_localPosition.SetPosition(x, y, 0.0f);
		SetPositionDirty();
	}

#pragma region HierarchyMethods
	void GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
	{
		/* VERIFY VALIDITY */
		if (IsChild(parent) || m_parent == parent || parent == this) return;

		/* CHECK FOR FLAG / STOP LOOP */
		if (m_flagOrphaned)
		{
			m_parent = parent;
			return;
		}

		/* ACCOUNT FOR POSITION CHANGE */
		if (parent == nullptr) SetLocalPosition(GetWorldPosition());
		else
		{
			if (keepWorldPosition)
			{
				SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
			}
		}

		/* REMOVE ITSELF FROM OLD PARENT */
		if (m_parent) m_parent->RemoveChild(this);

		/* SET NEW PARENT */
		m_parent = parent;

		/* SET ITSELF AS CHILD TO NEW PARENT */
		if (m_parent) m_parent->AddChild(this);

		/* UPDATE POSITION */
		SetPivotPosition(m_parent->GetWorldPosition());
		SetPositionDirty();
	}
	GameObject* GameObject::GetParent()
	{
		return m_parent;
	}
	const int GameObject::GetChildCount()
	{
		return int(m_children.size());
	}
	const GameObject* GameObject::GetChildAt(const int idx)
	{
		return m_children.at(idx);
	}

	void GameObject::AddChild(GameObject* child)
	{
		/* CHECK VALIDITY */
		if (child == nullptr || child == m_parent) return;

		/* ADOPT CHILD */
		child->SetParent(this);
		child->SetIsOrphaned(false);

		/* ADD CHILDREN TO HOUSEHOLD */
		m_children.push_back(child);
	}
	void GameObject::RemoveChild(GameObject* child)
	{
		/* CHECK VALIDITY*/
		if (child == nullptr || !IsChild(child)) return;

		/* REMOVE CHILD FROM LIST */
		m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());

		/* SET AS ORPHAN */
		child->SetIsOrphaned(true);
		SetParent(nullptr);
	}
	const bool GameObject::IsChild(GameObject* potentialChild)
	{

		for (const GameObject* child : m_children)
		{
			if (child == potentialChild) return true;
		}

		return false;
	}

	void GameObject::SetPositionDirty(bool boolean)
	{
		{ m_positionNeedsUpdate = boolean; }
		for (GameObject* child : m_children)
		{
			child->SetPositionDirty();
		}
	}
#pragma endregion

#pragma region Observers
	void GameObject::AddObserver(Observer* observer) {
		
		m_observers.push_back(observer);
	}

	void GameObject::RemoveObserver(Observer* observer) {
		m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
	}

	void GameObject::Notify(Observer::Event event)
	{ 
		for (Observer* observer : m_observers) {
			observer->OnNotify(event);
		}
	}
#pragma endregion

}