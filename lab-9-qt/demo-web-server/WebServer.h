#pragma once

#include <QHostAddress>
#include <QTcpServer>

/**
 * Сервер.
 */
class WebServer final: public QObject {

Q_OBJECT

private:

    QTcpServer* _server; /**< TCP-сервер. */

public:

    /**
     * Конструктор сервера.
     * 
     * @param ip IP-адрес, на котором будет развернут сервер.
     * @param port Порт, на котором будет развернут сервер.
     */
    WebServer(const QHostAddress& ip, quint16 port);


    /**
     * Запрещённый конструктор копирования.
     */
    WebServer(const WebServer&) = delete;

    /**
     * Запрещённый оператор присваивания копированием.
     */
    WebServer& operator=(const WebServer&) = delete;

    /**
     * Деструктор.
     */
    ~WebServer();

private slots:

    /**
     * Метод обработки очередного клиентского соединения.
     */
    void handleClient();
  
};
