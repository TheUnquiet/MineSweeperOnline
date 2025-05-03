import QtQuick
import QtQuick.Controls

Item {
  signal startGame
  signal joinGame

  // Just a plain property (no alias needed)
  property var socket

  width: parent ? parent.width : 600
  height: parent ? parent.height : 600

  Column {
    anchors.centerIn: parent
    spacing: 20

    Button {
      text: "Start Game"
      onClicked: startGame()
    }

    Button {
      text: "Join Game"
      onClicked: joinGame()
    }
  }
}
