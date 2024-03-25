#pragma once
#include "Command.h"

namespace bgn
{
	class AddSubtractPointsCommand : public Command
	{
	public:
		AddSubtractPointsCommand(std::shared_ptr<GameObject> targetObj, const int adjustmentValue)
			: m_targetObj(targetObj), m_value(adjustmentValue) {}

		void Execute() override;

		void SetValue(const int adjustmentValue) { m_value = adjustmentValue; }
		const int GetValue() const { return m_value; }

	private:
		std::shared_ptr<GameObject> m_targetObj;
		int m_value{};
	};
}
