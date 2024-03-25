#include "HealthComponent.h"

void bgn::HealthComponent::Update(float deltaTime)
{
	if (m_flagBuffer)
	{
		m_counter += deltaTime;
		if (m_counter >= 0.5f)
		{
			m_counter = 0;
			m_flagBuffer = false;
		}
	}
}

void bgn::HealthComponent::SetHealth(const int value)
{
	if (m_flagBuffer) return;
	if (value < m_minHealth - 1 || value > m_maxHealth) return;

	Observer::Event event{};
	event.type = Observer::EventType::PlayerHealthChanged;
	event.arg = value;

	if (!HasHealthLeft() && (value) >= m_minHealth)  //REVIVE
	{
		auto ic = m_parent->GetComponent<ImageComponent>();
		if (ic)
		{
			ic->SetVisible(true);
			std::cout << "revive\n";
			event.type = Observer::EventType::PlayerRevived;
		}

	}
	else if (HasHealthLeft() && (value) < m_minHealth) //KILL
	{
		auto ic = m_parent->GetComponent<ImageComponent>();
		if (ic)
		{
			ic->SetVisible(false);
			std::cout << "kill\n";
			event.type = Observer::EventType::PlayerDied;
		}

		//m_parent->Destroy(); /* to do : eventually uncomment this so obj can actually be destroyed */
	}
	m_parent->Notify(event);
	m_health = value;
	m_flagBuffer = true;
}