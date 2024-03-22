#include "MovementComponent.h"
#include "GameObject.h"

void bgn::MovementComponent::Move(glm::vec2 direction)
{
	glm::vec3 current = m_parent->GetPivotPosition();
	m_parent->SetPivotPosition(current.x + direction.x, current.y + direction.y);
}