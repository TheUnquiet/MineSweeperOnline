#include "messageFactory.h"

QString MessageFactory::sessionCreated(int id) {
    QJsonObject obj;
    obj["type"] = "sessionCreated";
    obj["sessionId"] = id;
    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QString MessageFactory::sessionJoined(const GameSession& session) {
    QJsonObject obj;
    obj["type"] = "sessionJoined";
    obj["sessionId"] = session.id;
    obj["rows"] = session.rows;
    obj["cols"] = session.cols;
    obj["bombs"] = session.bombs;

    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QString MessageFactory::sessionList(const QList<GameSession>& sessions) {
    QJsonArray array;
    for (const GameSession& s : sessions) {
        QJsonObject o;
        o["id"] = s.id;
        o["rows"] = s.rows;
        o["cols"] = s.cols;
        o["bombs"] = s.bombs;
        o["playersJoined"] = s.players.size();
        o["maxPlayers"] = s.maxPlayers;
        array.append(o);
    }

    QJsonObject obj;
    obj["type"] = "sessionList";
    obj["sessions"] = array;

    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

QString MessageFactory::newGame(const GameSession& session, const QVector<QPair<int, int>>& bombs) {
    QJsonArray bombArray;
    for (const auto& pair : bombs) {
        QJsonObject bomb;
        bomb["x"] = pair.first;
        bomb["y"] = pair.second;
        bombArray.append(bomb);
    }

    QJsonObject obj;
    obj["type"] = "newGame";
    obj["rows"] = session.rows;
    obj["cols"] = session.cols;
    obj["bombs"] = bombArray;

    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}