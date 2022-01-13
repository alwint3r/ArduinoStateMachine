#ifndef DEFAULT_MACHINE_H
#define DEFAULT_MACHINE_H

#include "StateMachine.h"
#include "StateEvent.h"
#include <vector>

class DefaultMachine: public StateMachine {
public:
    DefaultMachine();
    ~DefaultMachine();

    void event(const StateEvent &event) override;
    void eventFromISR(const StateEvent &event) override;

    void run();
private:
    std::vector<StateEvent> *_events;
};
#endif // DEFAULT_MACHINE_H