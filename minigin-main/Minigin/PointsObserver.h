#pragma once
#include "Observer.h"
#include <iostream>
#include <string>

namespace bgn
{

    class PointsObserver : public Observer
    {
    public:
		PointsObserver() : m_points(200) {}

        virtual void OnNotify(Event event);
        const std::string GetMessage()
        { 
            if (!m_hasMessage) { return "no new message"; }
            std::string result = m_messagePrefix + std::to_string(m_points);
            m_hasMessage = false;
            return result;
        }
        bool HasMessage() { return m_hasMessage; }

    private:
        bool m_hasMessage = false;
        int m_points;

        void OnPointsAdded();
        void OnPointsRemoved();
        const std::string m_messagePrefix = "Score : ";
    };

}