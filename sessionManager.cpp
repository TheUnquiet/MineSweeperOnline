#include "sessionManager.h"

GameSession* SessionManager::createSession(int rows, int cols, int bombs, int maxPlayers, QWebSocket* creator) {
    //session.players.append(creator);
    sessions.append( new GameSession(nextSessionId++, rows, cols, bombs, maxPlayers) ); // new GameSession
    return sessions.last(); // Return last session*
}

QList<GameSession*> SessionManager::getAvailableSessions() const{
    QList<GameSession*> availableSessions;
    for (auto session : sessions) {
        if ( ! session->isFull() ) {
            availableSessions.append(session);
        }
    }

    return availableSessions;
}

GameSession* SessionManager::getSessionById(int sessionId) {
    for (auto session : sessions) {
        if (session->id == sessionId) return session;
    }
    return nullptr;
}

