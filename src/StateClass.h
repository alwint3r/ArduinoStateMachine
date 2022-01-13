#ifndef STATECLASS_H
#define STATECLASS_H

#include "StateTypedefs.h"
#include <string>

template<typename T, class C>
class StateClass
{
public:
    using StateFunction = std::function<void()>;
    using StateEventFunction = std::function<std::string(StateEvent<T, C> *)>;

    StateClass(std::string name): _name(name)
    {
    }

    ~StateClass()
    {
    }

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

    std::string process(StateEvent<T, C> *event)
    {
        std::string result;

        if (_child != NULL)
        {
            result = _child->process(event);
        }
        else if (_onEvent != nullptr)
        {
            result = _onEvent(event);
        }
        else if (_parent != NULL)
        {
            result = _parent->process(event);
        }
        else
        {
            result = "";
        }

        return result;
    }

protected:
    std::string _name;
    StateClass *_parent = nullptr;
    StateClass *_child = nullptr;

    StateFunction _onExit = nullptr;
    StateFunction _onEnter = nullptr;
    StateEventFunction _onEvent = nullptr;
};

#endif // STATECLASS_H