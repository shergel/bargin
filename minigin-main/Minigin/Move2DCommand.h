#pragma once
#include "Command.h"
#include <glm/vec2.hpp>
#include "GameObject.h"

namespace bgn
{
	class Move2DCommand : public Command
	{
	public:
		Move2DCommand(std::shared_ptr<GameObject> actor, glm::vec2 direction)
			: m_actor(actor), m_direction(direction)
		{}

		virtual ~Move2DCommand() override = default;
		virtual void Execute() override;
		virtual void SetDirection(const glm::vec2& value) { m_direction = value; }

	private:
		glm::vec2 m_direction;
		std::shared_ptr<GameObject> m_actor;
	};
}