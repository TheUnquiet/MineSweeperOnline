#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include <QObject>

class GameBuilder : public QObject  {
    Q_OBJECT

public:
    explicit GameBuilder(int rows, int cols, int bombs);
    ~GameBuilder();
    QVector<QPair<int, int>> generateBombs();

private:
    int m_rows;
    int m_cols;
    int m_bombs;
};

#endif // GAMEBUILDER_H
