#include "dialog.h"
#include <iostream>
#include <QStringList>

Dialog::Dialog(QString applicationDirPath, QObject *parent) : QObject(parent), currentDir(applicationDirPath), switcher(nullptr)
{
}

Dialog::~Dialog()
{
}

void Dialog::startDialog()
{
    std::cout << "Type one of the following commands:\n"
              << "1 - to send text message\n"
              << "2 - to send audio message\n"
              << "3 - to send picture\n"
              << "4 - to call\n"
              << "5 - to videocall\n"
              << "6 - to change current protocol\n"
              << "7 - to view the list of protocols\n"
              << "8 - to view current used protocol\n"
              << "0 - to exit\n";

    int choise = 0;
    std::cin >> choise;

    if (choise < 0 || choise > 8)
    {
        std::cout << "Incorrect command!\nTry Again.\n";
        return;
    }

    if (!choise)
        emit quit();
    else if (choise == 1)
        emit sendText();
    else if (choise == 2)
        emit sendAudio();
    else if (choise == 3)
        emit sendPicture();
    else if (choise == 4)
        emit call();
    else if (choise == 5)
        emit videoCall();
    else if (choise == 6)
    {
        std::cout << "Type the number of protocol: ";
        int number = 0;
        std::cin >> number;
        emit changeProtocol(number);

        QString currentProtocol;
        emit getCurrentProtocol(currentProtocol);
        std::cout << "New protocol is \"" << currentProtocol.toStdString() << "\"\n";
    }
    else if (choise == 7)
    {
        QStringList listOfProtocols;
        emit getProtocolsList(listOfProtocols);

        std::cout << "List of protocols:\n";

        foreach (QString protocolName, listOfProtocols)
        {
            std::cout << protocolName.toStdString() << "\n";
        }
    }
    else
    {
        QString currentProtocol;
        emit getCurrentProtocol(currentProtocol);
        std::cout << "Current protocol is \"" << currentProtocol.toStdString() << "\"\n";
    }
    std::cout << "\n\n";
}

void Dialog::notSupported(QString protocolName)
{
    std::cout << "Current function not supported in " << protocolName.toStdString() << std::endl;
}

void Dialog::setSwitcher()
{
    switcher = new Switcher(this);

    connect(this, SIGNAL(loadPlugins(QString&)), switcher, SLOT(loadPlugins(QString&)));
    connect(this, SIGNAL(changeProtocol(int)), switcher, SLOT(changeProtocol(int)));
    connect(this, SIGNAL(getProtocolsList(QStringList&)), switcher, SLOT(getProtocolsList(QStringList&)));
    connect(this, SIGNAL(getCurrentProtocol(QString&)), switcher, SLOT(getCurrentProtocol(QString&)));

    connect(switcher, SIGNAL(noPlugins()), this, SIGNAL(quit()));
    connect(switcher, SIGNAL(notSupported(QString)), this, SLOT(notSupported(QString)));

    connect(this, SIGNAL(sendText()), switcher, SIGNAL(sendText()));
    connect(this, SIGNAL(sendAudio()), switcher, SIGNAL(sendAudio()));
    connect(this, SIGNAL(sendPicture()), switcher, SIGNAL(sendPicture()));
    connect(this, SIGNAL(call()), switcher, SIGNAL(call()));
    connect(this, SIGNAL(videoCall()), switcher, SIGNAL(videoCall()));

    emit loadPlugins(currentDir);
}

