#include "Move2DCommand.h"
#include "GameObject.h"

#include <iostream>

namespace bgn
{
	void Move2DCommand::Execute()
	{
		std::cout << "DEBUG : MOVE OBJECT!\n";
		//actor.Move(m_direction); todo on m_obj
	}
}