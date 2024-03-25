#pragma once
#include "Observer.h"
#include <iostream>

namespace bgn
{

    class LifeObserver : public Observer
    {
    public:
        LifeObserver() : m_livesCount(0){}

        //void OnAdd(); //must call on add for correct lifecount
        virtual void OnNotify(Event event);

    private:
        int m_livesCount;

        void OnPlayerDied();
        void OnPlayerRevived();
        void OnPlayerChangedHealth();
        const std::string m_messagePrefix = "# lives : ";
    };

}