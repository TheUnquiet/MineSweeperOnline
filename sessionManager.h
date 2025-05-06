#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "gameSession.h"

class SessionManager
{
public:
    GameSession& createSession(int rows, int cols, int bombs, int maxPlayers, QWebSocket* creator);
    QList<GameSession> getAvailableSessions() const;
    GameSession* getSessionById(int sessionId);
    bool joinSession(int sessionId, QWebSocket* client, bool& gameStarted);

private:
    QList<GameSession> sessions;
    int nextSessionId = 1;
};

#endif // SESSIONMANAGER_H
