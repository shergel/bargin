#pragma once
#include "Observer.h"
#include "LifeObserver.h"
#include <iostream>

#include "SceneManager.h"
#include "GameObject.h"
#include "TextComponent.h"
namespace bgn
{
	void LifeObserver::OnNotify(Event event)
	{
		m_hasMessage = true;
		m_livesCount = event.arg;
		std::cout << "Lives : " << m_livesCount;

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

	void  LifeObserver::OnPlayerDied()
	{
		std::cout << "player died" << std::endl;
	}
	void   LifeObserver::OnPlayerRevived()
	{
		std::cout << "player revived" << std::endl;
	}
	void   LifeObserver::OnPlayerChangedHealth()
	{
		std::cout << "player health changed" << std::endl;
	}

	const std::string LifeObserver::GetMessage()
	{
		const std::string message = "Lives : " + std::to_string(m_livesCount);
		m_hasMessage = false;
		return message;
	}
}