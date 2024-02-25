#pragma once
#include "Singleton.h"

namespace bgn
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
