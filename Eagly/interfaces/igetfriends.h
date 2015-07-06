#pragma once
#include <QtPlugin>

class IGetFriends
{
public:
    IGetFriends() { }
    virtual ~IGetFriends() { }

    virtual void getFriends(QList <QPair<QString, QString>> &friends) = 0;
};

Q_DECLARE_INTERFACE(IGetFriends, "protocol.functional.IGetFriends")
