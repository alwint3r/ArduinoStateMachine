#ifndef STATECLASS_H
#define STATECLASS_H

#include "StateTypedefs.h"
#include <string>

class StateClass
{
public:
    StateClass(std::string name);
    ~StateClass();

    void setName(std::string name)
    {
        _name = name;
    }

    std::string getName()
    {
        return _name;
    }

    void setParent(StateClass *parent)
    {
        _parent = parent;
    }

    void setChild(StateClass *child)
    {
        _child = child;
    }

    void onEnter(StateFunction func)
    {
        _onEnter = func;
    }

    void onExit(StateFunction func)
    {
        _onExit = func;
    }

    void onEvent(StateEventFunction func)
    {
        _onEvent = func;
    }

    void enter()
    {
        if (_onEnter)
        {
            _onEnter();
        }
    }

    void exit()
    {
        if (_onExit)
        {
            _onExit();
        }
    }

    StateProcessResult process(StateEvent *event);

protected:
    std::string _name;
    StateClass *_parent = nullptr;
    StateClass *_child = nullptr;

    StateFunction _onExit = nullptr;
    StateFunction _onEnter = nullptr;
    StateEventFunction _onEvent = nullptr;
};

#endif // STATECLASS_H