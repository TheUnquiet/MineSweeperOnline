#include "gameBuilder.h"
#include <QRandomGenerator>

GameBuilder::GameBuilder(int rows, int cols, int bombs)
    : m_rows(rows), m_cols(cols), m_bombs(bombs) {}

QVector<QPair<int, int>> GameBuilder::generateBombs() {
    QVector<QPair<int, int>> bombPositions;

    while (bombPositions.size() < m_bombs) {
        int x = QRandomGenerator::global()->bounded(m_cols);
        int y = QRandomGenerator::global()->bounded(m_rows);

        bool exists = false;
        for (const auto& bomb : bombPositions) {
            if (bomb.first == x && bomb.second == y) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            bombPositions.append(qMakePair(x, y));
        }
    }
    return bombPositions;
}

GameBuilder::~GameBuilder() {}