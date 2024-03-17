#pragma once

#include "Singleton.h"
#include <SDL.h>

#include "Command.h"
#include <memory>
#include <map>

#include <Windows.h>
#include <Xinput.h>
#include "Controller.h"

namespace bgn
{

	class InputManager final : public Singleton<InputManager>
	{

	public:
		
		enum class ControllerKey
		{
			Start = XINPUT_GAMEPAD_START,
			Back = XINPUT_GAMEPAD_BACK,

			DPad_Left = XINPUT_GAMEPAD_DPAD_LEFT,
			DPad_Right = XINPUT_GAMEPAD_DPAD_RIGHT,
			DPad_Up = XINPUT_GAMEPAD_DPAD_UP,
			DPad_Down = XINPUT_GAMEPAD_DPAD_DOWN,

			LShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
			LThumb = XINPUT_GAMEPAD_LEFT_THUMB,

			RShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
			RThumb = XINPUT_GAMEPAD_RIGHT_THUMB,

			A = XINPUT_GAMEPAD_A,
			B = XINPUT_GAMEPAD_B,
			X = XINPUT_GAMEPAD_X,
			Y = XINPUT_GAMEPAD_Y,
		};

		void Init();
		bool ProcessInput();

		void BindKey(SDL_Keycode keyCode, std::unique_ptr<Command> command);
		void BindController(ControllerKey key, std::unique_ptr<Command> command);
		void Unbind(Command* command);

	private:
		std::map<SDL_Keycode, std::unique_ptr<Command>> m_keyBinds;
		std::map<ControllerKey, std::unique_ptr<Command>> m_controllerKeyBinds;

		void ProcessControllerInput();
		bool ProcessKeyboardInput();
		void HandleKeyboardEvent(const SDL_Event& event);

		void HandleControllerEvent(const std::unique_ptr<bgn::Controller>& controller);

		std::vector<std::unique_ptr<Controller>> m_controllers; 

	};

}