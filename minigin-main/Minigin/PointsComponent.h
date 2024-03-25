#pragma once
#include <memory>
#include "Component.h"
#include <iostream>

namespace bgn
{
	class PointsComponent : public Component
	{
	public:
		PointsComponent(const int maxPoints = 1000, const int minPoints = 0) : m_points(minPoints), m_maxPoints(maxPoints), m_minPoints(minPoints) {}
		~PointsComponent() = default;
		PointsComponent(const PointsComponent& other) = delete;
		PointsComponent(PointsComponent&& other) = delete;
		PointsComponent& operator=(const PointsComponent& other) = delete;
		PointsComponent& operator=(PointsComponent&& other) = delete;

		void Update([[maybe_unused]] float deltaTime);

		void SetPoints(const int value);
		void IncrDecrPoints(const int value) { SetPoints(m_points + value); }

		const int GetPoints() const { return m_points; }

	private:
		int m_points;
		int m_maxPoints;
		int m_minPoints;
		bool m_flagBuffer = false; //to make sure we don't spam
		float m_counter{};
	};
}