#pragma once
namespace bgn
{

     class Observer {
    public:

        enum class EventType
        {
            PlayerHealthChanged,
            PlayerDied,
            PlayerRevived
        };

        struct Event
        {
            EventType type = EventType::PlayerHealthChanged;
            int arg = 0;
        };

        virtual ~Observer() {}
        //virtual void OnAdd() = 0;
        virtual void OnNotify(Event event) = 0;
    };
}