#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include <type_traits>
#include <cassert>
#include "Component.h"

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

		void SetPosition(float x, float y);
		glm::vec3 GetPosition(){ return m_transform.GetPosition(); }

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename T>
		bool AddComponent(std::unique_ptr<T> comp);

		template<typename T>
		bool RemoveComponent();

		template<typename T>
		bool HasComponent();

		template<typename T>
		T* GetComponent() const;

	private:
		Transform m_transform{};

		std::vector <std::unique_ptr<Component>> m_components;
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
