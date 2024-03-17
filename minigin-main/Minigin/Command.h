#pragma once
#include "GameObject.h"

namespace bgn
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute() = 0;
		
	private :
	};
}