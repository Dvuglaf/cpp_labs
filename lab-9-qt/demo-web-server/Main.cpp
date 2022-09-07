#include <QCoreApplication>
#include <QHostAddress>
#include <QNetworkInterface>

#include <iostream>

#include "WebServer.h"

using namespace std;

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    auto ipList = QNetworkInterface::allAddresses();
    for (const auto& ip : ipList) {
        cout << ip.toString().toUtf8().constData() << endl;
    }
    cout << endl;

    WebServer webServer(QHostAddress::Any, 80);

    return QCoreApplication::exec();
}
