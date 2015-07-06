#pragma once
#include <QtPlugin>

class ICall
{
public:
    ICall() { }
    virtual ~ICall() { }

    virtual void call() = 0;
};

Q_DECLARE_INTERFACE(ICall, "protocol.functional.ICall")
