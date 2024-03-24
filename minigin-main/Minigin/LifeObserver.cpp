#pragma once
#include "Observer.h"
#include "LifeObserver.h"
#include <iostream>

namespace bgn
{
    
        void LifeObserver::OnAdd() //must call on add for correct lifecount
        {
            ++m_aliveCount;
            std::cout << "LifeObserver has been added to a GameObject. Total alive: " << m_aliveCount << std::endl;
            
        }

        void LifeObserver::OnNotify(Event event) {
            if (event == Event::PlayerDied) 
            {
                OnPlayerDied();
            }
            else if (event == Event::PlayerRevived) 
            {
                OnPlayerRevived();
            }
        }

        void   LifeObserver::LifeObserver::OnPlayerDied()
        {
            --m_aliveCount;
            ++m_deadCount;
            std::cout << "LifeObserver: Player died. Total dead: " << m_deadCount << std::endl;
        }

        void   LifeObserver::LifeObserver::OnPlayerRevived()
        {
            ++m_aliveCount;
            --m_deadCount;
            std::cout << "LifeObserver: Player revived. Total alive: " << m_aliveCount << std::endl;
        }
    
}