#pragma once

#include <QObject>
#include "../switcher/switcher.h"
#include <QPair>

class Dialog : public QObject
{
    Q_OBJECT
public:
    explicit Dialog(QString applicationDirPath, QObject *parent = 0);
    ~Dialog();

signals:
    void quit();
    void changeProtocol(int index);

    void sendText(QString &, QString &);
    void getFriends(QList<QPair<QString, QString> > &);
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
