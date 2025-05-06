#include "sessionManager.h"

GameSession& SessionManager::createSession(int rows, int cols, int bombs, int maxPlayers, QWebSocket* creator) {
    GameSession session(nextSessionId++, rows, cols, bombs, maxPlayers);
    //session.players.append(creator);
    sessions.append(session);
    return sessions.last(); // Return last session*
}

QList<GameSession> SessionManager::getAvailableSessions() const{
    QList<GameSession> availableSessions;
    for (const GameSession& session : sessions) {
        if (!session.isFull()) availableSessions.append(session);
    }

    return availableSessions;
}

GameSession* SessionManager::getSessionById(int sessionId) {
    for (GameSession& session : sessions) {
        if (session.id == sessionId) return &session;
    }
    return nullptr;
}

bool SessionManager::joinSession(int sessionId, QWebSocket* client, bool& gameStarted) {
    GameSession* session = getSessionById(sessionId);
    if (!session || session->isFull()) return false;

    session->players.append(client);
    gameStarted = session->isFull();
    return true;
}