#pragma once
#include <QtPlugin>

class ISendAudio
{
public:
    ISendAudio() { }
    virtual ~ISendAudio() { }

    virtual void sendAudio() = 0;
};

Q_DECLARE_INTERFACE(ISendAudio, "protocol.functional.ISendAudio")
