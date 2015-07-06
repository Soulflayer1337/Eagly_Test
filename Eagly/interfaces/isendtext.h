#pragma once
#include <QtPlugin>

class ISendText
{
public:
    ISendText() { }
    virtual ~ISendText() { }

    virtual void sendText() = 0;
};

Q_DECLARE_INTERFACE(ISendText, "protocol.functional.ISendText")
