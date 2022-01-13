#include "StateClass.h"

StateClass::StateClass(std::string name) : _name(name)
{
}

StateClass::~StateClass()
{
}

std::string StateClass::process(StateEvent *event)
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