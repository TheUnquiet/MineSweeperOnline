#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include "gameSession.h"
#include "sessionManager.h"

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
    void startGameForSession(GameSession* session);

private:
    QWebSocketServer *server;
    QList<QWebSocket *> clients;

    SessionManager sessionManager;

signals:
    void serverStarted();
};

#endif // WEBSOCKETSERVER_H
