#pragma once
#include <QtPlugin>

class ISendPicture
{
public:
    ISendPicture() { }
    virtual ~ISendPicture() { }

    virtual void sendPicture() = 0;
};

Q_DECLARE_INTERFACE(ISendPicture, "protocol.functional.ISendPicture")
