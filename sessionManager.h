#pragma once

#include "gameSession.h"

class SessionManager
{
public:
    GameSession* createSession(int rows, int cols, int bombs, int maxPlayers, QWebSocket* creator);
    QList<GameSession*> getAvailableSessions() const;
    GameSession* getSessionById(int sessionId);

private:
    QList<GameSession*> sessions;
    int nextSessionId = 1;
};
