#include "protocol.h"
#include <iostream>

Protocol::Protocol(QObject *plugin, QObject *parent) : QObject(parent)
{
    protocol = plugin;

    textSender = qobject_cast<ISendText *>(protocol);
    friendsGetter = qobject_cast<IGetFriends *>(protocol);
    authenticator = qobject_cast<IAuth *>(protocol);

    if (!authenticator->auth())
        std::cout << "Authentication error!\n";//emit authError();
}

Protocol::~Protocol()
{
    delete protocol;
}

QString Protocol::getProtocolName()
{
    return protocol->objectName();
}

void Protocol::sendText(QString &id, QString &text)
{
    if (textSender)
        textSender->sendText(id, text);
    else
        emit notSupported(protocol->objectName());
}

void Protocol::getFriends(QList<QPair<QString, QString> > &friends)
{
    if (friendsGetter)
        friendsGetter->getFriends(friends);
    else
        emit notSupported(protocol->objectName());
}


