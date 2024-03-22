#include "GameObject.h"
#include "AdjustHealthCommand.h"
#include "HealthComponent.h"

namespace bgn
{
	void AdjustHealthCommand::Execute()
	{
		HealthComponent* component = m_targetObj->GetComponent<HealthComponent>();

		if (component == nullptr) return; //todo assert

		component->IncrDecrHealth(m_value);
	}

}