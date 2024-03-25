
#include "GameObject.h"
#include "AddSubtractPointsCommand.h"
#include "PointsComponent.h"

namespace bgn
{
	void AddSubtractPointsCommand::Execute()
	{
		PointsComponent* component = m_targetObj->GetComponent<PointsComponent>();

		if (component == nullptr) return; //todo assert

		component->IncrDecrPoints(m_value);
	}

}