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
    static QString sessionList(const QList<GameSession>& sessions);
    static QString sessionJoined(const GameSession& session);
    static QString newGame(const GameSession& session, const QVector<QPair<int, int>>& bombs);
};

#endif // MESSAGEFACTORY_H
