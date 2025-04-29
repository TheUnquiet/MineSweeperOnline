#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QwebSocket>

class WebSocketServer : public QObject {
    Q_OBJECT

public:
    explicit WebSocketServer(QObject *parent = nullptr);
    ~WebSocketServer();

private slots:
    void onNewConnection();
    void onMessageRecieved(const QString &message);
    void onClientDisconnect();
    void broadcastClientCount();

private:
    QWebSocketServer *server;
    QList<QWebSocket *> clients;

signals:
    void serverStarted();
};

#endif // WEBSOCKETSERVER_H
