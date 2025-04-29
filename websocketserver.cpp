#include "webSocketServer.h"
#include <QDebug>

WebSocketServer::WebSocketServer(QObject *parent) : QObject(parent), server(new QWebSocketServer("Qt WebSocket Server", QWebSocketServer::NonSecureMode, this)) {
    if (server->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Websocket Server started on port 1234";
        connect(server, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
    } else {
        qDebug() << "Failed to start WebSocket Server!";
    }
}

WebSocketServer::~WebSocketServer() {
    qDeleteAll(clients);
}

void WebSocketServer::onNewConnection() {
    QWebSocket *client = server->nextPendingConnection();

    connect(client, &QWebSocket::textMessageReceived, this, &WebSocketServer::onMessageRecieved);
    connect(client, &QWebSocket::disconnected, this, &WebSocketServer::onClientDisconnect);

    clients.append(client);
    qDebug() << "New Client Connect";
}

void WebSocketServer::onMessageRecieved(const QString &message) {
    qDebug() << "Recieved Message:" << message;

    for (QWebSocket *client : std::as_const(clients)) {
        if (client->isValid()) {
            client->sendTextMessage(message);
        }
    }
}

void WebSocketServer::onClientDisconnect() {
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        clients.removeAll(client);
        client->deleteLater();
        qDebug() << "Client disconnected";
    }
}

void WebSocketServer::broadcastClientCount() {
    int count = clients.size();
    QString message = QString("{\"type\": \"clientCount\", \"count\": %1}").arg(count);
    for (QWebSocket *client : std::as_const(clients)) {
        if (client->isValid()) {
            client->sendTextMessage(message);
        }
    }
}
