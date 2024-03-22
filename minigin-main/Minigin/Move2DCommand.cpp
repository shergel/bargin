#include "Move2DCommand.h"
#include "GameObject.h"
#include "MovementComponent.h"

#include <iostream>

namespace bgn
{
	void Move2DCommand::Execute()
	{
		MovementComponent* component = m_targetObj->GetComponent<MovementComponent>();

		if (component == nullptr) return;//todo assert

		component->Move({ m_direction.x * m_speed, m_direction.y * m_speed });
	}

	void Move2DCommand::SetDirection(const glm::vec2& value)
	{
		//To make sure the result is either -1, 0 or 1 for all.
		const int xSign = (value.x >= 0) ? 1 : -1;
		const int ySign = (value.y >= 0) ? 1 : -1;

		const int xAbs = (value.x == 0) ? 0 : 1;
		const int yAbs = (value.y == 0) ? 0 : 1;

		m_direction = { xSign * xAbs, ySign * yAbs };
	}
}