function handleCellClick(mouse, cell) {
  if (mouse.button === Qt.RightButton) {
    if (!cell.isRevealed) {
      cell.isFlagged = !cell.isFlagged;
    }
  } else {
    cell.clicked();
  }
}
