#pragma once
#include "Observer.h"
#include "LifeObserver.h"
#include <iostream>

namespace bgn
{

	void LifeObserver::OnNotify(Event event)
	{
		m_livesCount = event.arg;

		switch (event.type)
		{
		case(EventType::PlayerDied):
			OnPlayerDied();
			break;
		case(EventType::PlayerRevived):
			OnPlayerRevived();
			break;
		case(EventType::PlayerHealthChanged):
			OnPlayerChangedHealth();
			break;
		default:
			break;
		}
	}

	void   LifeObserver::LifeObserver::OnPlayerDied()
	{	
		std::cout << m_livesCount << std::endl;
	}

	void   LifeObserver::LifeObserver::OnPlayerRevived()
	{
		
		std::cout << m_livesCount << std::endl;
	}

	void   LifeObserver::LifeObserver::OnPlayerChangedHealth()
	{
		
		std::cout << m_livesCount << std::endl;
	}


}