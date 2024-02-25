#pragma once

namespace bgn
{
	class GameObject;
	class Component
	{
	public:
		Component() = default;
		~Component() = default;
	protected :
		GameObject* m_parent = nullptr;
	private:
		void SetParent(GameObject* parent);
	};
}
