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
	m_keyBinds[keyCode] = std::move(command);
}

void bgn::InputManager::BindController(ControllerKey key, std::unique_ptr<Command> command)
{
	m_controllerKeyBinds[key] = std::move(command);
}

void bgn::InputManager::Unbind(SDL_Keycode keyCode)
{
	auto it = m_keyBinds.find(keyCode);
	if (it != m_keyBinds.end()) {
		m_keyBinds.erase(it);
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
			HandleKeyboardEvent(e);
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;
}

void bgn::InputManager::HandleKeyboardEvent(const SDL_Event& event)
{
	SDL_Keycode keyCode = event.key.keysym.sym;

	if (m_keyBinds.find(keyCode) != m_keyBinds.end()) {
		m_keyBinds[keyCode]->Execute();
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