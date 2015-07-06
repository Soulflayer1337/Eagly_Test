#pragma once
#include <QtPlugin>

class IAuth
{
public:
    IAuth() { }
    virtual ~IAuth() { }

    virtual bool auth() = 0;
};

Q_DECLARE_INTERFACE(IAuth, "protocol.functional.IAuth")
