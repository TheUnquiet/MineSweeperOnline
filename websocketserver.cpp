#include "webSocketServer.h"
#include "gameBuilder.h"
#include "gameServerMessageTypes.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

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

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj = doc.object();

    QString type = obj["type"].toString();

    if (type == GameServerMessageTypes::CreateSession) {
        GameSession session;
        session.id = nextSessionId++;
        session.rows = obj["rows"].toInt();
        session.cols = obj["cols"].toInt();
        session.bombs = obj["bombs"].toInt();
        session.maxPlayers = obj["players"].toInt();
        sessions.append(session);

        QJsonObject response;
        response["type"] = "sessionCreated";
        response["sessionId"] = session.id;

        QJsonDocument responseDoc(response);
        qobject_cast<QWebSocket*>(sender())->sendTextMessage(responseDoc.toJson());

        session.players.append(qobject_cast<QWebSocket*>(sender()));
    } else if (type == GameServerMessageTypes::GetSessions) {
        QJsonArray sessionList;

        for (const GameSession &session : std::as_const(sessions)) {
            if (!session.isFull()) {
                QJsonObject s;
                s["id"] = session.id;
                s["rows"] = session.rows;
                s["cols"] = session.cols;
                s["bombs"] = session.bombs;
                s["playersJoined"] = session.players.size();
                s["maxPlayers"] = session.maxPlayers;
                sessionList.append(s);
            }
        }

        QJsonObject response;
        response["type"] = "sessionList";
        response["sessions"] = sessionList;

        QJsonDocument responseDoc(response);
        qobject_cast<QWebSocket*>(sender())->sendTextMessage(responseDoc.toJson());

    } else if (type == GameServerMessageTypes::JoinSession) {
        int sessionId = obj["sessionId"].toInt();
        QWebSocket *client = qobject_cast<QWebSocket*>(sender());

        for (GameSession &session : sessions) {
            if (session.id == sessionId && !session.isFull()) {
                session.players.append(client);

                if (session.isFull()) {
                    startGameForSession(session);
                } else {
                    // Game not started
                    QJsonObject joinedMsg;
                    joinedMsg["type"] = "sessionJoined";
                    joinedMsg["sessionId"] = session.id;

                    joinedMsg["rows"] = session.rows;
                    joinedMsg["cols"] = session.cols;
                    joinedMsg["bombs"] = session.bombs;

                    QJsonDocument joinedDoc(joinedMsg);
                    client->sendTextMessage(joinedDoc.toJson());
                }

                break;
            }
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

void WebSocketServer::startNewGame(int rows, int cols, int bombs) {
    GameBuilder builder(rows, cols, bombs);

    QVector<QPair<int, int>> bombsArray = builder.generateBombs();

    QJsonArray bombArray;
    for (const QPair<int, int> &pos : std::as_const(bombsArray)) {
        QJsonObject bombObj;
        bombObj["x"] = pos.first;
        bombObj["y"] = pos.second;
        bombArray.append(bombObj);
    }

    QJsonObject gameStartMsg;
    gameStartMsg["type"] = "newGame";
    gameStartMsg["bombs"] = bombArray;

    QJsonDocument doc(gameStartMsg);
    QString jsonString = doc.toJson(QJsonDocument::Compact);

    // Send to all connected clients
    for (QWebSocket *client : std::as_const(clients)) {
        if (client->isValid()) {
            client->sendTextMessage(jsonString);
        }
    }
}

void WebSocketServer::startGameForSession(const GameSession &session) {
    GameBuilder builder(session.rows, session.cols, session.bombs);
    QVector<QPair<int, int>> bombsArray = builder.generateBombs();

    QJsonArray bombArray;
    for (const QPair<int, int> &pos : std::as_const(bombsArray)) {
        QJsonObject bombObj;
        bombObj["x"] = pos.first;
        bombObj["y"] = pos.second;
        bombArray.append(bombObj);
    }

    QJsonObject gameStartMsg;
    gameStartMsg["type"] = "newGame";
    gameStartMsg["rows"] = session.rows;
    gameStartMsg["cols"] = session.cols;
    gameStartMsg["bombs"] = bombArray;

    QJsonDocument doc(gameStartMsg);
    QString jsonString = doc.toJson(QJsonDocument::Compact);

    for (QWebSocket *client : session.players) {
        if (client && client->isValid()) {
            client->sendTextMessage(jsonString);
        }
    }
}
