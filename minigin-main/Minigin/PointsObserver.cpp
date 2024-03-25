#pragma once
#include "Observer.h"
#include "PointsObserver.h"
#include <iostream>

namespace bgn
{

	void PointsObserver::OnNotify(Event event)
	{
		m_points = event.arg;

		switch (event.type)
		{
		case(EventType::PointsAdded):
			OnPointsAdded();
			break;
		case(EventType::PointsRemoved):
			OnPointsRemoved();
			break;
		default:
			break;
		}

		m_hasMessage = true;
	}

	void   PointsObserver::OnPointsAdded()
	{
		std::cout << m_messagePrefix << m_points << std::endl;
	}

	void   PointsObserver::OnPointsRemoved()
	{

		std::cout << m_messagePrefix << m_points << std::endl;
	}
}