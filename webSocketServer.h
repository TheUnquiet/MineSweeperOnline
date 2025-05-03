#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QwebSocket>

struct GameSession {
    int id;
    int rows;
    int cols;
    int bombs;
    int maxPlayers;
    QVector<QWebSocket*> players;

    bool isFull() const {
        return players.size() >= maxPlayers;
    }
};

class WebSocketServer : public QObject {
    Q_OBJECT

public:
    explicit WebSocketServer(QObject *parent = nullptr);
    ~WebSocketServer();

private slots:
    void onNewConnection();
    void onMessageRecieved(const QString &message);
    void onClientDisconnect();
    void broadcastClientCount();
    void startNewGame(int rows, int cols, int bombs);
    void startGameForSession(const GameSession &session);

private:
    QWebSocketServer *server;
    QList<QWebSocket *> clients;
    int nextSessionId = 1;
    QList<GameSession> sessions;

signals:
    void serverStarted();
};

#endif // WEBSOCKETSERVER_H
