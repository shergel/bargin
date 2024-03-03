#pragma once

namespace bgn
{
	class GameObject;
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
		void SetParent(GameObject* parent);

		virtual void Update([[maybe_unused]] float deltaTime){};
	protected:
		GameObject* m_parent = nullptr;
	};
}
