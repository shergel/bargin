#pragma once

#include "Singleton.h"
#include <SDL.h>

#include "Command.h"
#include <memory>
#include <map>

namespace bgn
{

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		
		void BindKey(SDL_Keycode keyCode, std::unique_ptr<Command> command);

	private:
		std::map<SDL_Keycode, std::unique_ptr<Command>> m_keyBinds;
		std::map<Uint8, std::unique_ptr<Command>> m_mouseBinds;

		void HandleKeyboardEvent(const SDL_Event& event);
	};

}