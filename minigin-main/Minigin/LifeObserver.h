#pragma once
#include "Observer.h"
#include <iostream>
#include <string>

namespace bgn
{

    class LifeObserver : public Observer
    {
    public:
        LifeObserver(){}

        virtual void OnNotify(Event event);
        std::string GetMessage()
        {
            if (!m_hasMessage) { return "no new message"; }
            std::string result = m_messagePrefix + std::to_string(m_livesCount);
            m_hasMessage = false;
            return result;
        }
        bool HasMessage() { return m_hasMessage; }

    private:
        bool m_hasMessage = false;
        int m_livesCount;

        void OnPlayerDied();
        void OnPlayerRevived();
        void OnPlayerChangedHealth();
        const std::string m_messagePrefix = "# lives : ";
    };

}