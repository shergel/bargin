#pragma once
#include <memory>
#include "Component.h"
#include "GameObject.h"
#include "ImageComponent.h"
#include <iostream>

namespace bgn
{
	class HealthComponent : public Component
	{
	public:
		HealthComponent(const int maxHealth = 1, const int minHealth = 1) : m_health(maxHealth), m_maxHealth(maxHealth), m_minHealth(minHealth) {}
		~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void SetHealth(const int value) 
		{ 
			if(!HasHealthLeft() && (value) >= m_minHealth)  //REVIVE
			{ 
				auto ic = m_parent->GetComponent<ImageComponent>();
				if (ic)
				{
					ic->SetVisible(true);
					std::cout << "revive\n";
					m_parent->Notify(Event::PlayerRevived);
				}
				
			}
			else if (HasHealthLeft() && (value) < m_minHealth) //KILL
			{ 
				auto ic = m_parent->GetComponent<ImageComponent>();
				if(ic)
				{
					ic->SetVisible(false);
					std::cout << "kill\n";
					m_parent->Notify(Event::PlayerDied);
				}
				
				//m_parent->Destroy(); /* to do : eventually uncomment this so obj can actually be destroyed */
			}
			m_health = value; 
		}

		void IncrDecrHealth(const int value) { SetHealth(m_health + value); }
		void IncreaseHealth(const unsigned int value = 1) { SetHealth(m_health + value); }
		void DecreaseHealth(const unsigned int value = 1) { SetHealth(m_health - value); }

		const int GetHealth() const { return m_health; }
		bool HasHealthLeft()
		{
			bool result = (m_health >= m_minHealth) ? true : false;
			return result;
		}

	private:
		int m_health;
		int m_maxHealth;
		int m_minHealth;
	};
}