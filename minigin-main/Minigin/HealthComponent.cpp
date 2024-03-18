#pragma once
#include <memory>
#include "Component.h"

namespace bgn
{
	class HealthComponent : public Component
	{
	public:
		HealthComponent(const int maxHealth = 1) : m_health(maxHealth) {}
		~HealthComponent() = default;
		
		const int GetHealth() const { return m_health; }
		void SetHealth(const int value) { m_health = value; }
		void IncreaseHealth(const int value = 1) { m_health += value; }
		void DecreaseHealth(const int value = 1) { m_health -= value; }
	private:
		int m_health;
	};
}