import QtQuick
import "BoardLogic.js" as BoardLogic

Item {
  id: board
  property int rows: 10
  property int cols: 10
  property int bombs: 15
  property var grid: []

  property alias repeater: repeater

  implicitWidth: gameGrid.implicitWidth
  implicitHeight: gameGrid.implicitHeight

  function revealCell(r, c) {
    BoardLogic.revealCell(board, r, c, grid, rows, cols, BoardLogic.revealAll,
                          BoardLogic.checkWin)
  }

  Grid {
    id: gameGrid
    rows: board.rows
    columns: board.cols
    spacing: 1

    Repeater {
      id: repeater
      model: board.rows * board.cols
      delegate: Cell {
        row: index / board.cols
        col: index % board.cols

        onClicked: {
          if (!isRevealed && !isFlagged) {
            board.revealCell(row, col)
          }
        }
      }
    }

    Component.onCompleted: {
      Qt.callLater(() => {
                     BoardLogic.initGame(board, rows, cols, bombs,
                                         grid, repeater)
                   })
    }
  }
}
