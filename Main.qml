import QtQuick
import QtQuick.Controls
import QtWebSockets
import "BoardLogic.js" as BoardLogic

ApplicationWindow {
  id: window
  width: 600
  height: 600
  title: "Minesweeper Online Final"
  visible: true

  property int rows: 10
  property int cols: 10
  property int bombs: 15
  property int connectedClients

  WebSocket {
    id: socket
    url: "ws://127.0.0.1:1234"
    active: true
    onTextMessageReceived: function (message) {
      console.log("Received: " + message)
      var data = JSON.parse(message)
      if (data.type === "clientCount") {
        connectedClients = data.count
      }
    }

    onStatusChanged: {
      if (socket.status === WebSocket.Open) {
        console.log("WebSocket connected")
        socket.sendTextMessage("Hello from QML client!")
      } else if (socket.status === WebSocket.Closed) {
        console.log("WebSocket connection closed")
      } else if (socket.status === WebSocket.Connecting) {
        console.log("WebSocket connecting...")
      } else {
        console.log("WebSocket error")
      }

      console.log(socket.status)
    }
  }

  Rectangle {
    anchors.centerIn: parent
    implicitHeight: button.implicitHeight + board.implicitHeight
    implicitWidth: Math.max(button.implicitWidth, board.implicitWidth)

    x: 150
    y: 100

    Button {
      id: button
      anchors.top: parent.top
      anchors.left: parent.left
      text: "Restart"
      onClicked: BoardLogic.initGame()
    }

    Board {
      id: board
      anchors.top: button.bottom
      anchors.left: parent.left
      rows: window.rows
      cols: window.cols
      bombs: window.bombs
    }
  }

  Text {
    id: clientsText
    text: "Player count: " + connectedClients
    font.pixelSize: 24
  }
}
