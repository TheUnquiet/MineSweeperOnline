#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <QWebSocket>

struct GameSession {
    int id;
    int rows;
    int cols;
    int bombs;
    int maxPlayers;
    QList<QWebSocket*> players;

    GameSession() = default;

    GameSession(int id_, int r, int c, int b, int maxP)
        : id(id_), rows(r), cols(c), bombs(b), maxPlayers(maxP) {}

    bool isFull() const {
        return players.size() >= maxPlayers;
    }
};

#endif // GAMESESSION_H
