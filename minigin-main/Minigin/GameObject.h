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

	// todo: this should become final.
	class GameObject
	{
	public:
		virtual void Update(const float deltaTime);
		virtual void FixedUpdate(const float fixedTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

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
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};

#pragma region TemplateMethods

	template<typename T>
	bool GameObject::AddComponent(std::unique_ptr<T> comp)
	{
		static_assert(std::is_base_of<Component, T>::value, "Invalid as component");
		//if (this->HasComponent<T>()) { static_assert(false, "Duplicate component not allowed"); } //todo : what if I need 0 text components?

		m_components.push_back(comp);
		m_components.back()->SetParent(this);

		return true;
	}

	template<typename T>
	bool GameObject::RemoveComponent()
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
	bool GameObject::HasComponent()
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
	T* GameObject::GetComponent() const
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
