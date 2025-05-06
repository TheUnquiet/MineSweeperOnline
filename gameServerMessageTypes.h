#ifndef GAMESERVERMESSAGETYPES_H
#define GAMESERVERMESSAGETYPES_H

#include <QObject>

class GameServerMessageTypes : public QObject {
    Q_OBJECT
public:
    static QString CreateSession;
    static QString GetSessions;
    static QString JoinSession;

private:
    GameServerMessageTypes();
};

#endif // GAMESERVERMESSAGETYPES_H
