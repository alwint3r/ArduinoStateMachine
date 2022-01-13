#ifndef DEFAULT_MACHINE_H
#define DEFAULT_MACHINE_H

#include "StateMachine.h"
#include <vector>

template <typename T, class C>
class DefaultMachine : public StateMachine<T, C>
{
public:
    DefaultMachine()
    {
        _events = new std::vector<StateEvent<T, C>>();
    }

    ~DefaultMachine()
    {
        delete _events;
        _events = nullptr;
    }

    void run()
    {
        if (_events->size() > 0)
        {
            StateEvent<T, C> event = _events->at(0);

            this->processEvent(&event);

            _events->erase(_events->begin());
        }
    }

protected:
    void dispatchEvent(const StateEvent<T, C> &event) override
    {
        _events->push_back(event);
    }

    void dispatchEventFromISR(const StateEvent<T, C> &event) override
    {
        _events->push_back(event);
    }

private:
    std::vector<StateEvent<T, C>> *_events;
};
#endif // DEFAULT_MACHINE_H