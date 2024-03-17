#include <SDL.h>
#include "InputManager.h"
#include "imgui_impl_sdl2.h"

void bgn::InputManager::BindKey(SDL_Keycode keyCode, std::unique_ptr<Command> command)
{
	m_keyBinds[keyCode] = std::move(command);
}


bool bgn::InputManager::ProcessInput()
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
		else if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
		}
		else 
		{
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