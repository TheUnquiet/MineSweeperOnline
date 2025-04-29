function initGame(board, rows, cols, bombs, grid, repeater) {
  for (var r = 0; r < rows; r++) {
    grid[r] = []
    for (var c = 0; c < cols; c++) {
      let cell = repeater.itemAt(r * cols + c)
      cell.isBomb = false
      cell.isFlagged = false
      cell.isRevealed = false
      cell.neighborBombs = 0
      grid[r][c] = cell
    }
  }

  let placed = 0
  while (placed < bombs) {
    let r = Math.floor(Math.random() * rows)
    let c = Math.floor(Math.random() * cols)
    let cell = grid[r][c]
    if (!cell.isBomb) {
      cell.isBomb = true
      placed++
      console.log("Bomb at:", r + 1, c + 1)
    }
  }

  for (var r = 0; r < rows; r++) {
    for (var c = 0; c < cols; c++) {
      let count = 0
      for (var dr = -1; dr <= 1; dr++) {
        for (var dc = -1; dc <= 1; dc++) {
          if (dr === 0 && dc === 0)
            continue
          let nr = r + dr
          let nc = c + dc
          if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
            if (grid[nr][nc].isBomb)
              count++
          }
        }
      }
      grid[r][c].neighborBombs = count
    }
  }
}

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
