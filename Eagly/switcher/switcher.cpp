#include "switcher.h"
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

        if (plugin)
            protocols << new Protocol(plugin, this);
    }

    if (protocols.isEmpty())
        emit noPlugins();
    else
        connectWith();
}

void Switcher::connectWith()
{
    connect(this, SIGNAL(sendText()), protocols[currentProtocolIndex], SLOT(sendText()));
    connect(this, SIGNAL(sendAudio()), protocols[currentProtocolIndex], SLOT(sendAudio()));
    connect(this, SIGNAL(sendPicture()), protocols[currentProtocolIndex], SLOT(sendPicture()));
    connect(this, SIGNAL(call()), protocols[currentProtocolIndex], SLOT(call()));
    connect(this, SIGNAL(videoCall()), protocols[currentProtocolIndex], SLOT(videoCall()));

    connect(protocols[currentProtocolIndex], SIGNAL(notSupported(QString)), this, SIGNAL(notSupported(QString)));
}

void Switcher::disconnectWith()
{

    disconnect(this, SIGNAL(sendText()), protocols[currentProtocolIndex], SLOT(sendText()));
    disconnect(this, SIGNAL(sendAudio()), protocols[currentProtocolIndex], SLOT(sendAudio()));
    disconnect(this, SIGNAL(sendPicture()), protocols[currentProtocolIndex], SLOT(sendPicture()));
    disconnect(this, SIGNAL(call()), protocols[currentProtocolIndex], SLOT(call()));
    disconnect(this, SIGNAL(videoCall()), protocols[currentProtocolIndex], SLOT(videoCall()));

    disconnect(protocols[currentProtocolIndex], SIGNAL(notSupported(QString)), this, SIGNAL(notSupported(QString)));
}
