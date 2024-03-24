#pragma once
namespace bgn
{
    enum class Event {
        PlayerDied,
        PlayerRevived
    };

    class Observer {
    public:
        virtual ~Observer() {}
        virtual void OnAdd() = 0;
        virtual void OnNotify(Event event) = 0;
    };
}