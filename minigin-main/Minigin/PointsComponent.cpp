#include "PointsComponent.h"
#include "Observer.h"
#include "GameObject.h"

void bgn::PointsComponent::Update(float deltaTime)
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

void bgn::PointsComponent::SetPoints(const int value)
{
	if (m_flagBuffer) return;
	if (value < m_minPoints - 1 || value > m_maxPoints) return;

	Observer::Event event{};
	event.arg = value;

	if (value >= m_points)  //ADD
	{
		event.type = Observer::EventType::PointsAdded;
	}
	else if (value < m_points) //REMOVE
	{
		event.type = Observer::EventType::PointsRemoved;
	}

	m_parent->Notify(event);
	m_points = value;
	m_flagBuffer = true;
}