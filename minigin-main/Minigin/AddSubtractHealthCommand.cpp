#include "GameObject.h"
#include "AddSubtractHealthCommand.h"
#include "HealthComponent.h"

namespace bgn
{
	void AddSubtractHealthCommand::Execute()
	{
		HealthComponent* component = m_targetObj->GetComponent<HealthComponent>();

		if (component == nullptr) return; //todo assert

		component->IncrDecrHealth(m_value);
	}

}