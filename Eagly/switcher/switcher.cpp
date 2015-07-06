#include "switcher.h"
#include "interfaces/iauth.h"
#include <QDir>
#include <QPluginLoader>
#include <iostream>

Switcher::Switcher(QObject *parent) : QObject(parent), currentProtocolIndex(0)
{
}

Switcher::~Switcher()
{
}

void Switcher::getProtocolsList(QStringList &listOfProtocols)
{
    foreach (Protocol *protocol, protocols)
    {
        listOfProtocols << protocol->getProtocolName();
    }
}

void Switcher::getCurrentProtocol(QString &currentProtocol)
{
    currentProtocol = protocols[currentProtocolIndex]->getProtocolName();
}

void Switcher::changeProtocol(int newIndex)
{
    if (protocols.size() <= newIndex || newIndex < 0 || newIndex == currentProtocolIndex)
        return;

    disconnectWith();
    currentProtocolIndex = newIndex;
    connectWith();
}

void Switcher::loadPlugins(QString &currentDir)
{
    QDir dir(currentDir);

    if (dir.cd("Plugins") == false)
    {
        emit noPlugins();
        return;
    }

    foreach (QString fileName, dir.entryList(QDir::Files))
    {
        QPluginLoader loader(dir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();

        if (qobject_cast<IAuth *> plugin)
            protocols << new Protocol(plugin, this);
    }

    if (protocols.isEmpty())
        emit noPlugins();
    else
        connectWith();
}

void Switcher::connectWith()
{
    connect(this, SIGNAL(sendText(QString&,QString&)), protocols[currentProtocolIndex], SLOT(sendText(QString&, QString&)));
    connect(this, SIGNAL(getFriends(QList<QPair<QString,QString> >&)), protocols[currentProtocolIndex], SLOT(getFriends(QList<QPair<QString,QString> >&)));

    connect(protocols[currentProtocolIndex], SIGNAL(notSupported(QString)), this, SIGNAL(notSupported(QString)));
}

void Switcher::disconnectWith()
{
    disconnect(this, SIGNAL(sendText(QString&,QString&)), protocols[currentProtocolIndex], SLOT(sendText(QString&, QString&)));
    disconnect(this, SIGNAL(getFriends(QList<QPair<QString,QString> >&)), protocols[currentProtocolIndex], SLOT(getFriends(QList<QPair<QString,QString> >&)));

    disconnect(protocols[currentProtocolIndex], SIGNAL(notSupported(QString)), this, SIGNAL(notSupported(QString)));
}
