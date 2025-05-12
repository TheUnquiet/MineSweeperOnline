#include "messageFactory.h"

QString MessageFactory::sessionCreated(int id) {
    QJsonObject obj;
    obj["type"] = "sessionCreated";
    obj["sessionId"] = id;
    return toJson(obj);
}

QString MessageFactory::sessionJoined(GameSession* session) {
    QJsonObject obj;
    obj["type"] = "sessionJoined";
    obj["sessionId"] = session->id;
    obj["rows"] = session->rows;
    obj["cols"] = session->cols;
    obj["bombs"] = session->bombs;
    obj["gameType"] = "MineSweeper";

    return toJson(obj);
}

QString MessageFactory::sessionList(const QList<GameSession*>& sessions) {
    QJsonArray array;
    for (auto s : sessions) {
        QJsonObject o;
        o["id"] = s->id;
        o["gameType"] = "MineSweeper";
        o["playersJoined"] = s->players.size(); // level deeper
        o["maxPlayers"] = s->maxPlayers;
        array.append(o);
    }

    QJsonObject obj;
    obj["type"] = "sessionList";
    obj["sessions"] = array;

    return toJson(obj);
}

QString MessageFactory::newGame(GameSession* session, const QVector<QPair<int, int>>& bombs) {
    QJsonArray bombArray;
    for (const auto& pair : bombs) {
        QJsonObject bomb;
        bomb["x"] = pair.first;
        bomb["y"] = pair.second;
        bombArray.append(bomb);
    }

    QJsonObject obj;
    obj["type"] = "newGame";
    obj["rows"] = session->rows;
    obj["cols"] = session->cols;
    obj["bombs"] = bombArray;

    return toJson(obj);
}









