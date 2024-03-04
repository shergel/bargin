#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Component.h"

namespace bgn
{
	class RotationComponent final : public Component
	{
	public:
		void Update(float deltaTime) override;

		RotationComponent(float radius = 2.5f, float speed = 7.f);
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;
	private:
		float m_angle;
		float m_radius;
		float m_speed;
	};
}