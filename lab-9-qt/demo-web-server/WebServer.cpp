#include "WebServer.h"

#include <QTcpSocket>

#include <iostream>

using namespace std;

WebServer::WebServer(const QHostAddress& ip, quint16 port) {
    _server = new QTcpServer;
    connect(_server, &QTcpServer::newConnection, this, &WebServer::handleClient);
    if (!_server->listen(ip, port)) {
        cout << "Unable to start the server." << endl;
        cout << _server->errorString().toUtf8().constData() << endl;
        return;
    }

    cout << "The server is running on " << _server->serverAddress().toString().toUtf8().constData() << ":" << _server->serverPort() << endl;
}

WebServer::~WebServer() {
    _server->close();
    _server->disconnect();
    _server->deleteLater();
}

void WebServer::handleClient() {
    // Получаем следующее ожидающее соединение
    auto socket = _server->nextPendingConnection();
    if (socket == nullptr)
        return;
    connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

    // Ждём, пока установится связь
    if (!socket->waitForConnected(1000)) {
        socket->deleteLater();
        return;
    }

    // Считываем данные клиента
    cout << "Data from client:" << endl;
    while (socket->waitForReadyRead(1000)) {
        while (socket->canReadLine()) {
            cout << "\t" << socket->readLine().constData();
        }
    }
    cout << endl;

    // Отправляем данные клиенту
    socket->write("HTTP/1.1 200 OK\n");
    socket->write("Content-Type: text/plain\n");
    socket->write("Content-Length: 12\n");
    socket->write("\n");
    socket->write("Hello world!");
    socket->flush();

    // Разрываем соединение
    socket->disconnectFromHost();
}
