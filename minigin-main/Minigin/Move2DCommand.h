#pragma once
#include "Command.h"
#include <glm/vec2.hpp>
#include "GameObject.h"

namespace bgn
{
	class Move2DCommand : public Command
	{
	public:
		Move2DCommand(std::shared_ptr<GameObject> targetObj, glm::vec2 direction, float speed = 1.f)
			: m_targetObj(targetObj), m_direction(direction), m_speed(speed)
		{}

		virtual ~Move2DCommand() override = default;
		void Execute() override;
		void SetDirection(const glm::vec2& value);
		void SetSpeed(const float speed) { m_speed = speed; }

	private:
		glm::vec2 m_direction;
		float m_speed;
		std::shared_ptr<GameObject> m_targetObj;
	};
}