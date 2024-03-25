#pragma once
#include "Observer.h"
#include <iostream>

namespace bgn
{

    class PointsObserver : public Observer
    {
    public:
		PointsObserver() : m_points(200) {}

        
        virtual void OnNotify(Event event);

    private:
        int m_points;
        void OnPointsAdded();
        void OnPointsRemoved();
        const std::string m_messagePrefix = "# points : ";
    };

}