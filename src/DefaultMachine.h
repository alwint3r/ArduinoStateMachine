#ifndef DEFAULT_MACHINE_H
#define DEFAULT_MACHINE_H

#include "StateMachine.h"
#include "StateEvent.h"
#include <vector>

class DefaultMachine: public StateMachine {
public:
    DefaultMachine();
    virtual ~DefaultMachine();

    virtual void event(const StateEvent &event);
    virtual void eventFromISR(const StateEvent &event);

    virtual void run();
private:
    std::vector<StateEvent> *_events;
};
#endif // DEFAULT_MACHINE_H