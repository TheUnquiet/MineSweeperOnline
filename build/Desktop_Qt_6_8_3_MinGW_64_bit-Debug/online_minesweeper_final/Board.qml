import QtQuick
import QtQuick.Controls
import "BoardLogic.js" as BoardLogic

Item {
  id: board
  property int rows: 0
  property int cols: 0
  property int bombs: 0
  property var grid: []
  property alias repeater: repeater

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
