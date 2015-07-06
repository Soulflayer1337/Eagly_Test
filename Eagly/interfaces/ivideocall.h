#pragma once
#include <QtPlugin>

class IVideoCall
{
public:
    IVideoCall() { }
    virtual ~IVideoCall() { }

    virtual void videoCall() = 0;
};

Q_DECLARE_INTERFACE(IVideoCall, "protocol.functional.IVideoCall")
