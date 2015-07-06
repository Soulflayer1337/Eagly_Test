#pragma once

#include <QObject>
#include <QString>

#include "../interfaces/isendaudio.h"
#include "../interfaces/isendpicture.h"
#include "../interfaces/isendtext.h"
#include "../interfaces/icall.h"
#include "../interfaces/ivideocall.h"

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
    void sendAudio();
    void sendPicture();
    void sendText();
    void call();
    void videoCall();
private:
    QObject *protocol;

    ISendAudio *audioSender;
    ISendPicture *pictureSender;
    ISendText *textSender;
    ICall *caller;
    IVideoCall *videoCaller;
};
