#ifndef DEFAULT_MACHINE_H
#define DEFAULT_MACHINE_H

#include "StateMachine.h"
#include <vector>

class DefaultMachine: public StateMachine {
public:
    DefaultMachine();
    ~DefaultMachine();

    void run();

protected:
    void dispatchEvent(const StateEvent &event) override;
    void dispatchEventFromISR(const StateEvent &event) override;

private:
    std::vector<StateEvent> *_events;
};
#endif // DEFAULT_MACHINE_H