#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace bgn
{
	class Transform : public Component
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_position{0,0,0};
	};
}
