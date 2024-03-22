#pragma once
#include <memory>
#include "Component.h"

namespace bgn
{
	class HealthComponent : public Component
	{
	public:
		HealthComponent(const int maxHealth = 1, const int minHealth = 0) : m_health(maxHealth), m_maxHealth(maxHealth), m_minHealth(minHealth){}
		~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void SetHealth(const int value) { m_health = value; }

		void IncrDecrHealth(const int value) { m_health += value; }
		void IncreaseHealth(const unsigned int value = 1) { m_health += value; }
		void DecreaseHealth(const unsigned int value = 1) { m_health -= value; }

		const int GetHealth() const { return m_health; }
		bool HasHealthLeft()
		{
			bool result = (m_health > 0) ? true : false;
			return result;
		}

	private:
		int m_health;
		int m_maxHealth;
		int m_minHealth;
	};
}