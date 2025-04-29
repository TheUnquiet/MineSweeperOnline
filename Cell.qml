import QtQuick
import "CellLogic.js" as CellLogic

Item {
  id: cell
  implicitHeight: 40
  implicitWidth: 40

  property int row: 0
  property int col: 0
  property bool isBomb: false
  property bool isFlagged: false
  property bool isRevealed: false
  property int neighborBombs: 0

  signal clicked
  signal rightClicked
  signal revealRequested

  Rectangle {
    anchors.fill: parent
    color: cell.isRevealed ? (cell.isBomb ? "red" : "#ddd") : "#aaa"
    border.color: "#444"
    border.width: 1

    MouseArea {
      anchors.fill: parent
      acceptedButtons: Qt.LeftButton | Qt.RightButton

      onClicked: mouse => {
                   CellLogic.handleCellClick(mouse, cell)
                 }
    }

    Text {
      anchors.centerIn: parent
      visible: cell.isRevealed && !cell.isBomb && cell.neighborBombs > 0
      text: cell.neighborBombs
      font.bold: true
      color: "black"
    }

    Image {
      anchors.centerIn: parent
      source: "https://cdn-icons-png.flaticon.com/512/703/703355.png"
      visible: cell.isFlagged && !cell.isRevealed
      width: 24
      height: 24
    }

    Image {
      anchors.centerIn: parent
      source: "https://cdn-icons-png.flaticon.com/512/112/112683.png"
      visible: cell.isRevealed && cell.isBomb
      width: 24
      height: 24
    }
  }
}
