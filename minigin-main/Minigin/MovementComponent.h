#pragma once
#include <memory>
#include "Component.h"
#include "Transform.h"

namespace bgn
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent() = default;
		~MovementComponent() = default;
		void Move(glm::vec2 direction);
	private:
	};
}