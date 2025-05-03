import QtQuick
import QtQuick.Controls
import QtWebSockets

ApplicationWindow {
  visible: true
  width: 600
  height: 600
  title: "Minesweeper Final"

  property var sessions: []
  property int connectedClients: 0

  WebSocket {
    id: webSocket
    url: "ws://127.0.0.1:1234"
    active: true

    onTextMessageReceived: function (message) {
      console.log("Received: " + message)
      var data = JSON.parse(message)

      if (data.type === "clientCount") {
        connectedClients = data.count
      } else if (data.type === "sessionList") {
        sessions = data.sessions
      } else if (data.type === "sessionJoined" || data.type === "newGame") {
        if (data.type === "newGame") {
          boardPageRef.rows = data.rows
          boardPageRef.cols = data.cols
          boardPageRef.bombs = data.bombs.length
          Qt.callLater(() => {
                         BoardLogic.initGameFromServer(boardPageRef, data.rows,
                                                       data.cols, data.bombs,
                                                       boardPageRef.grid,
                                                       boardPageRef.repeater)
                       })
        }
        stackView.push(boardPageComponent)
      }
    }
  }

  StackView {
    id: stackView
    anchors.fill: parent
    initialItem: LandingPage {
      socket: webSocket
      onStartGame: stackView.push(startPageComponent)
      onJoinGame: {
        webSocket.sendTextMessage(JSON.stringify({
                                                   "type": "getSessions"
                                                 }))
        stackView.push(joinPageComponent)
      }
    }
  }

  Component {
    id: startPageComponent
    StartSessionPage {
      socket: webSocket
      onBack: stackView.pop()
    }
  }

  Component {
    id: joinPageComponent
    JoinSessionPage {
      socket: webSocket
      sessionList: sessions
      onBack: stackView.pop()
    }
  }

  Component {
    id: boardPageComponent
    BoardPage {
      id: boardPageRef
    }
  }
}
