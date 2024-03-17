#include "Controller.h"
#include <SDL_syswm.h>
#include "InputManager.h"
#include "XInput.h"

namespace bgn
{
	class Controller::Impl
	{
	public:
		Impl(unsigned int id = 0) : m_id{ id } {}

		void Update()
		{
			CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
			const DWORD dwResult = XInputGetState(m_id, &m_currentState);

			if (dwResult == ERROR_DEVICE_NOT_CONNECTED)
			{
				m_isConnected = false;
				return;
			}
			m_isConnected = true;

			const auto buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
			buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
			buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);
		}

		glm::vec2 GetThumbL2D() const
		{
			const float threshold = m_deadzone * m_MAX_THUMBS_RANGE;

			const float x = std::abs(m_currentState.Gamepad.sThumbLX) < threshold ? 0.0f : m_currentState.Gamepad.sThumbLX / m_MAX_THUMBS_RANGE;
			const float y = std::abs(m_currentState.Gamepad.sThumbLY) < threshold ? 0.0f : m_currentState.Gamepad.sThumbLY / m_MAX_THUMBS_RANGE;

			return glm::vec2{ x, -y };
		}
		glm::vec2 GetThumbR2D() const
		{
			const float threshold = m_deadzone * m_MAX_THUMBS_RANGE;
			const float x = std::abs(m_currentState.Gamepad.sThumbRX) < threshold ? 0.0f : m_currentState.Gamepad.sThumbRX / m_MAX_THUMBS_RANGE;
			const float y = std::abs(m_currentState.Gamepad.sThumbRY) < threshold ? 0.0f : m_currentState.Gamepad.sThumbRY / m_MAX_THUMBS_RANGE;

			return glm::vec2{ x,-y };
		}
		glm::vec2 GetDPad2D() const
		{
			glm::vec2 direction{};

			//LEFT - RIGHT
			if (IsPressed(static_cast<unsigned int>(XINPUT_GAMEPAD_DPAD_LEFT))) direction.x = -1.f;
			else if (IsPressed(static_cast<unsigned int>(XINPUT_GAMEPAD_DPAD_RIGHT))) direction.x = 1.0f;

			//UP - DOWN
			if (IsPressed(static_cast<unsigned int>(XINPUT_GAMEPAD_DPAD_UP))) direction.y = -1.0f;
			else if (IsPressed(static_cast<unsigned int>(XINPUT_GAMEPAD_DPAD_DOWN))) direction.y = 1.f;

			return direction;
		}

		bool IsDown(unsigned int button) const { return buttonsPressedThisFrame & button; }
		bool IsPressed(unsigned int button) const { return m_currentState.Gamepad.wButtons & button; }
		bool IsUp(unsigned int button) const { return buttonsReleasedThisFrame & button; }
		bool IsStateChanged() const { return m_currentState.dwPacketNumber != m_previousState.dwPacketNumber; }

		void SetDeadzone(float deadzone)
		{
			if (deadzone < 0.f)
			{
				m_deadzone = 0.f;
				return;
			}

			if (deadzone > 1.f)
			{
				m_deadzone = 1.f;
				return;
			}

			m_deadzone = deadzone;
		}

	private:
		XINPUT_STATE m_previousState{};
		XINPUT_STATE m_currentState{};

		const float m_MAX_THUMBS_RANGE = 32767.0f;

		bool m_isConnected{ false };
		unsigned int buttonsPressedThisFrame{};
		unsigned int buttonsReleasedThisFrame{};

		float m_deadzone{ 0.5f };
		unsigned int m_id{};
	};


	Controller::Controller(unsigned int id) : m_pimpl{ std::make_unique<Impl>(id) } {}
	Controller::~Controller() = default;

	void Controller::SetDeadzone(const float deadzone) { m_pimpl->SetDeadzone(deadzone); }
	void Controller::Update() { m_pimpl->Update(); }
	bool Controller::IsPressed(unsigned button) const { return m_pimpl->IsPressed(button); }
	bool Controller::IsDown(unsigned button) const { return m_pimpl->IsDown(button); }
	bool Controller::IsUp(unsigned button) const { return m_pimpl->IsUp(button); }
	bool Controller::IsStateChanged() const { return m_pimpl->IsStateChanged(); }
	glm::vec2 Controller::GetDPad2D() const { return m_pimpl->GetDPad2D(); }
	glm::vec2 Controller::GetThumbL2D() const { return m_pimpl->GetThumbL2D(); }
	glm::vec2 Controller::GetThumbR2D() const { return m_pimpl->GetThumbR2D(); }
}