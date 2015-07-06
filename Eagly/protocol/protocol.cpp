#include "protocol.h"

Protocol::Protocol(QObject *plugin, QObject *parent) : QObject(parent)
{
    protocol = plugin;

    audioSender = qobject_cast<ISendAudio *>(protocol);
    pictureSender = qobject_cast<ISendPicture *>(protocol);
    textSender = qobject_cast<ISendText *>(protocol);
    caller = qobject_cast<ICall *>(protocol);
    videoCaller = qobject_cast<IVideoCall *>(protocol);
}

Protocol::~Protocol()
{
    delete protocol;
}

QString Protocol::getProtocolName()
{
    return protocol->objectName();
}

void Protocol::sendAudio()
{
    if (audioSender)
        audioSender->sendAudio();
    else
        emit notSupported(protocol->objectName());
}

void Protocol::sendPicture()
{
    if (pictureSender)
        pictureSender->sendPicture();
    else
        emit notSupported(protocol->objectName());
}

void Protocol::sendText()
{
    if (textSender)
        textSender->sendText();
    else
        emit notSupported(protocol->objectName());
}

void Protocol::call()
{
    if (caller)
        caller->call();
    else
        emit notSupported(protocol->objectName());
}

void Protocol::videoCall()
{
    if (videoCaller)
        videoCaller->videoCall();
    else
        emit notSupported(protocol->objectName());
}

