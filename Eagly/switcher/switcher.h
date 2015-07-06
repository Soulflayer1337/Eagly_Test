#pragma once

#include <QObject>
#include <QList>
#include <QStringList>
#include "../protocol/protocol.h"

class Switcher : public QObject
{
    Q_OBJECT
public:
    explicit Switcher(QObject *parent = 0);
    ~Switcher();

signals:
    void noPlugins();
    void notSupported(QString protocolName);

    void sendText(QString &, QString &);
    void getFriends(QList<QPair<QString, QString> > &);

public slots:
    void getProtocolsList(QStringList &listOfProtocols);
    void getCurrentProtocol(QString &currentProtocol);
    void changeProtocol(int newIndex);
    void loadPlugins(QString &currentDir);

private:
    void connectWith();
    void disconnectWith();

    int currentProtocolIndex;
    QList<Protocol *> protocols;
};
