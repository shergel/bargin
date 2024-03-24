#pragma once
#include "Observer.h"

namespace bgn
{

    class LifeObserver : public Observer
    {
    public:
        LifeObserver() : m_aliveCount(0), m_deadCount(0) {}

        void OnAdd(); //must call on add for correct lifecount
        virtual void OnNotify(Event event);

    private:
        int m_aliveCount;
        int m_deadCount;


        void OnPlayerDied();
        void OnPlayerRevived();
    };

}