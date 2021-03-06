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
              << "2 - to get friend list\n"
              << "3 - to change current protocol\n"
              << "4 - to view the list of protocols\n"
              << "5 - to view current used protocol\n"
              << "0 - to exit\n";

    int choise = 0;
    std::cin >> choise;

    if (choise < 0 || choise > 5)
    {
        std::cout << "Incorrect command!\nTry Again.\n";
        return;
    }

    if (!choise)
        emit quit();
    else if (choise == 1)
    {
        std::string stdId;
        std::cout << "Enter id of the user: ";
        std::cin >> stdId;

        std::string stdMessage;
        std::cout << "Enter da message: ";
        std::cin >> stdMessage;

        QString id = QString::fromStdString(stdId);
        QString message = QString::fromStdString(stdMessage);

        emit sendText(id, message);
    }
    else if (choise == 2)
    {
        QList<QPair<QString, QString> > friendList;

        emit getFriends(friendList);

        std::cout << "Friend list:\n";

        for (int i = 0; i < friendList.size(); i++)
            std::cout << friendList[i].first.toStdString() << " - " << friendList[i].second.toStdString() << "\n";

    }
    else if (choise == 3)
    {
        std::cout << "Type the number of protocol: ";
        int number = 0;
        std::cin >> number;
        emit changeProtocol(number);

        QString currentProtocol;
        emit getCurrentProtocol(currentProtocol);
        std::cout << "New protocol is \"" << currentProtocol.toStdString() << "\"\n";
    }
    else if (choise == 4)
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

    connect(this, SIGNAL(sendText(QString&,QString&)), switcher, SIGNAL(sendText(QString&,QString&)));
    connect(this, SIGNAL(getFriends(QList<QPair<QString,QString> >&)), switcher, SIGNAL(getFriends(QList<QPair<QString,QString> >&)));

    emit loadPlugins(currentDir);
}

