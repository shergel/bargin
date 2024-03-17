#pragma once
/*

///////////////////// END HEADER


#include "Controller.h"
#include <SDL_syswm.h>
#include "InputManager.h"

class Controller::Impl
{
public:
    Impl(unsigned int id) : m_id{ id } {}

    void setDeadZone(float deadzone)
    {
        if (deadzone < 0.f)
        {
            m_deadZone = 0.f;
            return;
        }

        if (deadzone > 1.f)
        {
            m_deadZone = 1.f;
            return;
        }

        m_deadZone = deadzone;
    }

    void update()
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

        const auto buttonChanges = m_currentState.Controller.wButtons ^ m_previousState.Controller.wButtons;
        buttonsPressedThisFrame = buttonChanges & m_currentState.Controller.wButtons;
        buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Controller.wButtons);
    }

    bool isDown(unsigned int button) const
    {
        return buttonsPressedThisFrame & button;
    }
    bool isPressed(unsigned int button) const
    {
        return m_currentState.Controller.wButtons & button;
    }
    bool isUp(unsigned int button) const
    {
        return buttonsReleasedThisFrame & button;
    }
    bool isStateChanged() const
    {
        return m_currentState.dwPacketNumber != m_previousState.dwPacketNumber;
    }

    glm::vec2 getThumbL2D() const
    {
        const float deadzoneThreshold = m_deadZone * 32767;

        const float x = std::abs(m_currentState.Controller.sThumbLX) < deadzoneThreshold ? 0.0f : m_currentState.Controller.sThumbLX / 32767.0f;
        const float y = std::abs(m_currentState.Controller.sThumbLY) < deadzoneThreshold ? 0.0f : m_currentState.Controller.sThumbLY / 32767.0f;

        return glm::vec2{ x, -1.f * y };
    }
    glm::vec2 getThumbR2D() const
    {
        const float deadzoneThreshold = m_deadZone * 32767;

        const float x = std::abs(m_currentState.Controller.sThumbRX) < deadzoneThreshold ? 0.0f : m_currentState.Controller.sThumbRX / 32767.0f;
        const float y = std::abs(m_currentState.Controller.sThumbRY) < deadzoneThreshold ? 0.0f : m_currentState.Controller.sThumbRY / 32767.0f;

        return glm::vec2{ x,-1.f * y };
    }
    glm::vec2 getDPad2D() const
    {
        glm::vec2 axis{};
        if (isPressed(static_cast<unsigned int>(GamepadKey::DPad_Left))) axis.x = -1.f;
        else if (isPressed(static_cast<unsigned int>(GamepadKey::DPad_Right))) axis.x = 1.0f;

        if (isPressed(static_cast<unsigned int>(GamepadKey::DPad_Down))) axis.y = 1.f;
        else if (isPressed(static_cast<unsigned int>(GamepadKey::DPad_Up))) axis.y = -1.0f;

        return axis;
    }

private:
    unsigned int m_id{};
    XINPUT_STATE m_previousState{};
    XINPUT_STATE m_currentState{};
    bool m_isConnected{ false };
    unsigned int buttonsPressedThisFrame{};
    unsigned int buttonsReleasedThisFrame{};
    float m_deadZone{ 0.5f };
};


Controller::Controller(unsigned int id) : m_pimpl{ std::make_unique<Impl>(id) } {}
Controller::~Controller() = default;


void Controller::setDeadZone(float deadzone)
{
    m_pimpl->setDeadZone(deadzone);
}

void Controller::update()
{
    m_pimpl->update();
}

bool Controller::isDown(unsigned button) const
{
    return m_pimpl->isDown(button);
}

bool Controller::isPressed(unsigned button) const
{
    return m_pimpl->isPressed(button);
}

bool Controller::isUp(unsigned button) const
{
    return m_pimpl->isUp(button);
}

bool Controller::isStateChanged() const
{
    return m_pimpl->isStateChanged();
}

glm::vec2 Controller::getThumbL2D() const
{
    return m_pimpl->getThumbL2D();
}

glm::vec2 Controller::getThumbR2D() const
{
    return m_pimpl->getThumbR2D();
}

glm::vec2 Controller::getDPad2D() const
{
    return m_pimpl->getDPad2D();
}

*/