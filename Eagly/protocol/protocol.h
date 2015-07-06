#pragma once

#include <QObject>
#include <QString>

#include "../interfaces/isendtext.h"
#include "../interfaces/iauth.h"
#include "../interfaces/igetfriends.h"

class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *plugin, QObject *parent = 0);
    ~Protocol();

    QString getProtocolName();

signals:
    void notSupported(QString protocolName);

public slots:
    void sendText(QString &id, QString &text);
    void getFriends(QList<QPair<QString, QString> > &friends);

private:
    QObject *protocol;

    ISendText *textSender;
    IGetFriends *friendsGetter;
    IAuth *authenticator;

    void auth();
};
