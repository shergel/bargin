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
	protected:
		GameObject* m_parent = nullptr;
	};
}
