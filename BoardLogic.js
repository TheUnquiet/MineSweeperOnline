function revealCell(board, r, c, grid, rows, cols, revealAll, checkWin) {
  let cell = grid[r][c]
  if (cell.isRevealed || cell.isFlagged)
    return

  cell.isRevealed = true

  if (cell.isBomb) {
    console.log("Game Over")
    revealAll(grid, rows, cols)
    return
  }

  if (cell.neighborBombs === 0) {
    for (var dr = -1; dr <= 1; dr++) {
      for (var dc = -1; dc <= 1; dc++) {
        if (dr === 0 && dc === 0)
          continue
        let nr = r + dr
        let nc = c + dc
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
          revealCell(board, nr, nc, grid, rows, cols, revealAll, checkWin)
        }
      }
    }
  }

  checkWin(grid, rows, cols, revealAll)
}

function checkWin(grid, rows, cols, revealAll) {
  for (var r = 0; r < rows; r++) {
    for (var c = 0; c < cols; c++) {
      let cell = grid[r][c]
      if (!cell.isBomb && !cell.isRevealed)
        return
    }
  }

  console.log("Game Won")
  revealAll(grid, rows, cols)
}

function revealAll(grid, rows, cols) {
  for (var r = 0; r < rows; r++) {
    for (var c = 0; c < cols; c++) {
      grid[r][c].isRevealed = true
    }
  }
}

function initGameFromServer(rows, cols, grid, repeater) {
  for (var r = 0; r < rows; r++) {
    grid[r] = []
    for (var c = 0; c < cols; c++) {
      let cell = repeater.itemAt(r * cols + c)
      grid[r][c] = cell
    }
  }
}
function setUpGameFromServer(rows, cols, grid, bombList) {
  grid.forEach(row => row.forEach(cell => {
                                    cell.isBomb = false
                                    cell.isFlagged = false
                                    cell.isRevealed = false
                                    cell.neighborBombs = 0
                                  }))
  for (var i = 0; i < bombList.length; i++) {
    let x = bombList[i].x
    let y = bombList[i].y
    grid[y][x].isBomb = true
    console.log(grid[y][x].isBomb)
  }

  for (var r = 0; r < rows; r++) {
    for (var c = 0; c < cols; c++) {
      let count = 0
      for (var dr = -1; dr <= 1; dr++) {
        for (var dc = -1; dc <= 1; dc++) {
          if (dr === 0 && dc === 0)
            continue
          let nr = r + dr, nc = c + dc
          if (nr >= 0 && nr < rows && nc >= 0 && nc < cols
              && grid[nr][nc].isBomb)
            count++
        }
      }
      grid[r][c].neighborBombs = count
    }
  }
}
