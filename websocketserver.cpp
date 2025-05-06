#include "webSocketServer.h"
#include "sessionManager.h"
#include "messageFactory.h"
#include "gameServerMessageTypes.h"
#include "gameBuilder.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

WebSocketServer::WebSocketServer(QObject *parent)
    : QObject(parent),
    server(new QWebSocketServer("Qt WebSocket Server", QWebSocketServer::NonSecureMode, this)) {
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
    QJsonObject obj = QJsonDocument::fromJson(message.toUtf8()).object();
    QString type = obj["type"].toString();
    QWebSocket* client = qobject_cast<QWebSocket*>(sender());

    if (type == GameServerMessageTypes::CreateSession) {
        auto& session = sessionManager.createSession(obj["rows"].toInt(), obj["cols"].toInt(),
                                                     obj["bombs"].toInt(), obj["players"].toInt(), client);
        client->sendTextMessage(MessageFactory::sessionCreated(session.id));

    } else if (type == GameServerMessageTypes::GetSessions) {
        client->sendTextMessage(MessageFactory::sessionList(sessionManager.getAvailableSessions()));

    } else if (type == GameServerMessageTypes::JoinSession) {
        bool gameStarted = false;
        if (sessionManager.joinSession(obj["sessionId"].toInt(), client, gameStarted)) {
            const GameSession* session = sessionManager.getSessionById(obj["sessionId"].toInt());
            if (gameStarted && session)
                startGameForSession(*session);
            else
                client->sendTextMessage(MessageFactory::sessionJoined(*session));
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

void WebSocketServer::startGameForSession(const GameSession &session) {
    GameBuilder builder(session.rows, session.cols, session.bombs);
    QVector<QPair<int, int>> bombsArray = builder.generateBombs();

    QString message = MessageFactory::newGame(session, bombsArray);
    for (QWebSocket *client : session.players) {
        if (client && client->isValid()) {
            client->sendTextMessage(message);
        }
    }
}
