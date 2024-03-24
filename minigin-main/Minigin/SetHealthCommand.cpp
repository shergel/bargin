#include "GameObject.h"
#include "SetHealthCommand.h"
#include "HealthComponent.h"

namespace bgn
{
	void SetHealthCommand::Execute()
	{
		HealthComponent* component = m_targetObj->GetComponent<HealthComponent>();

		if (component == nullptr) return; //todo assert

		component->SetHealth(m_value);
	}

}