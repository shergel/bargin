#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

void bgn::InputManager::Init()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		m_controllers.push_back(std::make_unique<Controller>(i));
	}
}

void bgn::InputManager::BindKey(SDL_Keycode keyCode, std::unique_ptr<Command> command)
{
	m_keyBinds.push_back(KeyBind{ keyCode, std::move(command) });
}

void bgn::InputManager::BindController(ControllerKey key, std::unique_ptr<Command> command)
{
	m_controllerKeyBinds[key] = std::move(command);
}

void bgn::InputManager::Unbind(SDL_Keycode keyCode)
{
	for (auto it = m_keyBinds.begin(); it != m_keyBinds.end();)
	{
		if (it->key == keyCode)
		{
			it = m_keyBinds.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void bgn::InputManager::Unbind(ControllerKey key)
{
	auto it = m_controllerKeyBinds.find(key);
	if (it != m_controllerKeyBinds.end()) {
		m_controllerKeyBinds.erase(it);
	}
}

bool bgn::InputManager::ProcessInput()
{
	for (const auto& controller : m_controllers) { controller->Update(); }

	ProcessControllerInput();
	
	if (ProcessKeyboardInput() == false) return false;
	HandleKeyboardEvent();
	return true;
		
}

void bgn::InputManager::ProcessControllerInput()
{
	for (const auto& controller : m_controllers)
	{
		/*if (controller->IsStateChanged()) //will use this later
		{*/
		HandleControllerEvent(controller);
		/*}*/
	}
}

bool bgn::InputManager::ProcessKeyboardInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		else if (e.type == SDL_KEYDOWN)
		{

			for (auto& bind : m_keyBinds)
			{
				if (bind.key == e.key.keysym.sym)
				{
					bind.isPressed = true;
				}
			}

		}
		else if (e.type == SDL_KEYUP)
		{

			for (auto& bind : m_keyBinds)
			{
				if (bind.key == e.key.keysym.sym)
				{
					bind.isPressed = false;
				}
			}
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;
}

void bgn::InputManager::HandleKeyboardEvent()
{

	for (const auto& bind : m_keyBinds)
	{
		if (bind.isPressed)
		{
			bind.command->Execute();
		}
	}
}

void bgn::InputManager::HandleControllerEvent(const std::unique_ptr<bgn::Controller>& controller)
{
	for (const auto& bind : m_controllerKeyBinds)
	{
		if (controller->IsPressed(static_cast<WORD>(bind.first)))
		{
			bind.second->Execute();
		}
	}
}