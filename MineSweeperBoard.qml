import QtQuick
import QtQuick.Controls
import "BoardLogic.js" as BoardLogic

Item {
  id: board
  property int rows: 0
  property int cols: 0
  property var grid: []
  property alias repeater: repeater

  property var game: ({})
  property bool running: false
  property var currentGame: ({})

  onGameChanged: {

    if (game.rows === undefined) {
      return
    }

    rows = game.rows
    cols = game.cols

    BoardLogic.initGameFromServer(rows, cols, board.grid, board.repeater)
  }

  onCurrentGameChanged: {
    if (currentGame.rows === undefined) {
      return
    }

    BoardLogic.setUpGameFromServer(rows, cols, board.grid, currentGame.bombs)
    board.running = true
  }

  function revealCell(r, c) {
    if (grid[r] && grid[r][c]) {
      BoardLogic.revealCell(board, r, c, grid, rows, cols,
                            BoardLogic.revealAll, BoardLogic.checkWin)
    } else {
      console.warn(`Tried to reveal invalid cell at (${r}, ${c})`)
    }
  }

  Grid {
    id: gameGrid
    rows: board.rows
    columns: board.cols
    spacing: 1

    Repeater {
      id: repeater
      model: rows * cols

      delegate: Cell {
        row: Math.floor(index / cols)
        col: index % cols

        onClicked: {
          if (!isRevealed && !isFlagged) {
            board.revealCell(row, col)
          }
        }
      }
    }
  }
}
