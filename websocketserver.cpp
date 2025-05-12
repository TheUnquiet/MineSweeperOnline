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
    // hash ( sessie->clients )

    if (type == GameServerMessageTypes::CreateSession) {
        auto session = sessionManager.createSession(obj["rows"].toInt(), obj["cols"].toInt(),
                                                     obj["bombs"].toInt(), obj["players"].toInt(), client);
        client->sendTextMessage(MessageFactory::sessionCreated(session->id));

    } else if (type == GameServerMessageTypes::GetSessions) {
        client->sendTextMessage(MessageFactory::sessionList(sessionManager.getAvailableSessions()));

    } else if (type == GameServerMessageTypes::JoinSession) {
        auto session = sessionManager.getSessionById(obj["sessionId"].toInt());
        if (!session || session->isFull()) {
            return;
        }
        session->players.append(client); // in GameSession
        client->sendTextMessage(MessageFactory::sessionJoined(session));
        if (session->isFull())  {
            startGameForSession(session); // aan sessie zeggen start de game
        }
            // client->sendTextMessage(MessageFactory::toJson(session->join(obj)));
            // session->join()
    }
}

void WebSocketServer::onClientDisconnect() {
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    // sessionManager.getSessionForClient(client)
    // -> session object
    // session->close()
    if (client) {
        clients.removeAll(client);
        client->deleteLater();
        qDebug() << "Client disconnected";
    }
}

// in session
void WebSocketServer::startGameForSession(GameSession* session) {

    GameBuilder builder(session->rows, session->cols, session->bombs);
    QVector<QPair<int, int>> bombsArray = builder.generateBombs();

    QString message = MessageFactory::newGame(session, bombsArray);
    for (QWebSocket *client : session->players) {
        if (client && client->isValid()) {
            client->sendTextMessage(message);
        }
    }
}










