#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include <type_traits>
#include <cassert>
#include "Component.h"
#include "Observer.h"

namespace bgn
{
	class Component;
	class Texture2D;

	class GameObject final
	{
	public:
		virtual void Update(const float deltaTime);
		virtual void FixedUpdate(const float fixedTime);
		virtual void Render() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Destroy() { m_hasFlagDestroy = true; }
		const bool HasFlagDestroy() { return m_hasFlagDestroy; }

		//Location
		const glm::vec3 GetWorldPosition();
		void SetPivotPosition(const float x, const float y);
		void SetPivotPosition(glm::vec3 pos) { SetPivotPosition(pos.x, pos.y); }
		const glm::vec3 GetPivotPosition() { return m_pivotPosition.GetPosition();}
		void SetLocalPosition(const float x, const float y);
		void SetLocalPosition(glm::vec3 pos) { SetLocalPosition(pos.x, pos.y); }
		const glm::vec3 GetLocalPosition() { return m_localPosition.GetPosition();}

		//Components
		template<typename T>
		bool AddComponent(std::unique_ptr<T> comp);

		template<typename T>
		bool RemoveComponent();

		template<typename T>
		bool HasComponent();

		template<typename T>
		T* GetComponent() const;

		//Hierarchy
		void SetParent(GameObject* parent, bool keepWorldPosition = true);
		GameObject* GetParent();
		const int GetChildCount();
		const GameObject* GetChildAt(const int idx);

		void SetIsOrphaned(bool isOrphaned = true) { m_flagOrphaned = isOrphaned; }
		const bool IsOrphaned() { return m_flagOrphaned; }

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(Event event);
	private:
		Transform m_pivotPosition{};
		Transform m_localPosition{};

		//Components
		std::vector <std::unique_ptr<Component>> m_components;

		//Hierarchy
		GameObject* m_parent = nullptr;
		std::vector <GameObject*> m_children{};
		bool m_positionNeedsUpdate{};
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		const bool IsChild(GameObject* potentialChild);

		bool m_flagOrphaned{};
		bool m_positionIsDirty{};
		void SetPositionDirty(bool boolean = true);

		bool m_hasFlagDestroy{false};

		std::vector<Observer*> m_observers;
	};

#pragma region TemplateMethods

	template<typename T>
	inline bool GameObject::AddComponent(std::unique_ptr<T> comp)
	{
		static_assert(std::is_base_of<Component, T>::value, "Invalid as component");

		m_components.push_back(std::move(comp));
		m_components.back()->SetParent(this);

		return true;
	}

	template<typename T>
	inline bool GameObject::RemoveComponent()
	{
		for (auto i = m_components.begin(); i != m_components.end(); ++i)
		{
			if (dynamic_cast<T*>(i->get()))
			{
				m_components.erase(i);
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline bool GameObject::HasComponent()
	{
		for (const auto& comp : m_components)
		{
			if (typeid(*comp) == typeid(T))
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline T* GameObject::GetComponent() const
	{
		for (auto i{ m_components.begin() }; i != m_components.end(); ++i)
		{
			T* comp = dynamic_cast<T*>(i->get());
			if (comp)
			{
				return comp;
			}
		}
		return nullptr;
	}

#pragma endregion

}
