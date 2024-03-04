#include "RotationComponent.h"

namespace bgn {
	RotationComponent::RotationComponent(float radius, float speed)
		: 
		  m_radius{ radius }
		, m_speed{ speed }
		, m_angle{ 0 }
	{}

	void RotationComponent::Update(float deltaTime)
	{

		m_angle += (m_speed * deltaTime);
		if (m_angle >= 360.f)
		{
			m_angle -= 360.f;
		}

		float x = m_radius * cosf(m_angle);
		float y = m_radius * sinf(m_angle);

		auto newPos = glm::vec3(m_parent->GetLocalPosition().x + x, m_parent->GetLocalPosition().y + y, 0.f);
		m_parent->SetLocalPosition(newPos);
	}
}