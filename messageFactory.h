#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include "gameSession.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class MessageFactory : public QObject
{
    Q_OBJECT
public:
    static QString sessionCreated(int id);
    static QString sessionList(const QList<GameSession*>& sessions);
    static QString sessionJoined(GameSession* session);
    static QString newGame(GameSession* session, const QVector<QPair<int, int>>& bombs);

    inline static QString toJson(const QJsonObject &obj) {
        return QJsonDocument(obj).toJson(QJsonDocument::Compact);
    }
};

#endif // MESSAGEFACTORY_H
