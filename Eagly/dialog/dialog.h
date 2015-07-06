#pragma once

#include <QObject>
#include "../switcher/switcher.h"

class Dialog : public QObject
{
    Q_OBJECT
public:
    explicit Dialog(QString applicationDirPath, QObject *parent = 0);
    ~Dialog();

signals:
    void quit();
    void changeProtocol(int index);

    void sendText();
    void sendAudio();
    void sendPicture();
    void call();
    void videoCall();

    void getCurrentProtocol(QString &);
    void getProtocolsList(QStringList &);
    void loadPlugins(QString &);
public slots:
    void setSwitcher();
    void startDialog();
    void notSupported(QString protocolName);

private:
    QString currentDir;
    Switcher *switcher;
};
